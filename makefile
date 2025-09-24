# Makefile for compiling and installing tdlst (Linux/macOS/Windows)

ifeq ($(OS),Windows_NT)
    EXEEXT := .exe
    RM := del /Q
    INSTALL_DIR := $(HOME)/bin
else
    EXEEXT :=
    RM := rm -f
    INSTALL_DIR := $(HOME)/bin
endif

CXX := g++
CXXFLAGS := -Wall -O2
TARGET := tdlst$(EXEEXT)

all: $(TARGET)

$(TARGET): tdlst.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

install: $(TARGET)
	@echo "Installing $(TARGET) into $(INSTALL_DIR)"
ifeq ($(OS),Windows_NT)
	@if not exist "$(HOME)\bin" mkdir "$(HOME)\bin"
	@copy /Y $(TARGET) "$(HOME)\bin\"
	@if not "$(PATH)" == "*$(HOME)\bin*" setx PATH "$(HOME)\bin;%PATH%"
	@echo "Added $(HOME)\bin to PATH permanently (may require restarting terminal)."
else
	@mkdir -p $(INSTALL_DIR)
	@cp $(TARGET) $(INSTALL_DIR)/
	@if ! grep -q 'export PATH="$$HOME/bin:$$PATH"' "$(HOME)/.bashrc"; then \
	    echo 'export PATH="$$HOME/bin:$$PATH"' >> "$(HOME)/.bashrc"; \
	    echo "Added ~/bin to PATH in ~/.bashrc (restart shell or run 'source ~/.bashrc')."; \
	else \
	    echo "~/bin already in PATH."; \
	fi
endif

clean:
	$(RM) $(TARGET)

