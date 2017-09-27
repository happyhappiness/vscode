
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

/* --------------------------------------------------------- */
/* write out request to a connection - assumes we can write
 * (small) request out in one go into our new socket buffer
 *
 */
#ifdef USE_SSL
static long ssl_print_cb(BIO *bio,int cmd,const char *argp,int argi,long argl,long ret)
{
    BIO *out;

    out=(BIO *)BIO_get_callback_arg(bio);
    if (out == NULL) return(ret);

    if (cmd == (BIO_CB_READ|BIO_CB_RETURN)) {
        BIO_printf(out,"read from %08X [%08lX] (%d bytes => %ld (0x%X))\n",
                bio,argp,argi,ret,ret);
        BIO_dump(out,(char *)argp,(int)ret);
        return(ret);
    }
    else if (cmd == (BIO_CB_WRITE|BIO_CB_RETURN)) {
        BIO_printf(out,"write to %08X [%08lX] (%d bytes => %ld (0x%X))\n",
            bio,argp,argi,ret,ret);
        BIO_dump(out,(char *)argp,(int)ret);
    }
    return ret;
}

static void ssl_state_cb(const SSL *s, int w, int r)
{
    if (w & SSL_CB_ALERT) {
        BIO_printf(bio_err, "SSL/TLS Alert [%s] %s:%s\n",
                   (w & SSL_CB_READ ? "read" : "write"),
                   SSL_alert_type_string_long(r),
                   SSL_alert_desc_string_long(r));
    } else if (w & SSL_CB_LOOP) {
        BIO_printf(bio_err, "SSL/TLS State [%s] %s\n",
                   (SSL_in_connect_init((SSL*)s) ? "connect" : "-"),
                   SSL_state_string_long(s));
    } else if (w & (SSL_CB_HANDSHAKE_START|SSL_CB_HANDSHAKE_DONE)) {
        BIO_printf(bio_err, "SSL/TLS Handshake [%s] %s\n",
                   (w & SSL_CB_HANDSHAKE_START ? "Start" : "Done"),
                   SSL_state_string_long(s));
    }
}

#ifndef RAND_MAX
#include <limits.h>
#define RAND_MAX INT_MAX
#endif
