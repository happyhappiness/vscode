void
ACLChecklist::asyncInProgress(bool const newAsync)
{
    assert (!finished() && !(asyncInProgress() && newAsync));
    async_ = newAsync;
    debugs(28, 3, "ACLChecklist::asyncInProgress: " << this <<
           " async set to " << async_);
}