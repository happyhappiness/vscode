StoreEntry *
StoreSearchCoss::currentItem()
{
    if (!current)
        return NULL;

    return static_cast<StoreEntry *>( current->data );
}