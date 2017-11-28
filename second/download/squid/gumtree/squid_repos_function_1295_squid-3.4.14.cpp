bool
EventScheduler::find(EVH * func, void * arg)
{

    ev_entry *event;

    for (event = tasks; event != NULL; event = event->next) {
        if (event->func == func && event->arg == arg)
            return true;
    }

    return false;
}