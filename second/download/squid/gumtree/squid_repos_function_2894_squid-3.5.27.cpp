static void
parse_wccp2_service_ports(char *options, int portlist[])
{
    if (!options) {
        return;
    }

    int i = 0;
    char *tmp = options;
    static char copy[10];

    while (size_t len = strcspn(tmp, ",")) {
        if (i >= WCCP2_NUMPORTS) {
            fatalf("parse_wccp2_service_ports: too many ports (maximum: 8) in list '%s'\n", options);
        }
        if (len > 6) { // 6 because "65535,"
            fatalf("parse_wccp2_service_ports: port value '%s' isn't valid (1..65535)\n", tmp);
        }

        memcpy(copy, tmp, len);
        copy[len] = '\0';
        int p = xatoi(copy);

        if (p < 1 || p > 65535) {
            fatalf("parse_wccp2_service_ports: port value '%s' isn't valid (1..65535)\n", tmp);
        }

        portlist[i] = p;
        ++i;
        if (tmp[len] == '\0')
            return;
        tmp += len+1;
    }
}