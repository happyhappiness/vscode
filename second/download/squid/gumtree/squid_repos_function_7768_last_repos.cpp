const char *
snmp_errstring(int errstat)
{
    if ((errstat <= (SNMP_ERR_INCONSISTENTNAME)) &&
            (errstat >= (SNMP_ERR_NOERROR))) {
        return error_string[errstat];
    } else {
        return "Unknown Error";
    }
}