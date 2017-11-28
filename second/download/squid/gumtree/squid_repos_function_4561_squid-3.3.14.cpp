void
ACLChecklist::nonBlockingCheck(ACLCB * callback_, void *callback_data_)
{
    preCheck("slow rules");
    callback = callback_;
    callback_data = cbdataReference(callback_data_);
    matchNonBlocking();
}