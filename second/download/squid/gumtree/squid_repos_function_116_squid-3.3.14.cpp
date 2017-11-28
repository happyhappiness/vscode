void
my_hash_insert(hash_table * h, const char *k, memitem * item)
{
    memitem *l;
    assert(item->pool);
    assert(item->my_ptr);
    hash_insert(h, k, item);
}