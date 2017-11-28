
        if (p < 1 || p > 65535) {
            fatalf("parse_wccp2_service_ports: port value '%s' isn't valid (1..65535)\n", port);
        }

        portlist[i] = p;
        ++i;
        port = strsep(&tmp2, ",");
    }

    if (i == WCCP2_NUMPORTS && port) {
        fatalf("parse_wccp2_service_ports: too many ports (maximum: 8) in list '%s'\n", options);
    }
