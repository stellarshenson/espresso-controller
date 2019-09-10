INC_DIRS += $(esp-serial-cmdline_ROOT)

esp-serial-cmdline_INC_DIR = $(esp-serial-cmdline_ROOT)
esp-serial-cmdline_SRC_DIR = $(esp-serial-cmdline_ROOT)

$(eval $(call component_compile_rules,esp-serial-cmdline))
