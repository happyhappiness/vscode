Range<const oid*>
Snmp::Var::getName() const
{
    return Range<const oid*>(name, name + name_length);
}