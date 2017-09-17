	return;
    }
    else
	inside = 1;
    (void) ap_release_mutex(garbage_mutex);

    ap_block_alarms();		/* avoid SIGALRM on big cache cleanup */
#if !defined(WIN32) && !defined(MPE) && !defined(__EMX__)
    detached_proxy_garbage_coll(r);
#else
    help_proxy_garbage_coll(r);
#endif
    ap_unblock_alarms();

    (void) ap_acquire_mutex(garbage_mutex);
    inside = 0;
    (void) ap_release_mutex(garbage_mutex);
}


static void
add_long61 (long61_t *accu, long val)
{
    /* Add in lower 30 bits */
    accu->lower += (val & 0x3FFFFFFFL);
    /* add in upper bits, and carry */
    accu->upper += (val >> 30) + ((accu->lower & ~0x3FFFFFFFL) != 0L);
    /* Clear carry */
    accu->lower &= 0x3FFFFFFFL;
}

static void
sub_long61 (long61_t *accu, long val)
{
    int carry = (val & 0x3FFFFFFFL) > accu->lower;
    /* Subtract lower 30 bits */
    accu->lower = accu->lower - (val & 0x3FFFFFFFL) + ((carry) ? 0x40000000 : 0);
    /* add in upper bits, and carry */
    accu->upper -= (val >> 30) + carry;
}

/* Compare two long61's:
 * return <0 when left < right
 * return  0 when left == right
 * return >0 when left > right
 */
static long
cmp_long61 (long61_t *left, long61_t *right)
{
    return (left->upper == right->upper) ? (left->lower - right->lower)
					 : (left->upper - right->upper);
}

/* Compare two gc_ent's, sort them by expiration date */
static int gcdiff(const void *ap, const void *bp)
{
    const struct gc_ent *a = (const struct gc_ent * const) ap;
    const struct gc_ent *b = (const struct gc_ent * const) bp;

    if (a->expire > b->expire)
	return 1;
    else if (a->expire < b->expire)
	return -1;
    else
	return 0;
}

#if !defined(WIN32) && !defined(MPE) && !defined(__EMX__)
static void detached_proxy_garbage_coll(request_rec *r)
{
    pid_t pid;
    int status;
    pid_t pgrp;

    switch (pid = fork()) {
	case -1:
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: fork() for cache cleanup failed");
	    return;

	case 0:	/* Child */

	    /* close all sorts of things, including the socket fd */
	    ap_cleanup_for_exec();

	    /* Fork twice to disassociate from the child */
	    switch (pid = fork()) {
		case -1:
		    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: fork(2nd) for cache cleanup failed");
		    exit(1);

		case 0:	/* Child */
		    /* The setpgrp() stuff was snarfed from http_main.c */
#ifndef NO_SETSID
		    if ((pgrp = setsid()) == -1) {
			perror("setsid");
			fprintf(stderr, "httpd: setsid failed\n");
			exit(1);
		    }
#elif defined(NEXT) || defined(NEWSOS)
		    if (setpgrp(0, getpid()) == -1 || (pgrp = getpgrp(0)) == -1) {
			perror("setpgrp");
			fprintf(stderr, "httpd: setpgrp or getpgrp failed\n");
			exit(1);
		    }
#else
		    if ((pgrp = setpgrp(getpid(), 0)) == -1) {
			perror("setpgrp");
			fprintf(stderr, "httpd: setpgrp failed\n");
			exit(1);
		    }
#endif
		    help_proxy_garbage_coll(r);
		    exit(0);

		default:    /* Father */
		    /* After grandson has been forked off, */
		    /* there's nothing else to do. */
		    exit(0);		    
	    }
	default:
	    /* Wait until grandson has been forked off */
	    /* (without wait we'd leave a zombie) */
	    waitpid(pid, &status, 0);
	    return;
    }
}
#endif /* ndef WIN32 */

static void help_proxy_garbage_coll(request_rec *r)
{
    const char *cachedir;
    void *sconf = r->server->module_config;
    proxy_server_conf *pconf =
    (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
    const struct cache_conf *conf = &pconf->cache;
    array_header *files;
    struct stat buf;
    struct gc_ent *fent;
    int i, timefd;
    static time_t lastcheck = BAD_DATE;		/* static (per-process) data!!! */

    cachedir = conf->root;
    /* configured size is given in kB. Make it bytes, convert to long61_t: */
    cachesize.lower = cachesize.upper = 0;
    add_long61(&cachesize, conf->space << 10);
    every = conf->gcinterval;

    if (cachedir == NULL || every == -1)
	return;
    garbage_now = time(NULL);
    /* Usually, the modification time of <cachedir>/.time can only increase.
     * Thus, even with several child processes having their own copy of
     * lastcheck, if time(NULL) still < lastcheck then it's not time
     * for GC yet.
     */
    if (garbage_now != -1 && lastcheck != BAD_DATE && garbage_now < lastcheck + every)
	return;

    ap_block_alarms();		/* avoid SIGALRM on big cache cleanup */

    filename = ap_palloc(r->pool, strlen(cachedir) + HASH_LEN + 2);
