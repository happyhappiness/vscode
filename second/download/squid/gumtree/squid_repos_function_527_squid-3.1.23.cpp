const char *
snmp_api_error(int err)
{
    int foo = (err * -1);
    if ((foo < SNMPERR_GENERR) ||
            (foo > SNMPERR_LAST))
        foo = 0;

    return (api_errors[foo]);
}