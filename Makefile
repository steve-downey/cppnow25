TOPLEVEL := clean clean-venv compile coverage ctest dev-shell help install lint lint-manual realclean show-venv test venv

SUB := streams

$(TOPLEVEL) : $(SUB)

streams:
	$(MAKE) -C streams  $(MAKECMDGOALS)

optional:
	$(MAKE) -C optional $(MAKECMDGOALS)

.PHONY: streams optional $(SUB) $(TOPLEVEL)
