set -e
SCREEN=1280x800
pkill Xephyr 2>/dev/null || true
Xephyr -br -ac -noreset -screen $SCREEN :1 &
XEPHYR_PID=$!
sleep 1
DISPLAY=:1 ./cans-dwm &

# optional
DISPLAY=:1 kitty &

wait $XEPHYR_PID