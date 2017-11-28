int
RegisterRunner(const RunnerRegistry &registryId, RegisteredRunner *rr)
{
    Runners &runners = GetRunners(registryId);
    runners.push_back(rr);
    return runners.size();
}