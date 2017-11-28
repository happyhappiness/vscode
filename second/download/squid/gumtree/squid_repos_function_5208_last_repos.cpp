bool
Client::abortOnData(const char *reason)
{
    abortAll(reason);
    return true;
}