hash_link *
hash_get_bucket(hash_table * hid, unsigned int bucket)
{
    if (bucket >= hid->size)
        return NULL;
    return (hid->buckets[bucket]);
}