#!/bin/bash

# Find the USB device that corresponds to the Raspberry Pi Pico (CMSIS-DAP)
PICO_DEVICE=$(lsusb | grep -i 'pico\|cmsis-dap')

if [ -z "$PICO_DEVICE" ]; then
  echo "Pico device not found. Make sure it is plugged in."
  exit 1
fi

# Extract the VID and PID from the lsusb output
VID=$(echo "$PICO_DEVICE" | awk '{print $6}' | cut -d: -f1)
PID=$(echo "$PICO_DEVICE" | awk '{print $6}' | cut -d: -f2)

echo "Detected Pico device with VID:PID = $VID:$PID"

RULES_FILE="/etc/udev/rules.d/99-cmsis-dap.rules"
GDB_SCRIPT="gdb_init_script.gdb"
ELF_FILE="../build/src/myproject.elf"

# Function to compare existing udev rules with the detected values
check_existing_rules() {
  if [ -f "$RULES_FILE" ]; then
    EXISTING_RULE=$(grep -E 'ATTRS{idVendor}==".*", ATTRS{idProduct}==".*"' $RULES_FILE)
    EXISTING_VID=$(echo "$EXISTING_RULE" | grep -oP 'ATTRS{idVendor}=="\K[^"]+')
    EXISTING_PID=$(echo "$EXISTING_RULE" | grep -oP 'ATTRS{idProduct}=="\K[^"]+')

    if [[ "$VID" == "$EXISTING_VID" && "$PID" == "$EXISTING_PID" ]]; then
      echo "udev rules are already up to date. No changes needed."
      return 0
    else
      echo "udev rules differ. Existing VID:PID = $EXISTING_VID:$EXISTING_PID"
      echo "New VID:PID = $VID:$PID"
      return 1
    fi
  else
    echo "udev rules file does not exist. Creating it now."
    return 1
  fi
}

# Check if udev rules need to be updated
if check_existing_rules; then
  echo "No changes to udev rules."
else
  echo "Updating udev rules with new values..."

  # Create or overwrite the udev rule to set the correct permissions for the device
  sudo bash -c "cat <<EOF > $RULES_FILE
SUBSYSTEM==\"usb\", ATTRS{idVendor}==\"$VID\", ATTRS{idProduct}==\"$PID\", MODE=\"0666\", GROUP=\"plugdev\"
EOF"

  # Reload udev rules
  echo "Reloading udev rules..."
  sudo udevadm control --reload-rules
  sudo udevadm trigger

  # Wait for a moment to let udev apply the changes
  sleep 1

  # Check if the USB device is detected with the correct permissions
  echo "Checking device permissions..."
  lsusb -d $VID:$PID
  cat $RULES_FILE
fi

# Start GDB multiarch with the custom script
# echo "Starting gdb-multiarch with target configuration..."
# gdb-multiarch -x $GDB_SCRIPT $ELF_FILE
