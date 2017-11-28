void
Snmp::Pdu::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.putPod(command);
    msg.putPod(address);
    msg.putPod(reqid);
    msg.putPod(errstat);
    msg.putPod(errindex);
    msg.putPod(non_repeaters);
    msg.putPod(max_repetitions);
    msg.putInt(enterprise_length);
    if (enterprise_length > 0) {
        Must(enterprise != NULL);
        msg.putFixed(enterprise, enterprise_length * sizeof(oid));
    }
    msg.putPod(agent_addr);
    msg.putPod(trap_type);
    msg.putPod(specific_type);
    msg.putPod(time);
    msg.putInt(varCount());
    for (variable_list* var = variables; var != NULL; var = var->next_variable)
        static_cast<Var*>(var)->pack(msg);
}