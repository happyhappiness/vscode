void ZLIB_INTERNAL z_error (m)
    char *m;
{
    fprintf(stderr, "%s\n", m);
    exit(1);
}