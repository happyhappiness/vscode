void
dump_wccp2_service_info(StoreEntry * e, const char *label, void *v)
{
    char comma;

    struct wccp2_service_list_t *srv;
    int flags;
    srv = wccp2_service_list_head;

    while (srv != NULL) {
        debugs(80, 3, "dump_wccp2_service_info: id " << srv->info.service_id << " (type " << srv->info.service << ")");

        /* We don't need to spit out information for standard services */

        if (srv->info.service == WCCP2_SERVICE_STANDARD) {
            debugs(80, 3, "dump_wccp2_service_info: id " << srv->info.service_id << ": standard service, not dumping info");

            /* XXX eww */
            srv = srv->next;
            continue;
        }

        storeAppendPrintf(e, "%s %d", label, srv->info.service_id);

        /* priority */
        storeAppendPrintf(e, " priority=%d", srv->info.service_priority);

        /* flags */
        flags = ntohl(srv->info.service_flags);

        if (flags != 0) {
            comma = 0;
            storeAppendPrintf(e, " flags=");

            if (flags & WCCP2_SERVICE_SRC_IP_HASH) {
                storeAppendPrintf(e, "%ssrc_ip_hash", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_DST_IP_HASH) {
                storeAppendPrintf(e, "%sdst_ip_hash", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_SRC_PORT_HASH) {
                storeAppendPrintf(e, "%ssource_port_hash", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_DST_PORT_HASH) {
                storeAppendPrintf(e, "%sdst_port_hash", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_PORTS_DEFINED) {
                storeAppendPrintf(e, "%sports_defined", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_PORTS_SOURCE) {
                storeAppendPrintf(e, "%sports_source", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_SRC_IP_ALT_HASH) {
                storeAppendPrintf(e, "%ssrc_ip_alt_hash", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_DST_IP_ALT_HASH) {
                storeAppendPrintf(e, "%ssrc_ip_alt_hash", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_SRC_PORT_ALT_HASH) {
                storeAppendPrintf(e, "%ssrc_port_alt_hash", comma ? "," : "");
                comma = 1;
            }

            if (flags & WCCP2_SERVICE_DST_PORT_ALT_HASH) {
                storeAppendPrintf(e, "%sdst_port_alt_hash", comma ? "," : "");
                comma = 1;
            }
        }

        /* ports */
        comma = 0;

        if (srv->info.port0 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : " ports=", ntohs(srv->info.port0));
            comma = 1;
        }

        if (srv->info.port1 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port1));
            comma = 1;
        }

        if (srv->info.port2 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port2));
            comma = 1;
        }

        if (srv->info.port3 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port3));
            comma = 1;
        }

        if (srv->info.port4 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port4));
            comma = 1;
        }

        if (srv->info.port5 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port5));
            comma = 1;
        }

        if (srv->info.port6 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port6));
            comma = 1;
        }

        if (srv->info.port7 != 0) {
            storeAppendPrintf(e, "%s%d", comma ? "," : "ports=", ntohs(srv->info.port7));
            comma = 1;
        }

        /* protocol */
        storeAppendPrintf(e, " protocol=%s", (srv->info.service_protocol == IPPROTO_TCP) ? "tcp" : "udp");

        storeAppendPrintf(e, "\n");

        srv = srv->next;
    }
}