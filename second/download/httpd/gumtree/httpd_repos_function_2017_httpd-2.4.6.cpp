static
int ftp_proxyerror(request_rec *r, proxy_conn_rec *conn, int statuscode, const char *message)
{
    proxy_ftp_cleanup(r, conn);
    return ap_proxyerror(r, statuscode, message);
}