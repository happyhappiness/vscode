
static void apr_err(char *s, apr_status_t rv)
{
    char buf[120];

    fprintf(stderr,
	    "%s: %s (%d)\n",
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
        BIO_dump(out,(char *)argp,(int)ret);
        return(ret);
    }
    else if (cmd == (BIO_CB_WRITE|BIO_CB_RETURN))
    {
        BIO_printf(out,"write to %08X [%08lX] (%d bytes => %ld (0x%X))\n",
            bio,argp,argi,ret,ret);
        BIO_dump(out,(char *)argp,(int)ret);
    }
    return(ret);
}

#ifndef RAND_MAX
#include <limits.h>
#define RAND_MAX INT_MAX
#endif
