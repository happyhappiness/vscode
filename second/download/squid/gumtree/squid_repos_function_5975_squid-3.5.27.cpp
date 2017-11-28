static void
logfileFlushEvent(void *data)
{
    Logfile *lf = static_cast<Logfile *>(data);

    /*
     * This might work better if we keep track of when we wrote last and only
     * schedule a write if we haven't done so in the last second or two.
     */
    logfileQueueWrite(lf);
    eventAdd("logfileFlush", logfileFlushEvent, lf, 1.0, 1);
}