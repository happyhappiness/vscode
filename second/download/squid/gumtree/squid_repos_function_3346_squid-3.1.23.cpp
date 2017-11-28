void
clientReplyContext::cloneReply()
{
    assert(reply == NULL);

    HttpReply *rep = http->storeEntry()->getReply()->clone();

    reply = HTTPMSGLOCK(rep);

    if (reply->sline.protocol == PROTO_HTTP) {
        /* enforce 1.0 reply version (but only on real HTTP traffic) */
        reply->sline.version = HttpVersion(1,0);
    }

    /* do header conversions */
    buildReplyHeader();
}