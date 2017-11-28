void Adaptation::Iterator::start()
{
    Adaptation::Initiate::start();

    thePlan = ServicePlan(theGroup, filter());
    step();
}