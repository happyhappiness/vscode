static void
icpPktDump(icp_common_t * pkt)
{

    IpAddress a;

    debugs(12, 9, "opcode:     " << std::setw(3) << pkt->opcode  << " " << icp_opcode_str[pkt->opcode]);
    debugs(12, 9, "version: "<< std::left << std::setw(8) << pkt->version);
    debugs(12, 9, "length:  "<< std::left << std::setw(8) << ntohs(pkt->length));
    debugs(12, 9, "reqnum:  "<< std::left << std::setw(8) << ntohl(pkt->reqnum));
    debugs(12, 9, "flags:   "<< std::left << std::hex << std::setw(8) << ntohl(pkt->flags));
    a = (struct in_addr)pkt->shostid;
    debugs(12, 9, "shostid: " << a );
    debugs(12, 9, "payload: " << (char *) pkt + sizeof(icp_common_t));
}