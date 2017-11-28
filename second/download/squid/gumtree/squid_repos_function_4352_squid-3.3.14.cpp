const char *Ssl::ErrorDetail::err_lib_error() const
{
    if (lib_error_no != SSL_ERROR_NONE)
        return ERR_error_string(lib_error_no, NULL);
    else
        return "[No Error]";
}