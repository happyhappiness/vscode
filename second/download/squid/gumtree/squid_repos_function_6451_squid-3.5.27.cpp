int
Snmp::Var::asInt() const
{
    Must(type == SMI_INTEGER);
    Must(val.integer != NULL && val_len == sizeof(int));
    return *val.integer;
}