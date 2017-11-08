static int isSecure (const request_rec *r)
{
        return isSecureConn (r->server, r->connection);
}