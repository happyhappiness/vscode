const char *Ssl::ErrorDetail::cn() const
{
    if (!peer_cert)
        return "[Not available]";

    static String tmpStr;  ///< A temporary string buffer
    tmpStr.clean();
    Ssl::matchX509CommonNames(peer_cert.get(), &tmpStr, copy_cn);
    return tmpStr.termedBuf();
}