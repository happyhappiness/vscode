void
eventFreeMemory(void)
{
    EventScheduler::GetInstance()->clean();
}