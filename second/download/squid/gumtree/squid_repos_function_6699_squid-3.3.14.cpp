void
rfc1035RRDestroy(rfc1035_rr ** rr, int n)
{
    if (*rr == NULL) {
        return;
    }

    while (n-- > 0) {
        if ((*rr)[n].rdata)
            xfree((*rr)[n].rdata);
    }
    xfree(*rr);
    *rr = NULL;
}