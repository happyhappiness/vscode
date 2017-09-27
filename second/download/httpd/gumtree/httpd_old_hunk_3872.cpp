#include <httpd.h>
#include <http_core.h>
#include <http_log.h>
#include <http_connection.h>

#include "h2_private.h"
#include "h2_config.h"
#include "h2_conn_io.h"
#include "h2_h2.h"
#include "h2_util.h"

#define WRITE_BUFFER_SIZE     (64*1024)
#define WRITE_SIZE_INITIAL    1300
#define WRITE_SIZE_MAX        (16*1024)
#define WRITE_SIZE_IDLE_USEC  (1*APR_USEC_PER_SEC)
#define WRITE_SIZE_THRESHOLD  (1*1024*1024)

apr_status_t h2_conn_io_init(h2_conn_io *io, conn_rec *c)
{
    io->connection = c;
    io->input = apr_brigade_create(c->pool, c->bucket_alloc);
    io->output = apr_brigade_create(c->pool, c->bucket_alloc);
    io->buflen = 0;
    /* That is where we start with, 
     * see https://issues.apache.org/jira/browse/TS-2503 */
    io->write_size = WRITE_SIZE_INITIAL; 
    io->last_write = 0;
    io->buffer_output = h2_h2_is_tls(c);

    /* Currently we buffer only for TLS output. The reason this gives
     * improved performance is that buckets send to the mod_ssl network
     * filter will be encrypted in chunks. There is a special filter
     * that tries to aggregate data, but that does not work well when
     * bucket sizes alternate between tiny frame headers and large data
     * chunks.
     */
    if (io->buffer_output) {
        io->bufsize = WRITE_BUFFER_SIZE;
        io->buffer = apr_pcalloc(c->pool, io->bufsize);
    }
    else {
        io->bufsize = 0;
    }
    
    return APR_SUCCESS;
}

void h2_conn_io_destroy(h2_conn_io *io)
{
    io->input = NULL;
    io->output = NULL;
}

static apr_status_t h2_conn_io_bucket_read(h2_conn_io *io,
                                           apr_read_type_e block,
                                           h2_conn_io_on_read_cb on_read_cb,
                                           void *puser, int *pdone)
