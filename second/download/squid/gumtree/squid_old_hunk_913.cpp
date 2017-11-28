    }

    /* Schedule read reply. */
    AsyncCall::Pointer call =  commCbCall(5,5, "gopherReadReply",
                                          CommIoCbPtrFun(gopherReadReply, gopherState));
    entry->delayAwareRead(conn, gopherState->replybuf, BUFSIZ, call);

    if (buf)
        memFree(buf, MEM_4K_BUF);   /* Allocated by gopherSendRequest. */
}

/**
 \ingroup ServerProtocolGopherInternal
 * This will be called when connect completes. Write request.
 */
static void
gopherSendRequest(int fd, void *data)
{
    GopherStateData *gopherState = (GopherStateData *)data;
    char *buf = (char *)memAllocate(MEM_4K_BUF);

    if (gopherState->type_id == GOPHER_CSO) {
        const char *t = strchr(gopherState->request, '?');

        if (t != NULL)
            ++t;        /* skip the ? */
        else
            t = "";

        snprintf(buf, 4096, "query %s\r\nquit\r\n", t);
    } else if (gopherState->type_id == GOPHER_INDEX) {
        char *t = strchr(gopherState->request, '?');

        if (t != NULL)
            *t = '\t';

        snprintf(buf, 4096, "%s\r\n", gopherState->request);
    } else {
        snprintf(buf, 4096, "%s\r\n", gopherState->request);
    }

    debugs(10, 5, HERE << gopherState->serverConn);
    AsyncCall::Pointer call = commCbCall(5,5, "gopherSendComplete",
                                         CommIoCbPtrFun(gopherSendComplete, gopherState));
    Comm::Write(gopherState->serverConn, buf, strlen(buf), call, NULL);

    gopherState->entry->makePublic();
}

/// \ingroup ServerProtocolGopherInternal
CBDATA_TYPE(GopherStateData);
