static const char *log_bytes_sent(request_rec *r, char *a)
{
    if (!r->sent_bodyct) {
        return "0";
    }
    else {
	return apr_psprintf(r->pool, "%" APR_OFF_T_FMT, r->bytes_sent);
    }
}