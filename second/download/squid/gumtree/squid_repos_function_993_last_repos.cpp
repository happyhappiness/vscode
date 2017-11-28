void
EventScheduler::clean()
{
    while (ev_entry * event = tasks) {
        tasks = event->next;
        delete event;
    }

    tasks = NULL;
}