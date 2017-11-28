        /* priority */
        storeAppendPrintf(e, " priority=%d", srv->info.service_priority);

        /* flags */
        flags = ntohl(srv->info.service_flags);

        bool comma = false;
        if (flags != 0) {
            storeAppendPrintf(e, " flags=");

            if (flags & WCCP2_SERVICE_SRC_IP_HASH) {
                storeAppendPrintf(e, "src_ip_hash");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_DST_IP_HASH) {
                storeAppendPrintf(e, "%sdst_ip_hash", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_SRC_PORT_HASH) {
                storeAppendPrintf(e, "%ssource_port_hash", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_DST_PORT_HASH) {
                storeAppendPrintf(e, "%sdst_port_hash", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_PORTS_DEFINED) {
                storeAppendPrintf(e, "%sports_defined", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_PORTS_SOURCE) {
                storeAppendPrintf(e, "%sports_source", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_SRC_IP_ALT_HASH) {
                storeAppendPrintf(e, "%ssrc_ip_alt_hash", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_DST_IP_ALT_HASH) {
                storeAppendPrintf(e, "%ssrc_ip_alt_hash", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_SRC_PORT_ALT_HASH) {
                storeAppendPrintf(e, "%ssrc_port_alt_hash", comma ? "," : "");
                comma = true;
            }

            if (flags & WCCP2_SERVICE_DST_PORT_ALT_HASH) {
                storeAppendPrintf(e, "%sdst_port_alt_hash", comma ? "," : "");
                //comma = true; // uncomment if more options added
            }
        }

        /* ports */
        comma = false;

        if (srv->info.port0 != 0) {
            storeAppendPrintf(e, " ports=%d", ntohs(srv->info.port0));
            comma = true;
        }

        if (srv->info.port1 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port1));
            comma = true;
        }

        if (srv->info.port2 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port2));
            comma = true;
        }

        if (srv->info.port3 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port3));
            comma = true;
        }

        if (srv->info.port4 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port4));
            comma = true;
        }

        if (srv->info.port5 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port5));
            comma = true;
        }

        if (srv->info.port6 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port6));
            comma = true;
        }

        if (srv->info.port7 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port7));
            // comma = true; // uncomment if more options are added
        }

        /* protocol */
        storeAppendPrintf(e, " protocol=%s", (srv->info.service_protocol == IPPROTO_TCP) ? "tcp" : "udp");

        storeAppendPrintf(e, "\n");
