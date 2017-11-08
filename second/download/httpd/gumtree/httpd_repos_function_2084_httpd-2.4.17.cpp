static int proxy_match_word(struct dirconn_entry *This, request_rec *r)
{
    const char *host = proxy_get_host_of_request(r);
    return host != NULL && ap_strstr_c(host, This->name) != NULL;
}