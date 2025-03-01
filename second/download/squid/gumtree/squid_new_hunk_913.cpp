    }

    /* Schedule read reply. */
    AsyncCall::Pointer call =  commCbCall(5,5, "gopherReadReply",
                                          CommIoCbPtrFun(gopherReadReply, gopherState));
    entry->delayAwareRead(conn, gopherState->replybuf, BUFSIZ, call);
}

/**
 \ingroup ServerProtocolGopherInternal
 * This will be called when connect completes. Write request.
 */
static void
gopherSendRequest(int fd, void *data)
{
    GopherStateData *gopherState = (GopherStateData *)data;
    MemBuf mb;
    mb.init();

    if (gopherState->type_id == GOPHER_CSO) {
        const char *t = strchr(gopherState->request, '?');

        if (t)
            ++t;        /* skip the ? */
        else
            t = "";

        mb.Printf("query %s\r\nquit", t);
    } else {
        if (gopherState->type_id == GOPHER_INDEX) {
            if (char *t = strchr(gopherState->request, '?'))
                *t = '\t';
        }
        mb.append(gopherState->request, strlen(gopherState->request));
    }
    mb.append("\r\n", 2);

    debugs(10, 5, gopherState->serverConn);
    AsyncCall::Pointer call = commCbCall(5,5, "gopherSendComplete",
                                         CommIoCbPtrFun(gopherSendComplete, gopherState));
    Comm::Write(gopherState->serverConn, &mb, call);

    gopherState->entry->makePublic();
}

/// \ingroup ServerProtocolGopherInternal
CBDATA_TYPE(GopherStateData);
