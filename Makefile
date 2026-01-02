CC = cc

# Compilation flags (Optimized for minimal size)

CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -fno-omit-frame-pointer -fno-asynchronous-unwind-tables -fno-ident -Os -no-pie -fno-pic -Wall -Werror -Wl,-Tbuild.ld


# Program configuration
TARGET = quecto
ALIAS  = q
INSTALL_DIR = /usr/local/bin

# Files
SRC = quecto.c
HEADER = quecto.h
LDSCRIPT = build.ld

.PHONY: all clean install uninstall

all: $(TARGET) install


# Compile
$(TARGET): $(SRC) $(HEADER)
	@echo "Compiling $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo "Stripping binary file..."
	strip -s -R .comment -R .note $(TARGET)
	@echo ""
	@echo "------------------------------------"
	@echo "Build successful."
	@echo "Binary size: $$(wc -c < $(TARGET)) bytes"
	@echo "------------------------------------"

# Install to system path
install: $(TARGET)
	@echo "Installing to $(INSTALL_DIR)..."
	@cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	@chmod 755 $(INSTALL_DIR)/$(TARGET)
	@ln -sf $(INSTALL_DIR)/$(TARGET) $(INSTALL_DIR)/$(ALIAS)
	@echo "Installed as '$(TARGET)' and alias '$(ALIAS)'."

# Uninstall
uninstall:
	@echo "Removing from $(INSTALL_DIR)..."
	@rm -f $(INSTALL_DIR)/$(TARGET)
	@rm -f $(INSTALL_DIR)/$(ALIAS)
	@echo "Uninstalled."

# Clean workspace
clean:
	@rm -f $(TARGET) $(LDSCRIPT)
	@echo "Cleaned."