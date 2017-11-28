void
Comm::ConnOpener::cancelSleep()
{
    if (calls_.sleep_) {
        // It would be nice to delete the sleep event, but it might be out of
        // the event queue and in the async queue already, so (a) we do not know
        // whether we can safely delete the call ptr here and (b) eventDelete()
        // will assert if the event went async. Thus, we let the event run so
        // that it deletes the call ptr [after this job is gone]. Note that we
        // are called only when the job ends so this "hanging event" will do
        // nothing but deleting the call ptr.  TODO: Revise eventDelete() API.
        // eventDelete(Comm::ConnOpener::DelayedConnectRetry, calls_.sleep);
        calls_.sleep_ = false;
        debugs(5, 9, conn_ << " stops sleeping");
    }
}