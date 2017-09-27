 */

#include "ajp.h"

APLOG_USE_MODULE(proxy_ajp);

static char *hex_table = "0123456789ABCDEF";

/**
 * Dump up to the first 1024 bytes on an AJP Message
 *
 * @param pool      pool to allocate from
 * @param msg       AJP Message to dump
 * @param err       error string to display
 * @return          dump message
 */
char * ajp_msg_dump(apr_pool_t *pool, ajp_msg_t *msg, char *err)
{
    apr_size_t  i, j;
    char        line[80];
    char        *current;
    char        *rv, *p;
    apr_size_t  bl = 8192;
    apr_byte_t  x;
    apr_size_t  len = msg->len;

    /* Display only first 1024 bytes */
    if (len > 1024)
        len = 1024;
    rv = apr_palloc(pool, bl);
    apr_snprintf(rv, bl,
                 "ajp_msg_dump(): %s pos=%" APR_SIZE_T_FMT
                 " len=%" APR_SIZE_T_FMT " max=%" APR_SIZE_T_FMT "\n",
                 err, msg->pos, msg->len, msg->max_size);
    bl -= strlen(rv);
    p = rv + strlen(rv);
    for (i = 0; i < len; i += 16) {
        current = line;

        for (j = 0; j < 16; j++) {
             x = msg->buf[i + j];

            *current++ = hex_table[x >> 4];
            *current++ = hex_table[x & 0x0f];
            *current++ = ' ';
        }
        *current++ = ' ';
        *current++ = '-';
        *current++ = ' ';
        for (j = 0; j < 16; j++) {
            x = msg->buf[i + j];

            if (x > 0x20 && x < 0x7F) {
                *current++ = x;
            }
            else {
                *current++ = '.';
            }
        }

        *current++ = '\0';
        apr_snprintf(p, bl,
                     "ajp_msg_dump(): %.4lx    %s\n",
                     (unsigned long)i, line);
        bl -= strlen(rv);
        p = rv + strlen(rv);

    }

    return rv;
}


/**
 * Check a new AJP Message by looking at signature and return its size
 *
 * @param msg       AJP Message to check
 * @param len       Pointer to returned len
