void
Snmp::Var::assign(const Var& var)
{
    setName(var.getName());
    copyValue(var);
}