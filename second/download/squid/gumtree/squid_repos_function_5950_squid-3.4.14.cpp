void
Snmp::Var::setTimeTicks(unsigned int ticks)
{
    setValue(&ticks, sizeof(ticks), SMI_TIMETICKS);
}