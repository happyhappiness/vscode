static void
lshift(char *d, int count, int n)
{
    char out[64];
    int i;
    for (i = 0; i < n; i++)
        out[i] = d[(i + count) % n];
    for (i = 0; i < n; i++)
        d[i] = out[i];
}