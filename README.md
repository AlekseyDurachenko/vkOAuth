vkOAuth
=======

VKontakte application authorization utility.

Homepage: http://alekseydurachenko.github.io/vkoauth/

Build && Install
----------------

```bash
lrelease vkoauth.pro
qmake
make -f Makefile.Release
make install
```

Build linux portable version
----------------------------

```bash
lrelease vkoauth.pro
qmake "DEFINES += APP_PORTABLE"
make -f Makefile.Release
make INSTALL_ROOT=`pwd`/portable-build install
```
