    rewriteConfigYesNoOption(state,"lazyfree-lazy-expire",server.lazyfree_lazy_expire,CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE);
    rewriteConfigYesNoOption(state,"lazyfree-lazy-server-del",server.lazyfree_lazy_server_del,CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL);
    rewriteConfigYesNoOption(state,"slave-lazy-flush",server.repl_slave_lazy_flush,CONFIG_DEFAULT_SLAVE_LAZY_FLUSH);
    rewriteConfigYesNoOption(state,"hll-use-loglogbeta",server.hll_use_loglogbeta,CONFIG_DEFAULT_HLL_USE_LOGLOGBETA);

    /* Rewrite Sentinel config if in Sentinel mode. */
    if (server.sentinel_mode) rewriteConfigSentinelOption(state);
