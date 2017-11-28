void
eventDelete(EVH * func, void *arg)
{
    EventScheduler::GetInstance()->cancel(func, arg);
}