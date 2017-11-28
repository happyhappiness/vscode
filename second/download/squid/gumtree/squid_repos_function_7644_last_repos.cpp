static void
hash_next_bucket(hash_table * hid)
{
    while (hid->next == NULL && ++hid->current_slot < hid->size)
        hid->next = hid->buckets[hid->current_slot];
}