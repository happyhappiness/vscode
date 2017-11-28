void
eventAdd(const char *name, EVH * func, void *arg, double when, int weight, bool cbdata)
{
    EventScheduler::GetInstance()->schedule(name, func, arg, when, weight, cbdata);
}