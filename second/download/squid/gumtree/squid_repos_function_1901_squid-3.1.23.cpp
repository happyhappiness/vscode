void
StoreSearchHashIndex::copyBucket()
{
    /* probably need to lock the store entries...
     * we copy them all to prevent races on the links. */
    debugs(47, 3, "StoreSearchHashIndex::copyBucket #" << bucket);
    assert (!entries.size());
    hash_link *link_ptr = NULL;
    hash_link *link_next = NULL;
    link_next = hash_get_bucket(store_table, bucket);

    while (NULL != (link_ptr = link_next)) {
        link_next = link_ptr->next;
        StoreEntry *e = (StoreEntry *) link_ptr;

        entries.push_back(e);
    }

    bucket++;
    debugs(47,3, "got entries: " << entries.size());
}