Range<const oid*>
Snmp::Var::asObject() const
{
    Must(type == SMI_OBJID);
    Must(val_len % sizeof(oid) == 0);
    int length = val_len / sizeof(oid);
    Must(val.objid != NULL && length > 0);
    return Range<const oid*>(val.objid, val.objid + length);
}