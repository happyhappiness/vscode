static void
permute(char *out, char *in, int *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
        out[i] = in[p[i] - 1];
}