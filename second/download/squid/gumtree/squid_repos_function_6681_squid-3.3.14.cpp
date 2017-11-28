hash_link *
hash_next(hash_table * hid)
{
    hash_link *p = hid->next;
    if (NULL == p)
        return NULL;
    hid->next = p->next;
    if (NULL == hid->next)
        hash_next_bucket(hid);
    return p;
}