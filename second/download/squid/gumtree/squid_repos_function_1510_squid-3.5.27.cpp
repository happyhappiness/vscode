void
icpCreateAndSend(icp_opcode opcode, int flags, char const *url, int reqnum, int pad, int fd, const Ip::Address &from)
{
    icp_common_t *reply = _icp_common_t::createMessage(opcode, flags, url, reqnum, pad);
    icpUdpSend(fd, from, reply, icpLogFromICPCode(opcode), 0);
}