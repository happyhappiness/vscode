const char *Ssl::ErrorDetail::err_lib_error() const
{
    if (errReason.size() > 0)
        return errReason.termedBuf();
    else if (lib_error_no != SSL_ERROR_NONE)
        return Security::ErrorString(lib_error_no);
    else
        return "[No Error]";
}