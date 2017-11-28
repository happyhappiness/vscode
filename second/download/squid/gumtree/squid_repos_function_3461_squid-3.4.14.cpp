void
clientReplyContext::processReplyAccessResult(const allow_t &accessAllowed)
{
    debugs(88, 2, "The reply for " << RequestMethodStr(http->request->method)
           << " " << http->uri << " is " << accessAllowed << ", because it matched '"
           << (AclMatchedName ? AclMatchedName : "NO ACL's") << "'" );

    if (accessAllowed != ACCESS_ALLOWED) {
        ErrorState *err;
        err_type page_id;
        page_id = aclGetDenyInfoPage(&Config.denyInfoList, AclMatchedName, 1);

        http->logType = LOG_TCP_DENIED_REPLY;

        if (page_id == ERR_NONE)
            page_id = ERR_ACCESS_DENIED;

        Ip::Address tmp_noaddr;
        tmp_noaddr.setNoAddr();
        err = clientBuildError(page_id, Http::scForbidden, NULL,
                               http->getConn() != NULL ? http->getConn()->clientConnection->remote : tmp_noaddr,
                               http->request);

        removeClientStoreReference(&sc, http);

        HTTPMSGUNLOCK(reply);

        startError(err);

        return;
    }

    /* Ok, the reply is allowed, */
    http->loggingEntry(http->storeEntry());

    ssize_t body_size = reqofs - reply->hdr_sz;
    if (body_size < 0) {
        reqofs = reply->hdr_sz;
        body_size = 0;
    }

    debugs(88, 3, "clientReplyContext::sendMoreData: Appending " <<
           (int) body_size << " bytes after " << reply->hdr_sz <<
           " bytes of headers");

#if USE_SQUID_ESI

    if (http->flags.accel && reply->sline.status() != Http::scForbidden &&
            !alwaysAllowResponse(reply->sline.status()) &&
            esiEnableProcessing(reply)) {
        debugs(88, 2, "Enabling ESI processing for " << http->uri);
        clientStreamInsertHead(&http->client_stream, esiStreamRead,
                               esiProcessStream, esiStreamDetach, esiStreamStatus, NULL);
    }

#endif

    if (http->request->method == Http::METHOD_HEAD) {
        /* do not forward body for HEAD replies */
        body_size = 0;
        http->flags.done_copying = true;
        flags.complete = 1;
    }

    assert (!flags.headersSent);
    flags.headersSent = true;

    StoreIOBuffer localTempBuffer;
    char *buf = next()->readBuffer.data;
    char *body_buf = buf + reply->hdr_sz;

    //Server side may disable ranges under some circumstances.

    if ((!http->request->range))
        next()->readBuffer.offset = 0;

    body_buf -= next()->readBuffer.offset;

    if (next()->readBuffer.offset != 0) {
        if (next()->readBuffer.offset > body_size) {
            /* Can't use any of the body we received. send nothing */
            localTempBuffer.length = 0;
            localTempBuffer.data = NULL;
        } else {
            localTempBuffer.length = body_size - next()->readBuffer.offset;
            localTempBuffer.data = body_buf + next()->readBuffer.offset;
        }
    } else {
        localTempBuffer.length = body_size;
        localTempBuffer.data = body_buf;
    }

    /* TODO??: move the data in the buffer back by the request header size */
    clientStreamCallback((clientStreamNode *)http->client_stream.head->data,
                         http, reply, localTempBuffer);

    return;
}