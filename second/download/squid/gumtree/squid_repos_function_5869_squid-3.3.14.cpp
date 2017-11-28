void
Snmp::Session::clear()
{
    memset(this, 0, sizeof(*this));
}