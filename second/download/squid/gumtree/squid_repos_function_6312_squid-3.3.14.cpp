void
Ipc::Inquirer::RequestTimedOut(void* param)
{
    debugs(54, 3, HERE);
    Must(param != NULL);
    Inquirer* cmi = static_cast<Inquirer*>(param);
    // use async call to enable job call protection that time events lack
    CallJobHere(54, 5, cmi, Inquirer, requestTimedOut);
}