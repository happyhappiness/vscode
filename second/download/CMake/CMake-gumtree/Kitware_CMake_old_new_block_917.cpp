{
    va_list ap;
    int ret;
    va_start(ap, fmt);
    ret = Curl_sec_vfprintf(conn, f, fmt, ap);
    va_end(ap);
    return ret;
}