PROGRAM_NAME:= hestia
SRC_DIR:= src

build:
	gcc -o $(PROGRAM_NAME) $(SRC_DIR)/main.c $(SRC_DIR)/hestia.c -lsqlite3

run:
	./$(PROGRAM_NAME) --help

watch: 
	$(MAKE) build
	$(MAKE) run 
dev:
	@echo "Watching for changes... "
	watchexec -e c make watch