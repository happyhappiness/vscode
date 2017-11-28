Ipc::Request::Pointer
Snmp::Request::clone() const
{
    return new Request(*this);
}