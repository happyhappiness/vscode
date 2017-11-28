void
DeactivateRegistered(const RunnerRegistry &registryId)
{
    Runners &runners = GetRunners(registryId);
    while (!runners.empty()) {
        delete runners.back();
        runners.pop_back();
    }
}