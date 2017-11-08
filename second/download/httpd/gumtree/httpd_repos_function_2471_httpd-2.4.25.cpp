static int cmp_puint64(const void *p1, const void *p2)
{
    const apr_uint64_t *pu1 = p1, *pu2 = p2;
    return (*pu1 > *pu2)? 1 : ((*pu1 == *pu2)? 0 : -1);
}