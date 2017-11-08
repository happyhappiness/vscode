static APR_INLINE int ap_rputs(const char *str, request_rec *r)
{
    return ap_rwrite(str, (int)strlen(str), r);
}