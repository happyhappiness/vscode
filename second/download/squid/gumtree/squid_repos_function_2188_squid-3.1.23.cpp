void
MemObject::setNoDelay(bool const newValue)
{
#if DELAY_POOLS

    for (dlink_node *node = clients.head; node; node = node->next) {
        store_client *sc = (store_client *) node->data;
        sc->delayId.setNoDelay(newValue);
    }

#endif
}