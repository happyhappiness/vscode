int32_t
Auth::Digest::User::ttl() const
{
    int32_t global_ttl = static_cast<int32_t>(expiretime - squid_curtime + ::Config.authenticateTTL);

    /* find the longest lasting nonce. */
    int32_t latest_nonce = -1;
    dlink_node *link = nonces.head;
    while (link) {
        digest_nonce_h *nonce = static_cast<digest_nonce_h *>(link->data);
        if (nonce->flags.valid && nonce->noncedata.creationtime > latest_nonce)
            latest_nonce = nonce->noncedata.creationtime;

        link = link->next;
    }
    if (latest_nonce == -1)
        return min(-1, global_ttl);

    int32_t nonce_ttl = latest_nonce - current_time.tv_sec + static_cast<Config*>(Auth::Config::Find("digest"))->noncemaxduration;

    return min(nonce_ttl, global_ttl);
}