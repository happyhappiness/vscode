static const char *clf_log_bytes_sent(request_rec *r, char *a)
{
    if (!r->sent_bodyct || !r->bytes_sent) {
        return "-";
    }
    else {
        return apr_off_t_toa(r->pool, r->bytes_sent);
    }
}