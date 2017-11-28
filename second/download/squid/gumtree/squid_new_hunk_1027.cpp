        debugs(88, 3, "clientBuildReplyHeader: bumped reply forces close");
        request->flags.proxyKeepalive = false;
    } else if (request->pinnedConnection() && !reply->persistent()) {
        // The peer wants to close the pinned connection
        debugs(88, 3, "pinned reply forces close");
        request->flags.proxyKeepalive = false;
    } else if (http->getConn()) {
        ConnStateData * conn = http->getConn();
        if (!Comm::IsConnOpen(conn->port->listenConn)) {
            // The listening port closed because of a reconfigure
            debugs(88, 3, "listening port closed");
            request->flags.proxyKeepalive = false;
        }
    }

    // Decide if we send chunked reply
    if (maySendChunkedReply && reply->bodySize(request->method) < 0) {
        debugs(88, 3, "clientBuildReplyHeader: chunked reply");
        request->flags.chunkedReply = true;
        hdr->putStr(Http::HdrType::TRANSFER_ENCODING, "chunked");
    }

    hdr->addVia(reply->sline.version);

    /* Signal keep-alive or close explicitly */
    hdr->putStr(Http::HdrType::CONNECTION, request->flags.proxyKeepalive ? "keep-alive" : "close");

#if ADD_X_REQUEST_URI
    /*
     * Knowing the URI of the request is useful when debugging persistent
     * connections in a client; we cannot guarantee the order of http headers,
     * but X-Request-URI is likely to be the very last header to ease use from a
     * debugger [hdr->entries.count-1].
     */
    hdr->putStr(Http::HdrType::X_REQUEST_URI,
                http->memOjbect()->url ? http->memObject()->url : http->uri);

#endif

    /* Surrogate-Control requires Surrogate-Capability from upstream to pass on */
    if ( hdr->has(Http::HdrType::SURROGATE_CONTROL) ) {
        if (!request->header.has(Http::HdrType::SURROGATE_CAPABILITY)) {
            hdr->delById(Http::HdrType::SURROGATE_CONTROL);
        }
        /* TODO: else case: drop any controls intended specifically for our surrogate ID */
    }

    httpHdrMangleList(hdr, request, http->al, ROR_REPLY);
}

void
clientReplyContext::cloneReply()
{
    assert(reply == NULL);

    reply = http->storeEntry()->getReply()->clone();
    HTTPMSGLOCK(reply);

    if (reply->sline.protocol == AnyP::PROTO_HTTP) {
        /* RFC 2616 requires us to advertise our version (but only on real HTTP traffic) */
        reply->sline.version = Http::ProtocolVersion();
    }

    /* do header conversions */
    buildReplyHeader();
}

