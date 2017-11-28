void
Snmp::Var::copyValue(const Var& var)
{
    setValue(var.val.string, var.val_len, var.type);
}