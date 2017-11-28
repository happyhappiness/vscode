
    if (srv == NULL) {
        fatalf("parse_wccp2_service_info: unknown dynamic service id %d: you need to define it using wccp2_service (and make sure you wish to configure it as a dynamic service.)\n", service_id);
    }

    /* Next: loop until we don't have any more tokens */
    while ((t = strtok(NULL, w_space)) != NULL) {
        if (strncmp(t, "flags=", 6) == 0) {
            /* XXX eww, string pointer math */
            flags = parse_wccp2_service_flags(t + 6);
        } else if (strncmp(t, "ports=", 6) == 0) {
            parse_wccp2_service_ports(t + 6, portlist);
            flags |= WCCP2_SERVICE_PORTS_DEFINED;
