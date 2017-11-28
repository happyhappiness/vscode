void
Snmp::Pdu::setSystemOid(const Range<const oid*>& systemOid)
{
    clearSystemOid();
    if (systemOid.start != NULL && systemOid.size() != 0) {
        enterprise_length = systemOid.size();
        enterprise = static_cast<oid*>(xmalloc(enterprise_length * sizeof(oid)));
        std::copy(systemOid.start, systemOid.end, enterprise);
    }
}