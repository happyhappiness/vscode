int
EventScheduler::checkEvents(int timeout)
{

    ev_entry *event = NULL;

    if (NULL == tasks)
        return checkDelay();

    if (tasks->when > current_dtime)
        return checkDelay();

    PROF_start(eventRun);

    debugs(41, 5, HERE << "checkEvents");

    while ((event = tasks)) {
        if (event->when > current_dtime)
            break;

        /* XXX assumes event->name is static memory! */
        AsyncCall::Pointer call = asyncCall(41,5, event->name,
                                            EventDialer(event->func, event->arg, event->cbdata));
        ScheduleCallHere(call);

        last_event_ran = event->name; // XXX: move this to AsyncCallQueue
        const bool heavy = event->weight &&
                           (!event->cbdata || cbdataReferenceValid(event->arg));

        tasks = event->next;
        delete event;

        // XXX: We may be called again during the same event loop iteration.
        // Is there a point in breaking now?
        if (heavy)
            break; // do not dequeue events following a heavy event
    }

    PROF_stop(eventRun);
    return checkDelay();
}