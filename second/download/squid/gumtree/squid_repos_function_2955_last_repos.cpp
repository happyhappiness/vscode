void
clientReplyContext::sendMoreData (StoreIOBuffer result)
{
    if (deleting)
        return;

    StoreEntry *entry = http->storeEntry();

    if (ConnStateData * conn = http->getConn()) {
        if (!conn->isOpen()) {
            debugs(33,3, "not sending more data to closing connection " << conn->clientConnection);
            return;
        }
        if (conn->pinning.zeroReply) {
            debugs(33,3, "not sending more data after a pinned zero reply " << conn->clientConnection);
            return;
        }

        if (reqofs==0 && !http->logType.isTcpHit()) {
            if (Ip::Qos::TheConfig.isHitTosActive()) {
                Ip::Qos::doTosLocalMiss(conn->clientConnection, http->request->hier.code);
            }
            if (Ip::Qos::TheConfig.isHitNfmarkActive()) {
                Ip::Qos::doNfmarkLocalMiss(conn->clientConnection, http->request->hier.code);
            }
        }

        debugs(88, 5, conn->clientConnection <<
               " '" << entry->url() << "'" <<
               " out.offset=" << http->out.offset);
    }

    char *buf = next()->readBuffer.data;

    if (buf != result.data) {
        /* we've got to copy some data */
        assert(result.length <= next()->readBuffer.length);
        memcpy(buf, result.data, result.length);
    }

    /* We've got the final data to start pushing... */
    flags.storelogiccomplete = 1;

    reqofs += result.length;

    assert(reqofs <= HTTP_REQBUF_SZ || flags.headersSent);

    assert(http->request != NULL);

    /* ESI TODO: remove this assert once everything is stable */
    assert(http->client_stream.head->data
           && cbdataReferenceValid(http->client_stream.head->data));

    makeThisHead();

    debugs(88, 5, "clientReplyContext::sendMoreData: " << http->uri << ", " <<
           reqofs << " bytes (" << result.length <<
           " new bytes)");

    /* update size of the request */
    reqsize = reqofs;

    if (errorInStream(result, reqofs)) {
        sendStreamError(result);
        return;
    }

    if (flags.headersSent) {
        pushStreamData (result, buf);
        return;
    }

    cloneReply();

#if USE_DELAY_POOLS
    if (sc)
        sc->setDelayId(DelayId::DelayClient(http,reply));
#endif

    /* handle headers */

    if (Config.onoff.log_mime_hdrs) {
        size_t k;

        if ((k = headersEnd(buf, reqofs))) {
            safe_free(http->al->headers.reply);
            http->al->headers.reply = (char *)xcalloc(k + 1, 1);
            xstrncpy(http->al->headers.reply, buf, k);
        }
    }

    holdingBuffer = result;
    processReplyAccess();
    return;
}