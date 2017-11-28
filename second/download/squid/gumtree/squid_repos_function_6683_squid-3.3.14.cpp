void
hash_remove_link(hash_table * hid, hash_link * hl)
{
    assert(hl != NULL);
    int i = hid->hash(hl->key, hid->size);
    for (hash_link **P = &hid->buckets[i]; *P; P = &(*P)->next) {
        if (*P != hl)
            continue;
        *P = hl->next;
        if (hid->next == hl) {
            hid->next = hl->next;
            if (NULL == hid->next)
                hash_next_bucket(hid);
        }
        --hid->count;
        return;
    }
    assert(0);
}