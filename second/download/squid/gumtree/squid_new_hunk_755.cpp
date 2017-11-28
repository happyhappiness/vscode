
    default:
        fatal("Hit unreachable code in clientWriteComplete\n");
    }
}

ClientSocketContext *
ConnStateData::abortRequestParsing(const char *const uri)
{
    ClientHttpRequest *http = new ClientHttpRequest(this);
    http->req_sz = in.buf.length();
    http->uri = xstrdup(uri);
    setLogUri (http, uri);
    ClientSocketContext *context = new ClientSocketContext(clientConnection, http);
    StoreIOBuffer tempBuffer;
    tempBuffer.data = context->reqbuf;
    tempBuffer.length = HTTP_REQBUF_SZ;
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, new clientReplyContext(http), clientSocketRecipient,
                     clientSocketDetach, context, tempBuffer);
    return context;
}

void
ConnStateData::startShutdown()
{
    // RegisteredRunner API callback - Squid has been shut down

    // if connection is idle terminate it now,
    // otherwise wait for grace period to end
    if (getConcurrentRequestCount() == 0)
        endingShutdown();
}

void
ConnStateData::endingShutdown()
{
    // RegisteredRunner API callback - Squid shutdown grace period is over

    // force the client connection to close immediately
    // swanSong() in the close handler will cleanup.
    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();

    // deregister now to ensure finalShutdown() does not kill us prematurely.
    // fd_table purge will cleanup if close handler was not fast enough.
    DeregisterRunner(this);
}

char *
skipLeadingSpace(char *aString)
{
    char *result = aString;

    while (xisspace(*aString))
