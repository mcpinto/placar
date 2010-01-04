all:
	$(MAKE) -C generator
	$(MAKE) -C status
	$(MAKE) -C view
clean:
	$(MAKE) -C generator clean
	$(MAKE) -C status clean
	$(MAKE) -C view clean
	$(MAKE) -C log clean
