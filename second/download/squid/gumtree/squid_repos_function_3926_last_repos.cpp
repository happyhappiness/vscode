const char *Ssl::ErrorDetail::err_descr() const
{
    if (error_no == SSL_ERROR_NONE)
        return "[No Error]";
    if (const char *err = detailEntry.descr.termedBuf())
        return err;
    return "[Not available]";
}