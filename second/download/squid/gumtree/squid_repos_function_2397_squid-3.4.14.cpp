static store_client *
storeClientListSearch(const MemObject * mem, void *data)
{
    dlink_node *node;
    store_client *sc = NULL;

    for (node = mem->clients.head; node; node = node->next) {
        sc = node->data;

        if (sc->owner == data)
            return sc;
    }

    return NULL;
}