static void get_random_info(unsigned char node[NODE_LENGTH])
{
#if APR_HAS_RANDOM

    (void) apr_generate_random_bytes(node, NODE_LENGTH);

#else

    unsigned char seed[MD5_DIGESTSIZE];
    apr_md5_ctx_t c;

    /* ### probably should revise some of this to be a bit more portable */

    /* Leach & Salz use Linux-specific struct sysinfo;
     * replace with pid/tid for portability (in the spirit of mod_unique_id) */
    struct {
	/* Add thread id here, if applicable, when we get to pthread or apr */
        pid_t pid;
#ifdef NETWARE
        apr_uint64_t t;
#else
        struct timeval t;
#endif
        char hostname[257];

    } r;

    apr_md5_init(&c);
#ifdef NETWARE
    r.pid = NXThreadGetId();
    NXGetTime(NX_SINCE_BOOT, NX_USECONDS, &(r.t));
#else
    r.pid = getpid();
    gettimeofday(&r.t, (struct timezone *)0);
#endif
    gethostname(r.hostname, 256);
    apr_md5_update(&c, (const unsigned char *)&r, sizeof(r));
    apr_md5_final(seed, &c);

    memcpy(node, seed, NODE_LENGTH);    /* use a subset of the seed bytes */
#endif
}