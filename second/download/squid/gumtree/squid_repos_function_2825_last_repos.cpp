void
PconnPool::unlinkList(IdleConnList *list)
{
    theCount -= list->count();
    assert(theCount >= 0);
    hash_remove_link(table, list);
}