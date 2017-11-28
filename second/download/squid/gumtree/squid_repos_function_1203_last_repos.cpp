static void StartUsingConfig()
{
    RunRegisteredHere(RegisteredRunner::claimMemoryNeeds);
    RunRegisteredHere(RegisteredRunner::useConfig);
}