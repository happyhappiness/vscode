time_t
Adaptation::Icap::ServiceRep::optionsFetchTime() const
{
    if (theOptions && theOptions->valid()) {
        const time_t expire = theOptions->expire();
        debugs(93,7, HERE << "options expire on " << expire << " >= " << squid_curtime);

        // conservative estimate of how long the OPTIONS transaction will take
        // XXX: move hard-coded constants from here to Adaptation::Icap::TheConfig
        const int expectedWait = 20; // seconds

        // Unknown or invalid (too small) expiration times should not happen.
        // Adaptation::Icap::Options should use the default TTL, and ICAP servers should not
        // send invalid TTLs, but bugs and attacks happen.
        if (expire < expectedWait)
            return squid_curtime;
        else
            return expire - expectedWait; // before the current options expire
    }

    // use revival delay as "expiration" time for a service w/o valid options
    return squid_curtime + TheConfig.service_revival_delay;
}