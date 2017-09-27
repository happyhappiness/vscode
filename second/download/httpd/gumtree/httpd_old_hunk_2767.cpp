#include <stdarg.h>
#endif
#if APR_HAVE_UNISTD_H
#include <unistd.h>
#endif

APLOG_USE_MODULE(http);

static int parse_byterange(char *range, apr_off_t clength,
                           apr_off_t *start, apr_off_t *end)
{
    char *dash = strchr(range, '-');
    char *errp;
    apr_off_t number;

    if (!dash) {
        return 0;
    }

    if ((dash == range)) {
        /* In the form "-5" */
        if (apr_strtoff(&number, dash+1, &errp, 10) || *errp) {
            return 0;
        }
        *start = clength - number;
        *end = clength - 1;
    }
    else {
        *dash++ = '\0';
        if (apr_strtoff(&number, range, &errp, 10) || *errp) {
            return 0;
        }
        *start = number;
        if (*dash) {
            if (apr_strtoff(&number, dash, &errp, 10) || *errp) {
                return 0;
            }
            *end = number;
        }
        else {                  /* "5-" */
            *end = clength - 1;
        }
    }

    if (*start < 0) {
        *start = 0;
    }

    if (*end >= clength) {
        *end = clength - 1;
    }

    if (*start > *end) {
        return -1;
    }

    return (*start > 0 || *end < clength);
}

static int ap_set_byterange(request_rec *r);

typedef struct byterange_ctx {
    apr_bucket_brigade *bb;
    int num_ranges;
    char *boundary;
    char *bound_head;
} byterange_ctx;

/*
 * Here we try to be compatible with clients that want multipart/x-byteranges
 * instead of multipart/byteranges (also see above), as per HTTP/1.1. We
 * look for the Request-Range header (e.g. Netscape 2 and 3) as an indication
 * that the browser supports an older protocol. We also check User-Agent
