void Adaptation::Icap::ServiceRep::checkOptions()
{
    if (theOptions == NULL)
        return;

    if (!theOptions->valid()) {
        debugs(93, DBG_IMPORTANT, "WARNING: Squid got an invalid ICAP OPTIONS response " <<
               "from service " << cfg().uri << "; error: " << theOptions->error);
        return;
    }

    /*
     * Issue a warning if the ICAP server returned methods in the
     * options response that don't match the method from squid.conf.
     */

    if (!theOptions->methods.empty()) {
        bool method_found = false;
        String method_list;
        Vector <ICAP::Method>::iterator iter = theOptions->methods.begin();

        while (iter != theOptions->methods.end()) {

            if (*iter == cfg().method) {
                method_found = true;
                break;
            }

            method_list.append(ICAP::methodStr(*iter));
            method_list.append(" ", 1);
            ++iter;
        }

        if (!method_found) {
            debugs(93, DBG_IMPORTANT, "WARNING: Squid is configured to use ICAP method " <<
                   cfg().methodStr() <<
                   " for service " << cfg().uri <<
                   " but OPTIONS response declares the methods are " << method_list);
        }
    }

    /*
     *  Check the ICAP server's date header for clock skew
     */
    const int skew = (int)(theOptions->timestamp() - squid_curtime);
    if (abs(skew) > theOptions->ttl()) {
        // TODO: If skew is negative, the option will be considered down
        // because of stale options. We should probably change this.
        debugs(93, DBG_IMPORTANT, "ICAP service's clock is skewed by " << skew <<
               " seconds: " << cfg().uri);
    }
}