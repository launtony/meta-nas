DESCRIPTION = "A web file-explorer"
SECTION = "network"
HOMEPAGE = "https://github.com/simogeo/Filemanager"

RDEPENDS_${PN} = "lighttpd php-cgi python"

SRC_URI = "https://github.com/simogeo/Filemanager/archive/v${PV}.tar.gz"
SRC_URI += "file://0001-Move-fromPython2.6toPython.patch"
SRC_URI += "file://0002-Desactivate-php-errors.patch"

SRC_URI += "file://filemanager.config.js"

S = "${WORKDIR}/Filemanager-${PV}"

do_compile[noexec] = "1"

do_configure () {
	sed -i -e "s:@FILE_PATH@:${DOWNLOAD_DIR_TRANSMISSION}:" ${WORKDIR}/filemanager.config.js
}

do_install () {
    # Do it carefully
    [ -d "${S}" ] || exit 1
    mkdir -p ${D}/www/pages/${PN} || exit 1
    cd ${S} || exit 1
    tar --no-same-owner --exclude='./patches' --exclude='./.pc' -cpf - . \
        | tar --no-same-owner -xpf - -C ${D}/www/pages/${PN}
    cp ${WORKDIR}/filemanager.config.js ${D}/www/pages/${PN}/scripts/
}

FILES_${PN} = "/"
