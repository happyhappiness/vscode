void
Snmp::Pdu::clearSystemOid()
{
    if (enterprise != NULL) {
        xfree(enterprise);
        enterprise = NULL;
    }
    enterprise_length = 0;
}