ESIContext *
ESIContextNew (HttpReply *rep, clientStreamNode *thisNode, ClientHttpRequest *http)
{
    assert (rep);
    ESIContext *rv = new ESIContext;
    rv->rep = rep;
    rv->cbdataLocker = rv;

    if (esiAlwaysPassthrough(rep->sline.status())) {
        rv->flags.passthrough = 1;
    } else {
        /* remove specific headers for ESI to prevent
         * downstream cache confusion */
        HttpHeader *hdr = &rep->header;
        hdr->delById(Http::HdrType::ACCEPT_RANGES);
        hdr->delById(Http::HdrType::ETAG);
        hdr->delById(Http::HdrType::CONTENT_LENGTH);
        hdr->delById(Http::HdrType::CONTENT_MD5);
        rv->tree = new esiSequence (rv, true);
        rv->thisNode = thisNode;
        rv->http = http;
        rv->flags.clientwantsdata = 1;
        rv->varState = new ESIVarState (&http->request->header, http->uri);
        debugs(86, 5, "ESIContextNew: Client wants data (always created during reply cycle");
    }

    debugs(86, 5, "ESIContextNew: Create context " << rv);
    return rv;
}