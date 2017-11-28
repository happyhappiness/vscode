
    assert(entry->isEmpty());
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);

    HttpReply *reply = new HttpReply;
    entry->buffer();
    reply->setHeaders(HTTP_OK, "Gatewaying", mime_type, -1, -1, -2);
    if (mime_enc)
        reply->header.putStr(HDR_CONTENT_ENCODING, mime_enc);

    entry->replaceHttpReply(reply);
}

