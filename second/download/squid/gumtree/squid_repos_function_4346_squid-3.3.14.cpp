const char *Ssl::ErrorDetail::cn() const
{
    if (!broken_cert)
        return "[Not available]";

    static String tmpStr;  ///< A temporary string buffer
    tmpStr.clean();
    Ssl::matchX509CommonNames(broken_cert.get(), &tmpStr, copy_cn);
    return tmpStr.termedBuf();
}