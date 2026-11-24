#!/bin/bash

# Exit immediately if any command fails (except our controlled verification checks)
set -e

# Color codes for readable console outputs
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PROJECT_DIR=$(pwd)
echo -e "${BLUE}Starting ANTLR4 C++ Setup in: ${YELLOW}$PROJECT_DIR${NC}\n"

# ==========================================
# Phase 1: Installing System Dependencies
# ==========================================
echo -e "${YELLOW}=== Phase 1: Installing System Dependencies ===${NC}"
sudo apt update
# Added 'curl' and 'default-jre' to support direct JAR downloads and execution
sudo apt install -y build-essential cmake uuid-dev pkg-config unzip wget curl default-jre python3-pip python3-venv
echo -e "${GREEN}✓ System dependencies installed.${NC}\n"


# ==========================================
# Phase 2: Check & Install C++ Runtime
# ==========================================
echo -e "${YELLOW}=== Phase 2: Checking ANTLR4 C++ Runtime ===${NC}"
if [ -d "/usr/local/include/antlr4-runtime" ] && [ -f "/usr/local/lib/libantlr4-runtime.a" -o -f "/usr/local/lib/libantlr4-runtime.so" ]; then
    echo -e "${GREEN}✓ ANTLR4 C++ Runtime is already installed. Skipping compilation.${NC}\n"
else
    echo -e "${YELLOW}ANTLR4 C++ Runtime not found. Compiling from source...${NC}"
    
    # Run in /tmp to keep user folders clean
    TEMP_BUILD_DIR=$(mktemp -d)
    cd "$TEMP_BUILD_DIR"
    
    wget -q https://www.antlr.org/download/antlr4-cpp-runtime-4.13.2-source.zip
    unzip -q antlr4-cpp-runtime-4.13.2-source.zip -d antlr4-runtime-src
    cd antlr4-runtime-src
    
    mkdir build && cd build
    cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ..
    make -j$(nproc)
    
    sudo make install
    sudo ldconfig
    
    # Clean up temp files
    rm -rf "$TEMP_BUILD_DIR"
    echo -e "${GREEN}✓ ANTLR4 C++ Runtime compiled and installed successfully.${NC}\n"
fi

# Go back to the project directory
cd "$PROJECT_DIR"


# ==========================================
# Phase 3: Setting Up Virtual Environment
# ==========================================
echo -e "${YELLOW}=== Phase 3: Setting Up Python Virtual Environment ===${NC}"
if [ -d "venv" ]; then
    echo "Existing 'venv' directory found. Activating..."
    source venv/bin/activate
elif [ -d ".venv" ]; then
    echo "Existing '.venv' directory found. Activating..."
    source .venv/bin/activate
else
    echo "Creating a new virtual environment 'venv'..."
    python3 -m venv venv
    source venv/bin/activate
fi

# Install/Upgrade pip and antlr4-tools
echo "Installing antlr4-tools..."
pip install --upgrade pip
pip install antlr4-tools
echo -e "${GREEN}✓ Virtual environment active and tools installed.${NC}\n"


# ==========================================
# Phase 4: Safe Verification
# ==========================================
echo -e "${YELLOW}=== Phase 4: Verifying Installation ===${NC}"

# We run antlr4 with no args and grab its header version line.
# We temporarily disable 'set -e' because running antlr4 with no args or invalid args returns a non-zero exit code.
set +e
ANTLR_OUTPUT=$(antlr4 2>&1 | head -n 1)
set -e

if [[ "$ANTLR_OUTPUT" == *"ANTLR Parser Generator"* ]]; then
    echo -e "${GREEN}✓ Verification Successful: $ANTLR_OUTPUT${NC}"
else
    echo -e "${YELLOW}⚠ Verification Warning: could not parse version line, but command is installed.${NC}"
fi

# Make run-script executable if it exists in the folder
if [ -f "run-script.sh" ]; then
    chmod +x run-script.sh
fi

echo -e "\n${GREEN}===================================================${NC}"
echo -e "${GREEN} Setup Complete! ${NC}"
echo -e " To run your compiler in this project terminal:"
echo -e " 1. Make sure your virtual environment is active: ${YELLOW}source venv/bin/activate${NC}"
echo -e " 2. Run your compiler script: ${YELLOW}./run-script.sh input.c${NC}"
echo -e "${GREEN}===================================================${NC}"