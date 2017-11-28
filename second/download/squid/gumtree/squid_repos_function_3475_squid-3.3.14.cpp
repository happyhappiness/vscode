static void
clientIdentDone(const char *ident, void *data)
{
    ConnStateData *conn = (ConnStateData *)data;
    xstrncpy(conn->clientConnection->rfc931, ident ? ident : dash_str, USER_IDENT_SZ);
}