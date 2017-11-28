void
Snmp::Var::clearName()
{
    if (name != NULL) {
        xfree(name);
        name = NULL;
    }
    name_length = 0;
}