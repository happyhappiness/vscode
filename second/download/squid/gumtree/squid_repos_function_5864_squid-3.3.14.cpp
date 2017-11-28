void
Snmp::Var::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.putInt(name_length);
    if (name_length > 0) {
        Must(name != NULL);
        msg.putFixed(name, name_length * sizeof(oid));
    }
    msg.putPod(type);
    msg.putPod(val_len);
    if (val_len > 0) {
        Must(val.string != NULL);
        msg.putFixed(val.string, val_len);
    }
}