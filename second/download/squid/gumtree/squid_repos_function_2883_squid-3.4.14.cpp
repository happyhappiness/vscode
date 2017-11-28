static int
parse_wccp2_service_flags(char *flags)
{
    if (!flags)
        return 0;

    char *flag = flags;
    int retflag = 0;

    while (size_t len = strcspn(flag, ",")) {

        if (strncmp(flag, "src_ip_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_SRC_IP_HASH;
        } else if (strncmp(flag, "dst_ip_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_DST_IP_HASH;
        } else if (strncmp(flag, "source_port_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_SRC_PORT_HASH;
        } else if (strncmp(flag, "dst_port_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_DST_PORT_HASH;
        } else if (strncmp(flag, "ports_source", len) == 0) {
            retflag |= WCCP2_SERVICE_PORTS_SOURCE;
        } else if (strncmp(flag, "src_ip_alt_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_SRC_IP_ALT_HASH;
        } else if (strncmp(flag, "dst_ip_alt_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_DST_IP_ALT_HASH;
        } else if (strncmp(flag, "src_port_alt_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_SRC_PORT_ALT_HASH;
        } else if (strncmp(flag, "dst_port_alt_hash", len) == 0) {
            retflag |= WCCP2_SERVICE_DST_PORT_ALT_HASH;
        } else {
            flag[len] = '\0';
            fatalf("Unknown wccp2 service flag: %s\n", flag);
        }

        if (flag[len] == '\0')
            break;

        flag += len+1;
    }

    return retflag;
}