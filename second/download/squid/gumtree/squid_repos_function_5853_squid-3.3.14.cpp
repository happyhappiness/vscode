Range<const u_char*>
Snmp::Var::asString() const
{
    Must(type == SMI_STRING);
    Must(val.string != NULL && val_len > 0);
    return Range<const u_char*>(val.string, val.string + val_len);
}