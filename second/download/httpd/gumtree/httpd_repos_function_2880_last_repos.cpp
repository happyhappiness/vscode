static apr_status_t add_request(h2_proxy_session *session, request_rec *r)
{
    h2_proxy_ctx *ctx = session->user_data;
    const char *url;
    apr_status_t status;

    url = apr_table_get(r->notes, H2_PROXY_REQ_URL_NOTE);
    apr_table_setn(r->notes, "proxy-source-port", apr_psprintf(r->pool, "%hu",
                   ctx->p_conn->connection->local_addr->port));
    status = h2_proxy_session_submit(session, url, r, ctx->standalone);
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, r->connection, APLOGNO(03351)
                      "pass request body failed to %pI (%s) from %s (%s)",
                      ctx->p_conn->addr, ctx->p_conn->hostname ? 
                      ctx->p_conn->hostname: "", session->c->client_ip, 
                      session->c->remote_host ? session->c->remote_host: "");
    }
    return status;
}