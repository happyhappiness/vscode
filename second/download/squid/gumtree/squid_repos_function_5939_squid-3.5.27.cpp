int
DeregisterRunner(RegisteredRunner *rr)
{
    Runners &runners = GetRunners();
    runners.erase(rr);
    return runners.size();
}