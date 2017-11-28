void
RunRegistered(const RegisteredRunner::Method &m)
{
    Runners &runners = GetRunners();
    typedef Runners::iterator RRI;
    for (RRI i = runners.begin(); i != runners.end(); ++i)
        ((*i)->*m)();

    if (m == &RegisteredRunner::finishShutdown) {
        delete TheRunners;
        TheRunners = NULL;
    }
}