static inline Runners *
FindRunners()
{
    if (!TheRunners && !RunnersGone)
        TheRunners = new Runners;
    return TheRunners;
}