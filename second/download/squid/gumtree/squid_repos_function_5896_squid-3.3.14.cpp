Ipc::Response::Pointer
Snmp::Response::clone() const
{
    return new Response(*this);
}