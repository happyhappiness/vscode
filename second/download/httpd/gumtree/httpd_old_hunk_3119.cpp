                    server_rec *base_server)
{
    SSLModConfigRec *mc = myModConfig(base_server);
    SSLSrvConfigRec *sc;
    server_rec *s;

    /* We initialize mc->pid per-process in the child init,
     * but it should be initialized for startup before we
     * call ssl_rand_seed() below.
     */
    mc->pid = getpid();

