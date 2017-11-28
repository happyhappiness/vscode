void
eventInit(void)
{
    Mgr::RegisterAction("events", "Event Queue", eventDump, 0, 1);
}