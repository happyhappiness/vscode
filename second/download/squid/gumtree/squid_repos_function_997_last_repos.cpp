void
EventScheduler::schedule(const char *name, EVH * func, void *arg, double when, int weight, bool cbdata)
{
    // Use zero timestamp for when=0 events: Many of them are async calls that
    // must fire in the submission order. We cannot use current_dtime for them
    // because it may decrease if system clock is adjusted backwards.
    const double timestamp = when > 0.0 ? current_dtime + when : 0;
    ev_entry *event = new ev_entry(name, func, arg, timestamp, weight, cbdata);

    ev_entry **E;
    debugs(41, 7, HERE << "schedule: Adding '" << name << "', in " << when << " seconds");
    /* Insert after the last event with the same or earlier time */

    for (E = &tasks; *E; E = &(*E)->next) {
        if ((*E)->when > event->when)
            break;
    }

    event->next = *E;
    *E = event;
}