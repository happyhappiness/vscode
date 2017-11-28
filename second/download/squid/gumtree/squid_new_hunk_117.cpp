     */
    hdr->putStr(HDR_X_REQUEST_URI,
                http->memOjbect()->url ? http->memObject()->url : http->uri);

#endif

    /* Surrogate-Control requires Surrogate-Capability from upstream to pass on */
    if ( hdr->has(HDR_SURROGATE_CONTROL) ) {
        if (!request->header.has(HDR_SURROGATE_CAPABILITY)) {
            hdr->delById(HDR_SURROGATE_CONTROL);
        }
        /* TODO: else case: drop any controls intended specifically for our surrogate ID */
    }

    httpHdrMangleList(hdr, request, ROR_REPLY);
}


void
clientReplyContext::cloneReply()
