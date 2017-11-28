static int
parse_wccp2_service_flags(char *flags)
{
    char *tmp, *tmp2;
    char *flag;
    int retflag = 0;

    if (!flags) {
        return 0;
    }

    tmp = xstrdup(flags);
    tmp2 = tmp;

    flag = strsep(&tmp2, ",");

    while (flag) {
        if (strcmp(flag, "src_ip_hash") == 0) {
            retflag |= WCCP2_SERVICE_SRC_IP_HASH;
        } else if (strcmp(flag, "dst_ip_hash") == 0) {
            retflag |= WCCP2_SERVICE_DST_IP_HASH;
        } else if (strcmp(flag, "source_port_hash") == 0) {
            retflag |= WCCP2_SERVICE_SRC_PORT_HASH;
        } else if (strcmp(flag, "dst_port_hash") == 0) {
            retflag |= WCCP2_SERVICE_DST_PORT_HASH;
        } else if (strcmp(flag, "ports_source") == 0) {
            retflag |= WCCP2_SERVICE_PORTS_SOURCE;
        } else if (strcmp(flag, "src_ip_alt_hash") == 0) {
            retflag |= WCCP2_SERVICE_SRC_IP_ALT_HASH;
        } else if (strcmp(flag, "dst_ip_alt_hash") == 0) {
            retflag |= WCCP2_SERVICE_DST_IP_ALT_HASH;
        } else if (strcmp(flag, "src_port_alt_hash") == 0) {
            retflag |= WCCP2_SERVICE_SRC_PORT_ALT_HASH;
        } else if (strcmp(flag, "dst_port_alt_hash") == 0) {
            retflag |= WCCP2_SERVICE_DST_PORT_ALT_HASH;
        } else {
            fatalf("Unknown wccp2 service flag: %s\n", flag);
        }

        flag = strsep(&tmp2, ",");
    }

    xfree(tmp);
    return retflag;
}