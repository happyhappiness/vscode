void
Snmp::Var::setCounter(int value)
{
    setValue(&value, sizeof(value), SMI_COUNTER32);
}