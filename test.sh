set -e
SCREEN=2000x1200
pkill Xephyr 2>/dev/null || true
Xephyr -br -ac -noreset -screen $SCREEN :1 &
XEPHYR_PID=$!
sleep 1
DISPLAY=:1 cans-dwm -debug &

wait $XEPHYR_PID