void
Snmp::Pdu::unpack(const Ipc::TypedMsgHdr& msg)
{
    clear();
    msg.getPod(command);
    msg.getPod(address);
    msg.getPod(reqid);
    msg.getPod(errstat);
    msg.getPod(errindex);
    msg.getPod(non_repeaters);
    msg.getPod(max_repetitions);
    enterprise_length = msg.getInt();
    if (enterprise_length > 0) {
        enterprise = static_cast<oid*>(xmalloc(enterprise_length * sizeof(oid)));
        msg.getFixed(enterprise, enterprise_length * sizeof(oid));
    }
    msg.getPod(agent_addr);
    msg.getPod(trap_type);
    msg.getPod(specific_type);
    msg.getPod(time);
    int count = msg.getInt();
    for (variable_list** p_var = &variables; count > 0;
            p_var = &(*p_var)->next_variable, --count) {
        Var* var = new Var();
        var->unpack(msg);
        *p_var = var;
    }
}