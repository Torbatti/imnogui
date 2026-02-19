mkdir -p build
mkdir -p local
gcc ./app-imnogui/src/app.c -o build/imnogui -ldl -lX11 -Ivendor-glad/v2.0.8
