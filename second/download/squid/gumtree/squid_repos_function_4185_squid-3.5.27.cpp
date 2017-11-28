void Adaptation::Icap::VirginBodyAct::plan()
{
    Must(!disabled());
    Must(!theStart); // not started
    theState = stActive;
}