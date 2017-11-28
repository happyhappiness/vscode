void
Downloader::handleReply(clientStreamNode * node, ClientHttpRequest *http, HttpReply *reply, StoreIOBuffer receivedData)
{
    DownloaderContext::Pointer callerContext = dynamic_cast<DownloaderContext *>(node->data.getRaw());
    // TODO: remove the following check:
    assert(callerContext == context_);

    debugs(33, 4, "Received " << receivedData.length <<
           " object data, offset: " << receivedData.offset <<
           " error flag:" << receivedData.flags.error);

    const bool failed = receivedData.flags.error;
    if (failed) {
        callBack(Http::scInternalServerError);
        return;
    }

    const int64_t existingContent = reply ? reply->content_length : 0;
    const size_t maxSize = MaxObjectSize > SBuf::maxSize ? SBuf::maxSize : MaxObjectSize;
    const bool tooLarge = (existingContent > -1 && existingContent > static_cast<int64_t>(maxSize)) ||
                          (maxSize < object_.length()) ||
                          ((maxSize - object_.length()) < receivedData.length);

    if (tooLarge) {
        callBack(Http::scInternalServerError);
        return;
    }

    object_.append(receivedData.data, receivedData.length);
    http->out.size += receivedData.length;
    http->out.offset += receivedData.length;

    switch (clientStreamStatus(node, http)) {
    case STREAM_NONE: {
        debugs(33, 3, "Get more data");
        StoreIOBuffer tempBuffer;
        tempBuffer.offset = http->out.offset;
        tempBuffer.data = context_->requestBuffer;
        tempBuffer.length = HTTP_REQBUF_SZ;
        clientStreamRead(node, http, tempBuffer);
    }
    break;
    case STREAM_COMPLETE:
        debugs(33, 3, "Object data transfer successfully complete");
        callBack(Http::scOkay);
        break;
    case STREAM_UNPLANNED_COMPLETE:
        debugs(33, 3, "Object data transfer failed: STREAM_UNPLANNED_COMPLETE");
        callBack(Http::scInternalServerError);
        break;
    case STREAM_FAILED:
        debugs(33, 3, "Object data transfer failed: STREAM_FAILED");
        callBack(Http::scInternalServerError);
        break;
    default:
        fatal("unreachable code");
    }
}