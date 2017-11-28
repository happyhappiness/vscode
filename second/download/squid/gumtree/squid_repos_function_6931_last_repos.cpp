static char *
sslErrorName(Security::ErrorCode err, char *buf, size_t size)
{
    snprintf(buf, size, "SSL_ERR=%d", err);
    return buf;
}