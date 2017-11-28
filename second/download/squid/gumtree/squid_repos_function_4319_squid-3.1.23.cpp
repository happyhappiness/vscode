void
ACLChecklist::nonBlockingCheck(PF * callback_, void *callback_data_)
{
    callback = callback_;
    callback_data = cbdataReference(callback_data_);
    check();
}