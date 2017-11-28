Snmp::Session&
Snmp::Session::operator = (const Session& session)
{
    free();
    assign(session);
    return *this;
}