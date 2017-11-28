void
clientReplyContext::createStoreEntry(const HttpRequestMethod& m, RequestFlags reqFlags)
{
    assert(http != NULL);
    /*
     * For erroneous requests, we might not have a h->request,
     * so make a fake one.
     */

    if (http->request == NULL)
        http->request = HTTPMSGLOCK(new HttpRequest(m, AnyP::PROTO_NONE, null_string));

    StoreEntry *e = storeCreateEntry(http->uri, http->log_uri, reqFlags, m);

    sc = storeClientListAdd(e, this);

#if USE_DELAY_POOLS
    sc->setDelayId(DelayId::DelayClient(http));
#endif

    reqofs = 0;

    reqsize = 0;

    /* I don't think this is actually needed! -- adrian */
    /* http->reqbuf = http->norm_reqbuf; */
    //    assert(http->reqbuf == http->norm_reqbuf);
    /* The next line is illegal because we don't know if the client stream
     * buffers have been set up
     */
    //    storeClientCopy(http->sc, e, 0, HTTP_REQBUF_SZ, http->reqbuf,
    //        SendMoreData, this);
    /* So, we mark the store logic as complete */
    flags.storelogiccomplete = 1;

    /* and get the caller to request a read, from whereever they are */
    /* NOTE: after ANY data flows down the pipe, even one step,
     * this function CAN NOT be used to manage errors
     */
    http->storeEntry(e);
}