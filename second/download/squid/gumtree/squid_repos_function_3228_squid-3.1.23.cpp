void
PconnPool::unlinkList(IdleConnList *list) const
{
    hash_remove_link(table, &list->hash);
}