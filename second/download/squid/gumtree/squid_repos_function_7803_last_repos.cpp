static void
xor(char *out, char *in1, char *in2, int n)
{
    int i;
    for (i = 0; i < n; i++)
        out[i] = in1[i] ^ in2[i];
}