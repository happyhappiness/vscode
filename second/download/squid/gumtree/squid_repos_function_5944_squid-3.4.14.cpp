void
Snmp::Var::setInt(int value)
{
    setValue(&value, sizeof(value), SMI_INTEGER);
}