	return;

    }

    else

	inside = 1;

    (void) ap_release_mutex(garbage_mutex);



    help_proxy_garbage_coll(r);



    (void) ap_acquire_mutex(garbage_mutex);

    inside = 0;

    (void) ap_release_mutex(garbage_mutex);

}





static void help_proxy_garbage_coll(request_rec *r)

{

    const char *cachedir;

    void *sconf = r->server->module_config;

    proxy_server_conf *pconf =

    (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    const struct cache_conf *conf = &pconf->cache;

    array_header *files;

    struct stat buf;

    struct gc_ent *fent, **elts;

    int i, timefd;

    static time_t lastcheck = BAD_DATE;		/* static data!!! */



    cachedir = conf->root;

    cachesize = conf->space;

    every = conf->gcinterval;



    if (cachedir == NULL || every == -1)

	return;

    garbage_now = time(NULL);

    if (garbage_now != -1 && lastcheck != BAD_DATE && garbage_now < lastcheck + every)

	return;



    ap_block_alarms();		/* avoid SIGALRM on big cache cleanup */



    filename = ap_palloc(r->pool, strlen(cachedir) + HASH_LEN + 2);

