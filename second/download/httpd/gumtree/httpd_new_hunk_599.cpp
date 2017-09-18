	    s, apr_strerror(rv, buf, sizeof buf), rv);
    if (done)
        printf("Total of %ld requests completed\n" , done);
    exit(rv);
}

#if defined(USE_SSL) && USE_THREADS
/*
 * To ensure thread-safetyness in OpenSSL - work in progress
 */

static apr_thread_mutex_t **lock_cs;
static int                  lock_num_locks;

static void ssl_util_thr_lock(int mode, int type,
                              const char *file, int line)
{
    if (type < lock_num_locks) {
        if (mode & CRYPTO_LOCK) {
            apr_thread_mutex_lock(lock_cs[type]);
        }
        else {
            apr_thread_mutex_unlock(lock_cs[type]);
        }
    }
}

static unsigned long ssl_util_thr_id(void)
{
    /* OpenSSL needs this to return an unsigned long.  On OS/390, the pthread 
     * id is a structure twice that big.  Use the TCB pointer instead as a 
     * unique unsigned long.
     */
#ifdef __MVS__
    struct PSA {
        char unmapped[540];
        unsigned long PSATOLD;
    } *psaptr = 0;

    return psaptr->PSATOLD;
#else
    return (unsigned long) apr_os_thread_current();
#endif
}

static apr_status_t ssl_util_thread_cleanup(void *data)
{
    CRYPTO_set_locking_callback(NULL);

    /* Let the registered mutex cleanups do their own thing 
     */
    return APR_SUCCESS;
}

void ssl_util_thread_setup(apr_pool_t *p)
{
    int i;

    lock_num_locks = CRYPTO_num_locks();
    lock_cs = apr_palloc(p, lock_num_locks * sizeof(*lock_cs));

    for (i = 0; i < lock_num_locks; i++) {
        apr_thread_mutex_create(&(lock_cs[i]), APR_THREAD_MUTEX_DEFAULT, p);
    }

    CRYPTO_set_id_callback(ssl_util_thr_id);

    CRYPTO_set_locking_callback(ssl_util_thr_lock);

    apr_pool_cleanup_register(p, NULL, ssl_util_thread_cleanup,
                                       apr_pool_cleanup_null);
}
#endif

/* --------------------------------------------------------- */
/* write out request to a connection - assumes we can write
 * (small) request out in one go into our new socket buffer
 *
 */
#ifdef USE_SSL
long ssl_print_cb(BIO *bio,int cmd,const char *argp,int argi,long argl,long ret)
{
    BIO *out;

    out=(BIO *)BIO_get_callback_arg(bio);
    if (out == NULL) return(ret);

    if (cmd == (BIO_CB_READ|BIO_CB_RETURN))
    {
        BIO_printf(out,"read from %08X [%08lX] (%d bytes => %ld (0x%X))\n",
                bio,argp,argi,ret,ret);
        BIO_dump(out,argp,(int)ret);
        return(ret);
    }
    else if (cmd == (BIO_CB_WRITE|BIO_CB_RETURN))
    {
        BIO_printf(out,"write to %08X [%08lX] (%d bytes => %ld (0x%X))\n",
            bio,argp,argi,ret,ret);
        BIO_dump(out,argp,(int)ret);
    }
    return(ret);
}

#ifndef RAND_MAX
#include <limits.h>
#define RAND_MAX INT_MAX
#endif

static int ssl_rand_choosenum(int l, int h)
{
    int i;
    char buf[50];

    srand((unsigned int)time(NULL));
    apr_snprintf(buf, sizeof(buf), "%.0f",
                 (((double)(rand()%RAND_MAX)/RAND_MAX)*(h-l)));
    i = atoi(buf)+1;
    if (i < l) i = l;
    if (i > h) i = h;
    return i;
}

void ssl_rand_seed()
{
    int nDone = 0;
    int n, l;
    time_t t;
    pid_t pid;
    unsigned char stackdata[256];

    /*
     * seed in the current time (usually just 4 bytes)
     */
    t = time(NULL);
    l = sizeof(time_t);
    RAND_seed((unsigned char *)&t, l);
    nDone += l;

    /*
     * seed in the current process id (usually just 4 bytes)
     */
    pid = getpid();
    l = sizeof(pid_t);
    RAND_seed((unsigned char *)&pid, l);
    nDone += l;

    /*
     * seed in some current state of the run-time stack (128 bytes)
     */
    n = ssl_rand_choosenum(0, sizeof(stackdata)-128-1);
    RAND_seed(stackdata+n, 128);
    nDone += 128;
}

int ssl_print_connection_info(bio,ssl)
BIO *bio;
SSL *ssl;
{
        SSL_CIPHER *c;
        int alg_bits,bits;

        c=SSL_get_current_cipher(ssl);
        BIO_printf(bio,"Cipher Suite Protocol   :%s\n", SSL_CIPHER_get_version(c));
        BIO_printf(bio,"Cipher Suite Name       :%s\n",SSL_CIPHER_get_name(c));

        bits=SSL_CIPHER_get_bits(c,&alg_bits);
        BIO_printf(bio,"Cipher Suite Cipher Bits:%d (%d)\n",bits,alg_bits);

        return(1);
}

int ssl_print_cert_info(bio,x509cert)
BIO *bio;
X509 *x509cert;
{
        X509_NAME *dn;
        char buf[64];

        BIO_printf(bio,"Certificate version: %d\n",X509_get_version(x509cert)+1);

        BIO_printf(bio,"Valid from: ");
        ASN1_UTCTIME_print(bio, X509_get_notBefore(x509cert));
        BIO_printf(bio,"\n");

        BIO_printf(bio,"Valid to  : ");
        ASN1_UTCTIME_print(bio, X509_get_notAfter(x509cert));
        BIO_printf(bio,"\n");

        BIO_printf(bio,"Public key is %d bits\n",
            EVP_PKEY_bits(X509_get_pubkey(x509cert)));

        dn=X509_get_issuer_name(x509cert);
        X509_NAME_oneline(dn, buf, BUFSIZ);
        BIO_printf(bio,"The issuer name is %s\n", buf);

        dn=X509_get_subject_name(x509cert);
        X509_NAME_oneline(dn, buf, BUFSIZ);
        BIO_printf(bio,"The subject name is %s\n", buf);

        /* dump the extension list too */
        BIO_printf(bio,"Extension Count: %d\n",X509_get_ext_count(x509cert));

        return(1);
}

void ssl_start_connect(struct connection * c)
{
    BIO *bio;
    X509 *x509cert;
    STACK_OF(X509) *sk;
    int i, count, hdone = 0;
    char ssl_hostname[80];
    
    /* XXX - Verify if it's okay - TBD */
    if (requests < concurrency)
        requests = concurrency;

    if (!(started < requests))
        return;

    c->read = 0;
    c->bread = 0;
    c->keepalive = 0;
    c->cbx = 0;
    c->gotheader = 0;
    c->rwrite = 0;
    if (c->ctx)
        apr_pool_destroy(c->ctx);
    apr_pool_create(&c->ctx, cntxt);

    if ((c->ssl=SSL_new(ctx)) == NULL)
    {
        BIO_printf(bio_err,"SSL_new failed\n");
        exit(1);
    }

    ssl_rand_seed();

    c->start = apr_time_now();
    memset(ssl_hostname, 0, 80);
    sprintf(ssl_hostname, "%s:%d", hostname, port);

    if ((bio = BIO_new_connect(ssl_hostname)) == NULL)
    {
        BIO_printf(bio_err,"BIO_new_connect failed\n");
        exit(1);
    }
    SSL_set_bio(c->ssl,bio,bio);
    SSL_set_connect_state(c->ssl);

    if (verbosity >= 4)
    {
        BIO_set_callback(bio,ssl_print_cb);
        BIO_set_callback_arg(bio,bio_err);
    }

    while (!hdone)
    {
        i = SSL_do_handshake(c->ssl);

        switch (SSL_get_error(c->ssl,i))
        {
            case SSL_ERROR_NONE:
                hdone=1;
                break;
            case SSL_ERROR_SSL:
            case SSL_ERROR_SYSCALL:
                BIO_printf(bio_err,"SSL connection failed\n");
                err_conn++;
                c->state = STATE_UNCONNECTED;
                if (bad++ > 10) {
                    SSL_free (c->ssl);
                    BIO_printf(bio_err,"\nTest aborted after 10 failures\n\n");
                    exit (1);
                }
                break;
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
            case SSL_ERROR_WANT_CONNECT:
                BIO_printf(bio_err, "Waiting .. sleep(1)\n");
                apr_sleep(1 * APR_USEC_PER_SEC);
                c->state = STATE_CONNECTING;
                c->rwrite = 0;
                break;
            case SSL_ERROR_ZERO_RETURN:
                BIO_printf(bio_err,"socket closed\n");
                break;
        }
    }
    
    if (verbosity >= 2)
    {
        BIO_printf(bio_err, "\n");
        sk = SSL_get_peer_cert_chain(c->ssl);
        if ((count = sk_X509_num(sk)) > 0)
        {
            for (i=1; i<count; i++)
            {
                x509cert = (X509 *)sk_X509_value(sk,i);
                ssl_print_cert_info(bio_out,x509cert);
                X509_free(x509cert);
            }
        }

        x509cert = SSL_get_peer_certificate(c->ssl);
        if (x509cert == NULL)
            BIO_printf(bio_out, "Anon DH\n");
        else
        {
            BIO_printf(bio_out, "Peer certificate\n");
            ssl_print_cert_info(bio_out,x509cert);
            X509_free(x509cert);
        }

        ssl_print_connection_info(bio_err,c->ssl);
        SSL_SESSION_print(bio_err,SSL_get_session(c->ssl));
    }

    /* connected first time */
    started++;
    write_request(c);
}
#endif /* USE_SSL */

static void write_request(struct connection * c)
{
    do {
	apr_time_t tnow = apr_time_now();
	apr_size_t l = c->rwrite;
	apr_status_t e;

	/*
	 * First time round ?
	 */
	if (c->rwrite == 0) {
#ifdef USE_SSL
            if (ssl != 1)
#endif
	    apr_setsocketopt(c->aprsock, APR_SO_TIMEOUT, 0);
	    c->connect = tnow;
	    c->rwrite = reqlen;
	    c->rwrote = 0;
	    if (posting)
		c->rwrite += postlen;
