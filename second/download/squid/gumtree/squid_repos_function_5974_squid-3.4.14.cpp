void
Snmp::Pdu::assign(const Pdu& pdu)
{
    command = pdu.command;
    address.sin_addr.s_addr = pdu.address.sin_addr.s_addr;
    reqid = pdu.reqid;
    errstat = pdu.errstat;
    errindex = pdu.errindex;
    non_repeaters = pdu.non_repeaters;
    max_repetitions = pdu.max_repetitions;
    agent_addr.sin_addr.s_addr = pdu.agent_addr.sin_addr.s_addr;
    trap_type = pdu.trap_type;
    specific_type = pdu.specific_type;
    time = pdu.time;
    aggrCount = pdu.aggrCount;
    setSystemOid(pdu.getSystemOid());
    setVars(pdu.variables);
}