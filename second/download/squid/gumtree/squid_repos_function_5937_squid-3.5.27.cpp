static Runners &
GetRunners()
{
    if (!TheRunners)
        TheRunners = new Runners;
    return *TheRunners;
}