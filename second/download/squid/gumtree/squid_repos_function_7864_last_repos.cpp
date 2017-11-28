static char *
_tmpnam(void)
{
    static const char digits[] =
#if (L_tmpnam >= L_tmpmin + LONG_BIT / 4)
        "0123456789abcdef";
#define TMP_BASE    16
#else
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-";
#define TMP_BASE    64
#endif
    static unsigned long lastcount = 0;
    static char buffer[L_tmpnam + 1];
    char *s = buffer;
    unsigned long count = lastcount;
    pid_t pid = getpid();

    if (sizeof(_tmp) - 1 != lengthof_tmp)
        abort();        /* Consistency error. */

    for (;;) {
        register int i = L_tmpnam;
        register unsigned long c;
        register unsigned int p;

        /* Build filename. (the hard way) */
        s += i;
        *s = '\0';

        c = (count == TMP_MAX) ? 0 : ++count;
        do {
            *--s = digits[c % TMP_BASE];
            c /= TMP_BASE;
        } while (--i > L_tmpmin);

        p = (unsigned int) pid;
        do {
            *--s = digits[p % 10];
            p /= 10;
        } while (--i > lengthof_tmp);

        do {
            *--s = _tmp[--i];
        } while (i > 0);

        /* Check that the file doesn't exist. */
        if (access(s, 0) != 0)
            break;

        /* It exists; retry unless we tried them all. */
        if (count == lastcount) {
            s = NULL;
            break;
        }
    }

    lastcount = count;

    return s;
}