const char *
api_errstring(int snmp_errnumber)
{
    return (snmp_api_error(snmp_errnumber));
}