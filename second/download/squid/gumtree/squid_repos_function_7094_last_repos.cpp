void
Ipc::Inquirer::removeTimeoutEvent()
{
    if (eventFind(&Inquirer::RequestTimedOut, this))
        eventDelete(&Inquirer::RequestTimedOut, this);
}