        reply->setHeaders(Http::scPartialContent, "Gatewaying", mime_type, theSize - getCurrentOffset(), mdtm, -2);
        httpHeaderAddContRange(&reply->header, range_spec, theSize);
    }

    /* additional info */
    if (mime_enc)
        reply->header.putStr(HDR_CONTENT_ENCODING, mime_enc);

    setVirginReply(reply);
    adaptOrFinalizeReply();
}

void
Ftp::Gateway::haveParsedReplyHeaders()
