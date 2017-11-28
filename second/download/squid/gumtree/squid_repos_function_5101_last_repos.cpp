static int
rev_int_sort(const void *A, const void *B)
{
    const int *i1 = (const int *)A;
    const int *i2 = (const int *)B;
    return *i2 - *i1;
}