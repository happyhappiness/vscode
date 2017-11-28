void
Snmp::Var::setGauge(unsigned int value)
{
    setValue(&value, sizeof(value), SMI_GAUGE32);
}