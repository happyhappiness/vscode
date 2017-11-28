void
WhoisState::setReplyToOK(StoreEntry *sentry)
{
    HttpReply *reply = new HttpReply;
    sentry->buffer();
    reply->setHeaders(Http::scOkay, "Gatewaying", "text/plain", -1, -1, -2);
    sentry->replaceHttpReply(reply);
}