bool
Adaptation::Service::wants(const ServiceFilter &filter) const
{
    if (cfg().method != filter.method)
        return false;

    if (cfg().point != filter.point)
        return false;

    // sending a message to a broken service is likely to cause errors
    if (cfg().bypass && broken())
        return false;

    if (up()) {
        // Sending a message to a service that does not want it is useless.
        // note that we cannot check wantsUrl for service that is not "up"
        // note that even essential services are skipped on unwanted URLs!
        return wantsUrl(filter.request->url.path());
    }

    // The service is down and is either not bypassable or not probed due
    // to the bypass && broken() test above. Thus, we want to use it!
    return true;
}