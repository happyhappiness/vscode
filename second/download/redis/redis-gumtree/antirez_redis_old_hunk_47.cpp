    uint32_t totlen = ntohl(hdr->totlen);
    uint16_t type = ntohs(hdr->type);

    server.cluster->stats_bus_messages_received++;
    serverLog(LL_DEBUG,"--- Processing packet of type %d, %lu bytes",
        type, (unsigned long) totlen);

