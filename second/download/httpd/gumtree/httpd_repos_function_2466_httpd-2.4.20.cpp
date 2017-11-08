static apr_int32_t ceil_power_of_2(apr_int32_t n)
{
    if (n <= 2) return 2;
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return ++n;
}