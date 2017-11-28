void
clientReplyContext::sendMoreData (StoreIOBuffer result)
{
    if (deleting)
        return;

    StoreEntry *entry = http->storeEntry();

    ConnStateData * conn = http->getConn();

    int fd = conn != NULL ? conn->fd : -1;
    if (fd >= 0 && fd_table[fd].closing()) { // too late, our conn is closing
        // TODO: should we also quit when fd is negative?
        debugs(33,3, HERE << "not sending more data to a closing FD " << fd);
        return;
    }

    char *buf = next()->readBuffer.data;

    if (buf != result.data) {
        /* we've got to copy some data */
        assert(result.length <= next()->readBuffer.length);
        xmemcpy(buf, result.data, result.length);
    }

#if USE_ZPH_QOS
    if (reqofs==0 && !logTypeIsATcpHit(http->logType)) {
        assert(fd >= 0); // the beginning of this method implies fd may be -1
        int tos = 0;
        if (Config.zph.tos_sibling_hit && http->request->hier.code==SIBLING_HIT ) {
            tos = Config.zph.tos_sibling_hit;
            debugs(33, 2, "ZPH: Sibling Peer hit with hier.code=" << http->request->hier.code << ", TOS=" << tos);
        } else if (Config.zph.tos_parent_hit && http->request->hier.code==PARENT_HIT) {
            tos = Config.zph.tos_parent_hit;
            debugs(33, 2, "ZPH: Parent Peer hit with hier.code=" << http->request->hier.code << ", TOS=" << tos);
        } else if (Config.zph.preserve_miss_tos && Config.zph.preserve_miss_tos_mask) {
            tos = fd_table[fd].upstreamTOS & Config.zph.preserve_miss_tos_mask;
            debugs(33, 2, "ZPH: Preserving TOS on miss, TOS="<<tos);
        }
        comm_set_tos(fd,tos);
    }
#endif

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
    debugs(88, 5, "clientReplyContext::sendMoreData:"
           " FD " << fd <<
           " '" << entry->url() << "'" <<
           " out.offset=" << http->out.offset);

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

    /* handle headers */

    if (Config.onoff.log_mime_hdrs) {
        size_t k;

        if ((k = headersEnd(buf, reqofs))) {
            safe_free(http->al.headers.reply);
            http->al.headers.reply = (char *)xcalloc(k + 1, 1);
            xstrncpy(http->al.headers.reply, buf, k);
        }
    }

    holdingBuffer = result;
    processReplyAccess();
    return;
}