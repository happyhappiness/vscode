    }
    stoppedSending_ = error;

    if (!stoppedReceiving()) {
        if (const int64_t expecting = mayNeedToReadMoreBody()) {
            debugs(33, 5, HERE << "must still read " << expecting <<
                   " request body bytes with " << inBuf.length() << " unused");
            return; // wait for the request receiver to finish reading
        }
    }

    clientConnection->close();
}

void
ConnStateData::afterClientWrite(size_t size)
{
    if (pipeline.empty())
        return;

    auto ctx = pipeline.front();
    if (size) {
        statCounter.client_http.kbytes_out += size;
        if (ctx->http->logType.isTcpHit())
            statCounter.client_http.hit_kbytes_out += size;
    }
    ctx->writeComplete(size);
}

Http::Stream *
ConnStateData::abortRequestParsing(const char *const uri)
{
    ClientHttpRequest *http = new ClientHttpRequest(this);
    http->req_sz = inBuf.length();
    http->uri = xstrdup(uri);
    setLogUri (http, uri);
    auto *context = new Http::Stream(clientConnection, http);
    StoreIOBuffer tempBuffer;
    tempBuffer.data = context->reqbuf;
    tempBuffer.length = HTTP_REQBUF_SZ;
    clientStreamInit(&http->client_stream, clientGetMoreData, clientReplyDetach,
                     clientReplyStatus, new clientReplyContext(http), clientSocketRecipient,
                     clientSocketDetach, context, tempBuffer);
