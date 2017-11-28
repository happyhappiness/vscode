void
ACLFilledChecklist::operator delete (void *address)
{
    ACLFilledChecklist *t = static_cast<ACLFilledChecklist *>(address);
    cbdataFree(t);
}