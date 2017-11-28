hash_link *
hash_next(hash_table * hid)
{
    hash_link *this = hid->next;
    if (NULL == this)
        return NULL;
    hid->next = this->next;
    if (NULL == hid->next)
        hash_next_bucket(hid);
    return this;
}