void
Snmp::Var::setObject(const Range<const oid*>& object)
{
    setValue(object.start, object.size() * sizeof(oid), SMI_OBJID);
}