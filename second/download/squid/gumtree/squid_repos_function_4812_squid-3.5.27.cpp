bool
ACLChecklist::callerGone()
{
    return !cbdataReferenceValid(callback_data);
}