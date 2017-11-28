static int
fsCmp(const void *a, const void *b)
{
    const int *A = (const int *)a;
    const int *B = (const int *)b;
    return *A != *B;
}