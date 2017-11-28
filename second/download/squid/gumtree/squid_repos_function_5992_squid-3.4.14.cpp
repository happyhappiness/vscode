bool
Snmp::Inquirer::doneAll() const
{
    return !writer && Ipc::Inquirer::doneAll();
}