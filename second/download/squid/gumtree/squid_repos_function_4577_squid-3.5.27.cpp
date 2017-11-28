const char *Ssl::ErrorDetail::cn() const
{
    if (broken_cert.get()) {
        static String tmpStr;  ///< A temporary string buffer
        tmpStr.clean();
        Ssl::matchX509CommonNames(broken_cert.get(), &tmpStr, copy_cn);
        if (tmpStr.size())
            return tmpStr.termedBuf();
    }
    return "[Not available]";
}