static int core_generate_log_id(const conn_rec *c, const request_rec *r,
                                 const char **idstring)
{
    apr_uint64_t id, tmp;
    pid_t pid;
    int len;
    char *encoded;

    if (r && r->request_time) {
        id = (apr_uint64_t)r->request_time;
    }
    else {
        id = (apr_uint64_t)apr_time_now();
    }

    pid = getpid();
    if (sizeof(pid_t) > 2) {
        tmp = pid;
        tmp = tmp << 40;
        id ^= tmp;
        pid = pid >> 24;
        tmp = pid;
        tmp = tmp << 56;
        id ^= tmp;
    }
    else {
        tmp = pid;
        tmp = tmp << 40;
        id ^= tmp;
    }
#if APR_HAS_THREADS
    {
        apr_uintptr_t tmp2 = (apr_uintptr_t)c->current_thread;
        tmp = tmp2;
        tmp = tmp << 32;
        id ^= tmp;
    }
#endif

    len = apr_base64_encode_len(sizeof(id)); /* includes trailing \0 */
    encoded = apr_palloc(r ? r->pool : c->pool, len);
    apr_base64_encode(encoded, (char *)&id, sizeof(id));

    /* Skip the last char, it is always '=' */
    encoded[len - 2] = '\0';

    *idstring = encoded;

    return OK;
}