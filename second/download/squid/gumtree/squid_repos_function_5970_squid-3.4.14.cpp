Snmp::Pdu&
Snmp::Pdu::operator = (const Pdu& pdu)
{
    clear();
    assign(pdu);
    return *this;
}