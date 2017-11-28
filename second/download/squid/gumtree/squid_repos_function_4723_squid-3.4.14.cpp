static void
asHandleReply(void *data, StoreIOBuffer result)
{
    ASState *asState = (ASState *)data;
    StoreEntry *e = asState->entry;
    char *s;
    char *t;
    char *buf = asState->reqbuf;
    int leftoversz = -1;

    debugs(53, 3, "asHandleReply: Called with size=" << (unsigned int)result.length);
    debugs(53, 3, "asHandleReply: buffer='" << buf << "'");

    /* First figure out whether we should abort the request */

    if (EBIT_TEST(e->flags, ENTRY_ABORTED)) {
        asStateFree(asState);
        return;
    }

    if (result.length == 0 && asState->dataRead) {
        debugs(53, 3, "asHandleReply: Done: " << e->url()  );
        asStateFree(asState);
        return;
    } else if (result.flags.error) {
        debugs(53, DBG_IMPORTANT, "asHandleReply: Called with Error set and size=" << (unsigned int) result.length);
        asStateFree(asState);
        return;
    } else if (e->getReply()->sline.status() != Http::scOkay) {
        debugs(53, DBG_IMPORTANT, "WARNING: AS " << asState->as_number << " whois request failed");
        asStateFree(asState);
        return;
    }

    /*
     * Next, attempt to parse our request
     * Remembering that the actual buffer size is retsize + reqofs!
     */
    s = buf;

    while ((size_t)(s - buf) < result.length + asState->reqofs && *s != '\0') {
        while (*s && xisspace(*s))
            ++s;

        for (t = s; *t; ++t) {
            if (xisspace(*t))
                break;
        }

        if (*t == '\0') {
            /* oof, word should continue on next block */
            break;
        }

        *t = '\0';
        debugs(53, 3, "asHandleReply: AS# " << s << " (" << asState->as_number << ")");
        asnAddNet(s, asState->as_number);
        s = t + 1;
        asState->dataRead = 1;
    }

    /*
     * Next, grab the end of the 'valid data' in the buffer, and figure
     * out how much data is left in our buffer, which we need to keep
     * around for the next request
     */
    leftoversz = (asState->reqofs + result.length) - (s - buf);

    assert(leftoversz >= 0);

    /*
     * Next, copy the left over data, from s to s + leftoversz to the
     * beginning of the buffer
     */
    memmove(buf, s, leftoversz);

    /*
     * Next, update our offset and reqofs, and kick off a copy if required
     */
    asState->offset += result.length;

    asState->reqofs = leftoversz;

    debugs(53, 3, "asState->offset = " << asState->offset);

    if (e->store_status == STORE_PENDING) {
        debugs(53, 3, "asHandleReply: store_status == STORE_PENDING: " << e->url()  );
        StoreIOBuffer tempBuffer (AS_REQBUF_SZ - asState->reqofs,
                                  asState->offset,
                                  asState->reqbuf + asState->reqofs);
        storeClientCopy(asState->sc,
                        e,
                        tempBuffer,
                        asHandleReply,
                        asState);
    } else {
        StoreIOBuffer tempBuffer;
        debugs(53, 3, "asHandleReply: store complete, but data received " << e->url()  );
        tempBuffer.offset = asState->offset;
        tempBuffer.length = AS_REQBUF_SZ - asState->reqofs;
        tempBuffer.data = asState->reqbuf + asState->reqofs;
        storeClientCopy(asState->sc,
                        e,
                        tempBuffer,
                        asHandleReply,
                        asState);
    }
}