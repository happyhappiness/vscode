static inline void
RegisterRunner_(RegisteredRunner *rr)
{
    Runners *runners = FindRunners();
    Must(runners);
    runners->insert(rr);
}