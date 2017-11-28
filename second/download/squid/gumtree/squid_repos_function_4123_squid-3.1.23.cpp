void Ssl::ErrorDetail::buildDetail() const
{
    char const *s = getErrorDetail(error_no);
    char const *p;
    char const *t;
    int code_len = 0;

    assert(s);
    while ((p = strchr(s, '%'))) {
        errDetailStr.append(s, p - s);
        code_len = convert(++p, &t);
        if (code_len)
            errDetailStr.append(t);
        else
            errDetailStr.append("%");
        s = p + code_len;
    }
    errDetailStr.append(s, strlen(s));
}