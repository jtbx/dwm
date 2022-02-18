# Maintainer: Jeremy Baxter <jeremytbaxter@protonmail.com>
pkgname=dwm-jtbx
pkgver=r51.37ac25d
pkgrel=1
pkgdesc="Jeremy's build of dwm"
arch=(x86_64)
url="https://github.com/jtbx/dwm"
license=('MIT')
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'alacritty' 'ttf-jetbrains-mono' 'rofi' 'rofi-emoji' 'rofi-calc')
makedepends=('git' 'make' 'gcc')
provides=('dwm')
conflicts=('dwm' 'dwm-git' 'dwm-distrotube')
source=('dwm-jtbx::git://github.com/jtbx/dwm')
md5sums=('SKIP')

pkgver() {
	cd "dwm-jtbx"
	printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
	cd "dwm-jtbx"
	make
}

package() {
	cd "dwm-jtbx"
	sudo make install
}
