run: clean compile
    clear && ./main

compile:
    gcc *.c -o main

clean:
    rm -f main
