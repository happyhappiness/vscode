static bool
AvoidSignalAction(const char *description, volatile int &signalVar)
{
    const char *avoiding = "delaying";
    const char *currentEvent = "none";
    if (shutting_down) {
        currentEvent = "shutdown";
        avoiding = "canceling";
        // do not avoid repeated shutdown signals
        // which just means the user wants to skip/abort shutdown timeouts
        if (strcmp(currentEvent, description) == 0)
            return false;
        signalVar = 0;
    }
    else if (!configured_once)
        currentEvent = "startup";
    else if (reconfiguring)
        currentEvent = "reconfiguration";
    else {
        signalVar = 0;
        return false; // do not avoid (i.e., execute immediately)
        // the caller may produce a signal-specific debugging message
    }

    debugs(1, DBG_IMPORTANT, avoiding << ' ' << description <<
           " request during " << currentEvent);
    return true;
}