void
ClientDelayConfig::finalize()
{
    for (unsigned int i = 0; i < pools.size(); ++i) {
        /* pools require explicit 'allow' to assign a client into them */
        if (!pools[i].access) {
            debugs(77, DBG_IMPORTANT, "client_delay_pool #" << (i+1) <<
                   " has no client_delay_access configured. " <<
                   "No client will ever use it.");
        }
    }
}