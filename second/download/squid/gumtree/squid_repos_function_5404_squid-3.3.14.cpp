static void
fvdbInit(void)
{
    via_table = hash_create((HASHCMP *) strcmp, 977, hash4);
    forw_table = hash_create((HASHCMP *) strcmp, 977, hash4);
}