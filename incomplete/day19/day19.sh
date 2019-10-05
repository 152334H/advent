#/bin/sh
gcc day19.c day.c
echo "part 1:" `./a.out $(stdbuf -o0 python day19.py 2>/dev/null|head -1)`
echo "part 2:" `./a.out $(stdbuf -o0 python day19.py 2>/dev/null|head -2|tail -1)`
