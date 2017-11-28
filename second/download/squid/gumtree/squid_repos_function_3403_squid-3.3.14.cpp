void
clientReplyContext::cloneReply()
{
    assert(reply == NULL);

    HttpReply *rep = http->storeEntry()->getReply()->clone();

    reply = HTTPMSGLOCK(rep);

    if (reply->sline.protocol == AnyP::PROTO_HTTP) {
        /* RFC 2616 requires us to advertise our 1.1 version (but only on real HTTP traffic) */
        reply->sline.version = HttpVersion(1,1);
    }

    /* do header conversions */
    buildReplyHeader();
}