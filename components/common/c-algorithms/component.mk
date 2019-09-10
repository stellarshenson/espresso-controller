INC_DIRS += $(c-algorithms_ROOT)/c-algorithms/src

c-algorithms_INC_DIR = $(c-algorithms_ROOT)/c-algorithms/src
c-algorithms_SRC_DIR = $(c-algorithms_ROOT)/c-algorithms/src

$(eval $(call component_compile_rules,c-algorithms))
