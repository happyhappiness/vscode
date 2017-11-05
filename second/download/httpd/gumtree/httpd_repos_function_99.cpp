static void putline(apr_file_t *f, char *l)
{
    int x;

    for (x = 0; l[x]; x++)
        apr_file_putc(l[x], f);
}