int
EventScheduler::checkEvents(int)
{
    int result = timeRemaining();
    if (result != 0)
        return result;

    PROF_start(eventRun);

    do {
        ev_entry *event = tasks;
        assert(event);

        /* XXX assumes event->name is static memory! */
        AsyncCall::Pointer call = asyncCall(41,5, event->name,
                                            EventDialer(event->func, event->arg, event->cbdata));
        ScheduleCallHere(call);

        last_event_ran = event->name; // XXX: move this to AsyncCallQueue
        const bool heavy = event->weight &&
                           (!event->cbdata || cbdataReferenceValid(event->arg));

        tasks = event->next;
        delete event;

        result = timeRemaining();

        // XXX: We may be called again during the same event loop iteration.
        // Is there a point in breaking now?
        if (heavy)
            break; // do not dequeue events following a heavy event
    } while (result == 0);

    PROF_stop(eventRun);
    return result;
}