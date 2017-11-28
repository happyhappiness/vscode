void
hashFreeMemory(hash_table * hid)
{
    if (hid == NULL)
        return;
    if (hid->buckets)
        xfree(hid->buckets);
    xfree(hid);
}