void
acl_ip_data::toStr(char *buf, int len) const
{
    char *b1 = buf;
    char *b2 = NULL;
    char *b3 = NULL;
    int rlen = 0;

    addr1.NtoA(b1, len - rlen );
    rlen = strlen(buf);
    b2 = buf + rlen;

    if (!addr2.IsAnyAddr()) {
        b2[0] = '-';
        rlen++;
        addr2.NtoA(&(b2[1]), len - rlen );
        rlen = strlen(buf);
    } else
        b2[0] = '\0';

    b3 = buf + rlen;

    if (!mask.IsNoAddr()) {
        b3[0] = '/';
        rlen++;
        int cidr =  mask.GetCIDR() - (addr1.IsIPv4()?96:0);
        snprintf(&(b3[1]), (len-rlen), "%u", (unsigned int)(cidr<0?0:cidr) );
    } else
        b3[0] = '\0';
}