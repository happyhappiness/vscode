static void
parse_wccp2_service_ports(char *options, int portlist[])
{
    int i = 0;
    int p;
    char *tmp, *tmp2, *port, *end;

    if (!options) {
        return;
    }

    tmp = xstrdup(options);
    tmp2 = tmp;

    port = strsep(&tmp2, ",");

    while (port && i < WCCP2_NUMPORTS) {
        p = strtol(port, &end, 0);

        if (p < 1 || p > 65535) {
            fatalf("parse_wccp2_service_ports: port value '%s' isn't valid (1..65535)\n", port);
        }

        portlist[i] = p;
        i++;
        port = strsep(&tmp2, ",");
    }

    if (i == WCCP2_NUMPORTS && port) {
        fatalf("parse_wccp2_service_ports: too many ports (maximum: 8) in list '%s'\n", options);
    }

    xfree(tmp);
}