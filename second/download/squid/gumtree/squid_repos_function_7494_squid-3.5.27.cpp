void
print_oid_nums(oid * O, int len)
{
    int x;

    for (x = 0; x < len; x++)
        printf(".%u", O[x]);
}