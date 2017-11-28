bool
ACLServerNameStrategy::valid() const
{
    int optionCount = 0;

    if (useClientRequested)
        optionCount++;
    if (useServerProvided)
        optionCount++;
    if (useConsensus)
        optionCount++;

    if (optionCount > 1) {
        debugs(28, DBG_CRITICAL, "ERROR: Multiple options given for the server_name ACL");
        return false;
    }
    return true;
}