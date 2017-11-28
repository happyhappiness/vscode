void
Snmp::Pdu::clear()
{
    clearSystemOid();
    clearVars();
    init();
}