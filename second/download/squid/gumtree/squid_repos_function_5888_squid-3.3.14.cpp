Range<const oid*>
Snmp::Pdu::getSystemOid() const
{
    return Range<const oid*>(enterprise, enterprise + enterprise_length);
}