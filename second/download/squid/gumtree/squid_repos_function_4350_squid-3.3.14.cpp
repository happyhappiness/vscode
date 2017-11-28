const char *Ssl::ErrorDetail::err_code() const
{
    static char tmpBuffer[64];
    // We can use the GetErrorName but using the detailEntry is faster,
    // so try it first.
    const char *err = detailEntry.name.termedBuf();

    // error details not loaded yet or not defined in error_details.txt,
    // try the GetErrorName...
    if (!err)
        err = GetErrorName(error_no);

    if (!err) {
        snprintf(tmpBuffer, 64, "%d", (int)error_no);
        err = tmpBuffer;
    }
    return err;
}