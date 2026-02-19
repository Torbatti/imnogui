mkdir -p build
mkdir -p local
# zig cc ./app-imnogui/src/app.c -o build/imnogui -g3 -ldl -lX11 -Ivendor-glad/v2.0.8
gcc ./app-imnogui/src/app.c -o build/imnogui -g3 -ldl -lX11 -Ivendor-glad/v2.0.8 -fsanitize=address
