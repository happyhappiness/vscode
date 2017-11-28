static void
fvdbClear(void)
{
    hashFreeItems(via_table, fvdbFreeEntry);
    hashFreeMemory(via_table);
    via_table = hash_create((HASHCMP *) strcmp, 977, hash4);
    hashFreeItems(forw_table, fvdbFreeEntry);
    hashFreeMemory(forw_table);
    forw_table = hash_create((HASHCMP *) strcmp, 977, hash4);
}