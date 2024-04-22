set -e

: "${CC:=tcc}"
: "${CFLAGS:=-O2}"
task=${1:-"uxxd.exe"}

$CC $CFLAGS -DCC=\""$CC"\" -DCFLAGS=\""$CFLAGS"\" build.c -o build.exe
./build.exe $task && echo "ok" || echo "err"
