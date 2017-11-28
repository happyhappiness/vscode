int
ActivateRegistered(const RunnerRegistry &registryId)
{
    Runners &runners = GetRunners(registryId);
    typedef Runners::iterator RRI;
    for (RRI i = runners.begin(); i != runners.end(); ++i)
        (*i)->run(registryId);
    return runners.size();
}