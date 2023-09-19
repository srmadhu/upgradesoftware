define FOREACH
	for DIR in common client server; do \
		$(MAKE) -C $$DIR $(1); \
	done
endef

.PHONY: build
build:
	$(call FOREACH,build)

.PHONY: clean
clean:
	$(call FOREACH,clean)

.PHONY: test
test:
	$(call FOREACH,test)
