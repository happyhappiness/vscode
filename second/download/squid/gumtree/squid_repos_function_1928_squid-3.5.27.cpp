static const char *
external_acl_ssl_get_user_attribute(const ACLFilledChecklist &ch, const char *attr)
{
    if (ch.conn() != NULL && Comm::IsConnOpen(ch.conn()->clientConnection)) {
        if (SSL *ssl = fd_table[ch.conn()->clientConnection->fd].ssl)
            return sslGetUserAttribute(ssl, attr);
    }
    return NULL;
}