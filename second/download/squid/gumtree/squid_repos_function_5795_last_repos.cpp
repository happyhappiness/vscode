static void
closeFds(FILE *a, FILE *b, FILE *c, FILE *d)
{
    if (a)
        fclose(a);
    if (b)
        fclose(b);
    if (c)
        fclose(c);
    if (d)
        fclose(d);
}