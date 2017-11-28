void Adaptation::Icap::ServiceRep::scheduleUpdate(time_t when)
{
    if (updateScheduled) {
        debugs(93,7, HERE << "reschedules update");
        // XXX: check whether the event is there because AR saw
        // an unreproducible eventDelete assertion on 2007/06/18
        if (eventFind(&ServiceRep_noteTimeToUpdate, this))
            eventDelete(&ServiceRep_noteTimeToUpdate, this);
        else
            debugs(93,1, "XXX: ICAP service lost an update event.");
        updateScheduled = false;
    }

    debugs(93,7, HERE << "raw OPTIONS fetch at " << when << " or in " <<
           (when - squid_curtime) << " sec");
    debugs(93,9, HERE << "last fetched at " << theLastUpdate << " or " <<
           (squid_curtime - theLastUpdate) << " sec ago");

    /* adjust update time to prevent too-frequent updates */

    if (when < squid_curtime)
        when = squid_curtime;

    // XXX: move hard-coded constants from here to Adaptation::Icap::TheConfig
    const int minUpdateGap = 30; // seconds
    if (when < theLastUpdate + minUpdateGap)
        when = theLastUpdate + minUpdateGap;

    const int delay = when - squid_curtime;
    debugs(93,5, HERE << "will fetch OPTIONS in " << delay << " sec");

    eventAdd("Adaptation::Icap::ServiceRep::noteTimeToUpdate",
             &ServiceRep_noteTimeToUpdate, this, delay, 0, true);
    updateScheduled = true;
}