static u_int32_t ipstr2long(char *ip_str)
{
    char	buf[6];
    char	*ptr;
    int	i;
    int	count;
    u_int32_t	ipaddr;
    int	cur_byte;

    ipaddr = (u_int32_t)0;
    for (i = 0; i < 4; i++) {
        ptr = buf;
        count = 0;
        *ptr = '\0';
        while (*ip_str != '.' && *ip_str != '\0' && count < 4) {
            if (!isdigit((int)*ip_str)) {
                return((u_int32_t)0);
            }
            *ptr++ = *ip_str++;
            count++;
        }
        if (count >= 4 || count == 0) {
            return((u_int32_t)0);
        }
        *ptr = '\0';
        cur_byte = atoi(buf);
        if (cur_byte < 0 || cur_byte > 255) {
            return((u_int32_t)0);
        }
        ip_str++;
        ipaddr = ipaddr << 8 | (u_int32_t)cur_byte;
    }
    return(ipaddr);
}