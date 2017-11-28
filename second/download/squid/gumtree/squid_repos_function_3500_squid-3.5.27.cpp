void
clientReplyContext::doGetMoreData()
{
    /* We still have to do store logic processing - vary, cache hit etc */
    if (http->storeEntry() != NULL) {
        /* someone found the object in the cache for us */
        StoreIOBuffer localTempBuffer;

        http->storeEntry()->lock("clientReplyContext::doGetMoreData");

        MemObject *mem_obj = http->storeEntry()->makeMemObject();
        if (!mem_obj->hasUris()) {
            /*
             * This if-block exists because we don't want to clobber
             * a preexiting mem_obj->method value if the mem_obj
             * already exists.  For example, when a HEAD request
             * is a cache hit for a GET response, we want to keep
             * the method as GET.
             */
            mem_obj->setUris(storeId(), http->log_uri, http->request->method);
            /**
             * Here we can see if the object was
             * created using URL or alternative StoreID from helper.
             */
            debugs(88, 3, "storeId: " << http->storeEntry()->mem_obj->storeId());
        }

        sc = storeClientListAdd(http->storeEntry(), this);
#if USE_DELAY_POOLS
        sc->setDelayId(DelayId::DelayClient(http));
#endif

        assert(http->logType == LOG_TCP_HIT);
        reqofs = 0;
        /* guarantee nothing has been sent yet! */
        assert(http->out.size == 0);
        assert(http->out.offset == 0);

        if (Ip::Qos::TheConfig.isHitTosActive()) {
            Ip::Qos::doTosLocalHit(http->getConn()->clientConnection);
        }

        if (Ip::Qos::TheConfig.isHitNfmarkActive()) {
            Ip::Qos::doNfmarkLocalHit(http->getConn()->clientConnection);
        }

        localTempBuffer.offset = reqofs;
        localTempBuffer.length = getNextNode()->readBuffer.length;
        localTempBuffer.data = getNextNode()->readBuffer.data;
        storeClientCopy(sc, http->storeEntry(), localTempBuffer, CacheHit, this);
    } else {
        /* MISS CASE, http->logType is already set! */
        processMiss();
    }
}