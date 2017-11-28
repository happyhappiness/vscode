void
print_fastmap(fastmap)
char *fastmap;
{
    unsigned was_a_range = 0;
    unsigned i = 0;

    while (i < (1 << BYTEWIDTH)) {
        if (fastmap[i++]) {
            was_a_range = 0;
            printchar(i - 1);
            while (i < (1 << BYTEWIDTH) && fastmap[i]) {
                was_a_range = 1;
                i++;
            }
            if (was_a_range) {
                printf("-");
                printchar(i - 1);
            }
        }
    }
    putchar('\n');
}