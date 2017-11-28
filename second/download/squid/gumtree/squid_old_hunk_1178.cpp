    }
}

void
Ftp::Server::handleFeatReply(const HttpReply *reply, StoreIOBuffer)
{
    if (getCurrentContext()->http->request->errType != ERR_NONE) {
        writeCustomReply(502, "Server does not support FEAT", reply);
        return;
    }

    Must(reply);
    HttpReply::Pointer featReply = Ftp::HttpReplyWrapper(211, "End", Http::scNoContent, 0);
