const char *Ssl::ErrorDetail::err_code() const
{
    static char tmpBuffer[64];
    const char *err = getErrorName(error_no);
    if (!err) {
        snprintf(tmpBuffer, 64, "%d", (int)error_no);
        err = tmpBuffer;
    }
    return err;
}