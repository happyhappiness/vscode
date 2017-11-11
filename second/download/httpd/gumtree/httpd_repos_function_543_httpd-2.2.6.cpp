static const char *unwrap_header(apr_pool_t *p, const char *hdr)
{
    if (ap_strchr_c(hdr, APR_ASCII_LF) || ap_strchr_c(hdr, APR_ASCII_CR)) {
        char *ptr;

        hdr = ptr = apr_pstrdup(p, hdr);

        do {
            if (*ptr == APR_ASCII_LF || *ptr == APR_ASCII_CR)
                *ptr = APR_ASCII_BLANK;
        } while (*ptr++);
    }
    return hdr;
}