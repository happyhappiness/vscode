bool Ssl::sslDateIsInTheFuture(char const * date)
{
    ASN1_UTCTIME tm;
    tm.flags = 0;
    tm.type = 23;
    tm.data = (unsigned char *)date;
    tm.length = strlen(date);

    return (X509_cmp_current_time(&tm) > 0);
}