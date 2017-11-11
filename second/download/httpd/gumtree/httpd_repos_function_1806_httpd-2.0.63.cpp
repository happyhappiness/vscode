static APR_INLINE unsigned hash_inaddr(unsigned key)
{
    key ^= (key >> 16);
    return ((key >> 8) ^ key) % IPHASH_TABLE_SIZE;
}