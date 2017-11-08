static const char *log_bytes_sent(request_rec *r, char *a)
{
    if (!r->sent_bodyct || !r->bytes_sent) {
        return "0";
    }
    else {
        return apr_off_t_toa(r->pool, r->bytes_sent);
    }
}