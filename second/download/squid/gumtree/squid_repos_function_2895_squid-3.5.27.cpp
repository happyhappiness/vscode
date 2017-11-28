void
parse_wccp2_service_info(void *v)
{
    char *t, *end;
    int service_id = 0;
    int flags = 0;
    int portlist[WCCP2_NUMPORTS];
    int protocol = -1;      /* IPPROTO_TCP | IPPROTO_UDP */

    struct wccp2_service_list_t *srv;
    int priority = -1;

    if (wccp2_connected == 1) {
        debugs(80, DBG_IMPORTANT, "WCCPv2: Somehow reparsing the configuration without having shut down WCCP! Try reloading squid again.");
        return;
    }

    debugs(80, 5, "parse_wccp2_service_info: called");
    memset(portlist, 0, sizeof(portlist));
    /* First argument: id */
    service_id = GetInteger();

    if (service_id < 0 || service_id > 255) {
        debugs(80, DBG_CRITICAL, "ERROR: invalid WCCP service id " << service_id << " (must be between 0 .. 255)");
        self_destruct();
    }

    /* Next: find the (hopefully!) existing service */
    srv = wccp2_get_service_by_id(WCCP2_SERVICE_DYNAMIC, service_id);

    if (srv == NULL) {
        fatalf("parse_wccp2_service_info: unknown dynamic service id %d: you need to define it using wccp2_service (and make sure you wish to configure it as a dynamic service.)\n", service_id);
    }

    /* Next: loop until we don't have any more tokens */
    while ((t = ConfigParser::NextToken()) != NULL) {
        if (strncmp(t, "flags=", 6) == 0) {
            /* XXX eww, string pointer math */
            flags = parse_wccp2_service_flags(t + 6);
        } else if (strncmp(t, "ports=", 6) == 0) {
            parse_wccp2_service_ports(t + 6, portlist);
            flags |= WCCP2_SERVICE_PORTS_DEFINED;
        } else if (strncmp(t, "protocol=tcp", 12) == 0) {
            protocol = IPPROTO_TCP;
        } else if (strncmp(t, "protocol=udp", 12) == 0) {
            protocol = IPPROTO_UDP;
        } else if (strncmp(t, "protocol=", 9) == 0) {
            fatalf("parse_wccp2_service_info: id %d: unknown protocol (%s) - must be tcp or udp!\n", service_id, t);
        } else if (strncmp(t, "priority=", 9) == 0) {
            priority = strtol(t + 9, &end, 0);

            if (priority < 0 || priority > 255) {
                fatalf("parse_wccp2_service_info: id %d: %s out of range (0..255)!\n", service_id, t);
            }
        } else {
            fatalf("parse_wccp2_service_info: id %d: unknown option '%s'\n", service_id, t);
        }
    }

    /* Check everything is set */
    if (priority == -1) {
        fatalf("parse_wccp2_service_info: service %d: no priority defined (valid: 0..255)!\n", service_id);
    }

    if (protocol == -1) {
        fatalf("parse_wccp2_service_info: service %d: no protocol defined (valid: tcp or udp)!\n", service_id);
    }

    if (!(flags & WCCP2_SERVICE_PORTS_DEFINED)) {
        fatalf("parse_wccp2_service_info: service %d: no ports defined!\n", service_id);
    }

    /* rightio! now we can update */
    wccp2_update_service(srv, WCCP2_SERVICE_DYNAMIC, service_id, priority,
                         protocol, flags, portlist);

    /* Done! */
}