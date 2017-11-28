void
Snmp::Var::setCounter64(long long int counter)
{
    setValue(&counter, sizeof(counter), SMI_COUNTER64);
}