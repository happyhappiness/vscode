static void
remove_session_cb(SSL_CTX *, SSL_SESSION *sessionID)
{
    if (!SslSessionCache)
        return ;

    debugs(83, 5, "Request to remove corrupted or not valid SSL Session ");
    int pos;
    Ipc::MemMap::Slot const *slot = SslSessionCache->openForReading((const cache_key*)sessionID, pos);
    if (slot == NULL)
        return;
    SslSessionCache->closeForReading(pos);
    // TODO:
    // What if we are not able to remove the session?
    // Maybe schedule a job to remove it later?
    // For now we just have an invalid entry in cache until will be expired
    // The openSSL will reject it when we try to use it
    SslSessionCache->free(pos);
}