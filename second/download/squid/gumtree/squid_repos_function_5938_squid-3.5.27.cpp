int
RegisterRunner(RegisteredRunner *rr)
{
    Runners &runners = GetRunners();
    runners.insert(rr);
    return runners.size();
}