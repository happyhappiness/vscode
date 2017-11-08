static char *apr_ecvt(double arg, int ndigits, int *decpt, int *sign, char *buf)
{
    return (apr_cvt(arg, ndigits, decpt, sign, 1, buf));
}