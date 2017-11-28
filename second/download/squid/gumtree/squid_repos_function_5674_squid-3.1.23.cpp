void
hash_first(hash_table * hid)
{
    assert(NULL == hid->next);
    hid->current_slot = 0;
    hid->next = hid->buckets[hid->current_slot];
    if (NULL == hid->next)
        hash_next_bucket(hid);
}