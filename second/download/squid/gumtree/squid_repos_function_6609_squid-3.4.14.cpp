bool
Mgr::Inquirer::doneAll() const
{
    return !writer && Ipc::Inquirer::doneAll();
}