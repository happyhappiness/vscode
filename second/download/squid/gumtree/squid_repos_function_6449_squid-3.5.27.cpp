void
Snmp::Var::clearValue()
{
    if (val.string != NULL) {
        xfree(val.string);
        val.string = NULL;
    }
    val_len = 0;
    type = 0;
}