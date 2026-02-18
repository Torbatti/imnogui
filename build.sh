mkdir -p build
mkdir -p local
gcc ./app-imnogui/src/app.c -o build/imnogui -ldl -lX11
