bool
clientReplyContext::blockedHit() const
{
    if (!Config.accessList.sendHit)
        return false; // hits are not blocked by default

    if (http->flags.internal)
        return false; // internal content "hits" cannot be blocked

    if (const HttpReply *rep = http->storeEntry()->getReply()) {
        std::unique_ptr<ACLFilledChecklist> chl(clientAclChecklistCreate(Config.accessList.sendHit, http));
        chl->reply = const_cast<HttpReply*>(rep); // ACLChecklist API bug
        HTTPMSGLOCK(chl->reply);
        return chl->fastCheck() != ACCESS_ALLOWED; // when in doubt, block
    }

    // This does not happen, I hope, because we are called from CacheHit, which
    // is called via a storeClientCopy() callback, and store should initialize
    // the reply before calling that callback.
    debugs(88, 3, "Missing reply!");
    return false;
}