void Ssl::ErrorDetail::buildDetail() const
{
    char const *s = NULL;
    char const *p;
    char const *t;
    int code_len = 0;

    if (ErrorDetailsManager::GetInstance().getErrorDetail(error_no, request, detailEntry))
        s = detailEntry.detail.termedBuf();

    if (!s)
        s = SslErrorDetailDefaultStr;

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