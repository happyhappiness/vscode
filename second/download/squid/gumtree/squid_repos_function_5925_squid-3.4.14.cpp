Snmp::Var&
Snmp::Var::operator = (const Var& var)
{
    clear();
    assign(var);
    return *this;
}