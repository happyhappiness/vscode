static Runners &
GetRunners(const RunnerRegistry &registryId)
{
    if (!TheRegistries)
        TheRegistries = new Registries;

    if (TheRegistries->find(registryId) == TheRegistries->end())
        (*TheRegistries)[registryId] = new Runners;

    return *(*TheRegistries)[registryId];
}