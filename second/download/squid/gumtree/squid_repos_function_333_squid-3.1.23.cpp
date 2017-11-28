static int
name_cmp(const void *a, const void *b)
{
    const char * const *A = a;
    const char * const *B = b;
    return strcasecmp(*A, *B);
}