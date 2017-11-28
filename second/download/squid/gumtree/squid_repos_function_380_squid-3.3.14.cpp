static int
name_cmp(const void *a, const void *b)
{
    const char * const *A = static_cast<const char * const *>(a);
    const char * const *B = static_cast<const char * const *>(b);
    return strcasecmp(*A, *B);
}