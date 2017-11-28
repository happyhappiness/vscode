DelayId
MemObject::mostBytesAllowed() const
{
    int j;
    int jmax = -1;
    DelayId result;

    for (dlink_node *node = clients.head; node; node = node->next) {
        store_client *sc = (store_client *) node->data;
#if 0
        /* This test is invalid because the client may be writing data
         * and thus will want data immediately.
         * If we include the test, there is a race condition when too much
         * data is read - if all sc's are writing when a read is scheduled.
         * XXX: fixme.
         */

        if (!sc->callbackPending())
            /* not waiting for more data */
            continue;

#endif

        j = sc->delayId.bytesWanted(0, sc->copyInto.length);

        if (j > jmax) {
            jmax = j;
            result = sc->delayId;
        }
    }

    return result;
}