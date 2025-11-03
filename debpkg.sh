#!/bin/bash
### debpkg.sh
###  by darkQ
###
VERSION=1.0
SUBVER=$(date "+%Y %j" | awk '{printf("%02d%03d\n",$(1)-2000,$2);}')
PKGNAME=cbcp
FILES="cbcp cbps"
DESCRIPTION="stdin to X11 clipboard and X11 clipboard to stdout"
DEBPATH=${PKGNAME}_${VERSION}-${SUBVER}
BINPATH=/usr/bin
RELBINP=${DEBPATH}${BINPATH}

if ! test -x /usr/bin/dpkg-deb
then
 exit 0
fi

rm -rf ${DEBPATH} 2>/dev/null

mkdir -p ${DEBPATH}/DEBIAN 2>/dev/null
mkdir -p ${RELBINP} 2>/dev/null

for i in $FILES
do
 cp $i ${RELBINP}/
 chmod 755 ${RELBINP}/$i
done

cat >${DEBPATH}/DEBIAN/control << EOF
Package: ${PKGNAME}
Version: ${VERSION}-${SUBVER}
Section: base
Priority: optional
Architecture: all
Maintainer: darkQ
Description: ${DESCRIPTION}
EOF

cat >${DEBPATH}/DEBIAN/postinst <<EOF
EOF

cat >${DEBPATH}/DEBIAN/prerm <<EOF
EOF

chmod 755 ${DEBPATH}/DEBIAN/postinst
chmod 755 ${DEBPATH}/DEBIAN/prerm

dpkg-deb --build $DEBPATH

rm -rf ${DEBPATH} 2>/dev/null
