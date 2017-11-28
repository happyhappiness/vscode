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