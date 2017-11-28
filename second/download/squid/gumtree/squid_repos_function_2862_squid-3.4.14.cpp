static void
wccp2_update_service(struct wccp2_service_list_t *srv, int service,
                     int service_id, int service_priority, int service_proto, int service_flags,
                     int ports[])
{
    /* XXX check what needs to be wrapped in htons()! */
    srv->info.service = service;
    srv->info.service_id = service_id;
    srv->info.service_priority = service_priority;
    srv->info.service_protocol = service_proto;
    srv->info.service_flags = htonl(service_flags);
    srv->info.port0 = htons(ports[0]);
    srv->info.port1 = htons(ports[1]);
    srv->info.port2 = htons(ports[2]);
    srv->info.port3 = htons(ports[3]);
    srv->info.port4 = htons(ports[4]);
    srv->info.port5 = htons(ports[5]);
    srv->info.port6 = htons(ports[6]);
    srv->info.port7 = htons(ports[7]);
}