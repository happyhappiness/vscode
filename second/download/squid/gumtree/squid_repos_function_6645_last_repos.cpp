void
Snmp::Var::unpack(const Ipc::TypedMsgHdr& msg)
{
    clearName();
    clearValue();
    name_length = msg.getInt();
    Must(name_length >= 0);
    if (name_length > 0) {
        name = static_cast<oid*>(xmalloc(name_length * sizeof(oid)));
        msg.getFixed(name, name_length * sizeof(oid));
    }
    msg.getPod(type);
    val_len = msg.getInt();
    Must(val_len >= 0);
    if (val_len > 0) {
        val.string = static_cast<u_char*>(xmalloc(val_len));
        msg.getFixed(val.string, val_len);
    }
}