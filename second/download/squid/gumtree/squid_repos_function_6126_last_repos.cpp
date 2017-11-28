bool AsyncJob::done() const
{
    // stopReason, set in mustStop(), overwrites all other conditions
    return stopReason != NULL || doneAll();
}