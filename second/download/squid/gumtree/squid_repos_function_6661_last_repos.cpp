void
Snmp::Pdu::init()
{
    memset(this, 0, sizeof(*this));
    errstat = SNMP_DEFAULT_ERRSTAT;
    errindex = SNMP_DEFAULT_ERRINDEX;
}