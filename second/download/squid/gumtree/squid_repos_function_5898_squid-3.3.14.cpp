void
Snmp::Inquirer::start()
{
    debugs(49, 5, HERE);
    Ipc::Inquirer::start();
    Must(Comm::IsConnOpen(conn));
    inquire();
}