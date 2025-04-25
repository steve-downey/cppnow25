TOPLEVEL := clean clean-venv compile coverage ctest dev-shell help install lint lint-manual realclean show-venv test venv

$(TOPLEVEL) : code

code:
	$(MAKE) -C code $(MAKECMDGOALS)

.PHONY: code $(TOPLEVEL)
