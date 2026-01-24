# Setup Instructions

This repository contains projects for learning ethical hacking from scratch. Follow these instructions to set up your environment.

## System Requirements

- Linux-based OS (Ubuntu 20.04+ recommended) or WSL2 on Windows
- At least 4GB RAM
- 10GB free disk space
- Root/sudo access for some projects

## Required Software

### Basic Tools
```bash
# Update package manager
sudo apt update

# Install build essentials
sudo apt install -y build-essential gcc g++ make

# Install debugging tools
sudo apt install -y gdb valgrind

# Install network tools
sudo apt install -y netcat tcpdump wireshark nmap

# Install assembly tools
sudo apt install -y nasm yasm

# Install Python
sudo apt install -y python3 python3-pip

# Install git
sudo apt install -y git
```

### Optional but Recommended
```bash
# GDB enhancements
pip3 install pwntools

# Install GEF (GDB Enhanced Features)
bash -c "$(curl -fsSL https://gef.blah.cat/sh)"

# Or install PEDA
git clone https://github.com/longld/peda.git ~/peda
echo "source ~/peda/peda.py" >> ~/.gdbinit
```

## Verification

After installation, verify everything is working:

```bash
# Check GCC
gcc --version

# Check NASM
nasm -version

# Check Python
python3 --version

# Check GDB
gdb --version
```

## Project Setup

Clone this repository:
```bash
git clone https://github.com/alektebel/ethical-hacking.git
cd ethical-hacking
```

## Testing the Setup

### Test Level 0 - C Programming
```bash
cd level-0-fundamentals/project-0.1-c-basics
make
./memory_basics
```

### Test Level 0 - Assembly (requires NASM)
```bash
cd level-0-fundamentals/project-0.3-assembly-intro
make hello
./hello
```

### Test Level 0 - Socket Programming
```bash
cd level-0-fundamentals/project-0.2-socket-programming
make
# Terminal 1:
./echo_server
# Terminal 2:
./echo_client localhost
```

## Virtual Machine Setup (Recommended)

For safety, it's recommended to use a virtual machine:

1. Install VirtualBox or VMware
2. Download Ubuntu 22.04 LTS
3. Create a VM with 4GB RAM and 20GB disk
4. Install the required software
5. Take a snapshot before starting projects

## Network Testing Environment

For network-related projects, consider:

1. **Local Only**: Use 127.0.0.1 (localhost) for initial testing
2. **VM Network**: Set up a host-only network between VMs
3. **Isolated Network**: Use a separate physical network isolated from the internet

## Troubleshooting

### Permission Denied for Raw Sockets
```bash
# Some projects need raw socket access
sudo setcap cap_net_raw+ep ./program_name
# Or run with sudo
sudo ./program_name
```

### GCC Warnings
The educational programs intentionally contain vulnerabilities and will produce warnings. This is expected.

### Assembly Won't Compile
Make sure NASM is installed:
```bash
sudo apt install nasm
```

## Security Notes

⚠️ **Important**: Never run these programs on production systems or networks you don't own.

- Use virtual machines
- Create isolated networks
- Get permission before testing on any network
- Understand your local laws regarding security testing

## Support

If you encounter issues:
1. Check the README in each project folder
2. Search for the error message
3. Open an issue on GitHub with details about your environment

## Next Steps

Once setup is complete, start with Level 0: Fundamentals!

```bash
cd level-0-fundamentals
cat README.md
```
