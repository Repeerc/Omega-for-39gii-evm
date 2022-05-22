
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	${OBJCOPY} -I elf32-little -O binary -R .note -R .comment -S $(BUILD_DIR)/%.elf $(BUILD_DIR)/%.bin



