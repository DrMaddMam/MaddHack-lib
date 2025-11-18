nasm -f elf64 -o $1.o $1.asm -O0 -s
if [ $? -eq 0 ]; then
    ld $1.o -o $1
    if [ $1 -eq 0 ]; then
        rm $1.o
    else
        echo "Failed linking! $?"
    fi
else
    echo "Failed NASM! $?"
fi
