#!/bin/sh
# Script to install my configuration of dwm
# https://github.com/jtbx/dwm

set -e

# Functions

doNothing()
{
	printf ""
}

detectDistro()
{
	DISTRO=unix
	[ -e /bin/apt    ] && [ -e /bin/dpkg ] && DISTRO="debian"
	[ -e /bin/dnf    ] && [ -e /bin/rpm  ] && DISTRO="redhat"
	[ -e /bin/zypper ] && [ -e /bin/rpm  ] && DISTRO="suse"
	[ -e /bin/pacman ] && DISTRO="arch"
}

msg_check()
{
	TEXT=$1
	printf "\t\033[32;1m✓\033[0m \033[1m$TEXT\033[0m\n"
}

msg1()
{
	TEXT=$1
	printf "\t\033[32;1m*\033[0m \033[1m$TEXT\033[0m\n"
}

msg2()
{
	TEXT=$1
	printf "\t\033[34;1m*\033[0m \033[1m$TEXT\033[0m\n"
}

error()
{
	TEXT=$1
	printf "\t\033[31;1m*\033[0m \033[1m$TEXT\033[0m\n"
}

inputInto()
{
	printf "\t\033[34;1m->\033[0m"
	read -p " " $1
}

enterPrompt()
{
	printf "\t\033[34;1m>\033[0;1m Press Enter to begin \033[34;1m<\033[0m"
	read -p "" tempvar
}

confirmation()
{
	msg2 $1
	printf "\t\033[34;1m->\033[0m"
	read -p " " confirmChoice
	case $confirmChoice in
		y)
			doNothing
			;;
		Y)
			doNothing
			;;
		n)
			doNothing
			;;
		N)
			doNothing
			;;
		*)
			error "Invalid choice. Exiting..." ; exit 1
			;;
	esac
}

compile_rofi_emoji()
{
	confirmation "rofi-emoji will compile now. If you don't want the emoji picker, you can skip this step. Continue? (Y/N)"
	case $confirmChoice in
		y)
			git clone https://github.com/Mange/rofi-emoji
			cd rofi-emoji
			autoreconf -i
			mkdir build
			cd build/
			../configure
			make
			make install
			cd ../..
			;;
		Y)
			git clone https://github.com/Mange/rofi-emoji
			cd rofi-emoji
			autoreconf -i
			mkdir build
			cd build/
			../configure
			make
			make install
			cd ../..
			;;
		n)
			msg2 "Skipping compilation of rofi-emoji."
			;;
		N)
			msg2 "Skipping compilation of rofi-emoji."
			;;
	esac


}

# End functions

# Check if running as root
[ $USER != "root" ] && error "Authentication failed. Try running the script as sudo." && exit 1

# Check if Makefile is present
if [ -e Makefile ];
	then doNothing;
	else error "Makefile is not present. To fix this, re-clone the repository." && exit 1
fi

# Begin
clear
msg1 "dwm Installation Script\n\t  https://github.com/jtbx/dwm\n"
enterPrompt

# Cloning repository
msg1 "Cloning jtbx/dwm..."
dwm_clone_folder="/tmp/jtbx_dwm"
rm -rf $dwm_clone_folder
git clone https://github.com/jtbx/dwm $dwm_clone_folder

# Dependencies & compiling rofi-emoji if not on Arch
msg1 "Detecting distribution..."
detectDistro
msg2 "Detected distribution: $DISTRO"
msg1 "Installing dependencies..."
[ $DISTRO = arch   ] && pacman -Sy ttf-jetbrains-mono rofi rofi-emoji --noconfirm
[ $DISTRO = redhat ] && dnf install -y jetbrains-mono-fonts rofi rofi-devel autoconf automake libtool && compile_rofi_emoji
[ $DISTRO = suse   ] && zypper install autoconf automake libtool && rpm -i https://kojipkgs.fedoraproject.org//packages/jetbrains-mono-fonts/1.0.4/5.fc33/noarch/jetbrains-mono-fonts-all-1.0.4-5.fc33.noarch.rpm https://kojipkgs.fedoraproject.org//packages/rofi/1.7.2/1.fc35/x86_64/rofi-1.7.2-1.fc35.x86_64.rpm https://kojipkgs.fedoraproject.org//packages/rofi/1.7.2/1.fc35/x86_64/rofi-devel-1.7.2-1.fc35.x86_64.rpm && compile_rofi_emoji
[ $DISTRO = debian ] && apt install -yy fonts-jetbrains-mono rofi rofi-dev autoconf automake libtool-bin libtool && compile_rofi_emoji

# Compiling dwm
msg1 "Starting compilation of dwm..."
msg2 "Patches:\n\t  fullgaps\n\t  barpadding\n\t  hide_vacant_tags\n\t  swallow"
cd $dwm_clone_folder
sleep 1
make clean install

msg_check "Installation completed."
