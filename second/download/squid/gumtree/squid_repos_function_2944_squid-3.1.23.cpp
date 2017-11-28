void
StoreEntry::kickProducer()
{
    if (deferredProducer != NULL) {
        ScheduleCallHere(deferredProducer);
        deferredProducer = NULL;
    }
}