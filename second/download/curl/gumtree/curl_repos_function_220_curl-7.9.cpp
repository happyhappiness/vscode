int
Curl_sec_fprintf2(struct connectdata *conn, FILE *f, const char *fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = Curl_sec_vfprintf2(conn, f, fmt, ap);
    va_end(ap);
    return ret;
}