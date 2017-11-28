void
hash_last(hash_table * hid)
{
    assert(hid != NULL);
    hid->next = NULL;
    hid->current_slot = 0;
}