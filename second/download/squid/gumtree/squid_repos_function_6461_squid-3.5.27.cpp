void
Snmp::Var::setString(const Range<const u_char*>& string)
{
    setValue(string.start, string.size(), SMI_STRING);
}