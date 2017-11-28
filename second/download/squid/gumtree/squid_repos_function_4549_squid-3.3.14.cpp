void
ACLChecklist::preCheck(const char *what)
{
    debugs(28, 3, HERE << this << " checking " << what);
    finished_ = false;
}