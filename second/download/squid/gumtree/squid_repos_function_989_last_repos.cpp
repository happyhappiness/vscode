int
eventFind(EVH * func, void *arg)
{
    return EventScheduler::GetInstance()->find(func, arg);
}