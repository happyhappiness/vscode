static int iphash_compare(const void *a, const void *b)
{
    return (*(const int *) b - *(const int *) a);
}