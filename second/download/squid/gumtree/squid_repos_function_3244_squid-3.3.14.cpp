DelayId
DelayId::DelayClient(ClientHttpRequest * http)
{
    HttpRequest *r;
    unsigned short pool;
    assert(http);
    r = http->request;

    if (r->client_addr.IsNoAddr()) {
        debugs(77, 2, "delayClient: WARNING: Called with 'NO_ADDR' address, ignoring");
        return DelayId();
    }

    for (pool = 0; pool < DelayPools::pools(); ++pool) {

        /* pools require explicit 'allow' to assign a client into them */
        if (!DelayPools::delay_data[pool].access) {
            debugs(77, DBG_IMPORTANT, "delay_pool " << pool <<
                   " has no delay_access configured. This means that no clients will ever use it.");
            continue;
        }

        ACLFilledChecklist ch(DelayPools::delay_data[pool].access, r, NULL);
#if FOLLOW_X_FORWARDED_FOR
        if (Config.onoff.delay_pool_uses_indirect_client)
            ch.src_addr = r->indirect_client_addr;
        else
#endif /* FOLLOW_X_FORWARDED_FOR */
            ch.src_addr = r->client_addr;
        ch.my_addr = r->my_addr;

        if (http->getConn() != NULL)
            ch.conn(http->getConn());

        if (DelayPools::delay_data[pool].theComposite().getRaw() && ch.fastCheck() == ACCESS_ALLOWED) {

            DelayId result (pool + 1);
            CompositePoolNode::CompositeSelectionDetails details;
            details.src_addr = ch.src_addr;
#if USE_AUTH
            details.user = r->auth_user_request;
#endif
            details.tag = r->tag;
            result.compositePosition(DelayPools::delay_data[pool].theComposite()->id(details));
            return result;
        }
    }

    return DelayId();
}