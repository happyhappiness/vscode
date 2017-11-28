bool
Snmp::Inquirer::aggregate(Response::Pointer aResponse)
{
    Snmp::Response& response = static_cast<Snmp::Response&>(*aResponse);
    bool error = response.pdu.errstat != SNMP_ERR_NOERROR;
    if (error) {
        aggrPdu = response.pdu;
    } else {
        aggrPdu.aggregate(response.pdu);
    }
    return !error;
}