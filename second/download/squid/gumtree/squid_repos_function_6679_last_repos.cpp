void
Snmp::Inquirer::handleException(const std::exception& e)
{
    aggrPdu.errstat = SNMP_ERR_GENERR;
    Ipc::Inquirer::handleException(e);
}