bool
Adaptation::ServiceGroup::findService(const ServiceFilter &filter, Pos &pos) const
{
    if (method != filter.method || point != filter.point) {
        debugs(93,5,HERE << id << " serves another location");
        return false; // assume other services have the same wrong location
    }

    // find the next interested service, skipping problematic ones if possible
    bool foundEssential = false;
    Pos essPos = 0;
    for (; has(pos); ++pos) {
        debugs(93,9,HERE << id << " checks service at " << pos);
        ServicePointer service = at(pos);

        if (!service)
            continue; // the service was lost due to reconfiguration

        if (!service->wants(filter))
            continue; // the service is not interested

        if (service->up() || !service->probed()) {
            debugs(93,9,HERE << id << " has matching service at " << pos);
            return true;
        }

        if (service->cfg().bypass) { // we can safely ignore bypassable downers
            debugs(93,9,HERE << id << " has bypassable service at " << pos);
            continue;
        }

        if (!allServicesSame) { // cannot skip (i.e., find best) service
            debugs(93,9,HERE << id << " has essential service at " << pos);
            return true;
        }

        if (!foundEssential) {
            debugs(93,9,HERE << id << " searches for best essential service from " << pos);
            foundEssential = true;
            essPos = pos;
        }
    }

    if (foundEssential) {
        debugs(93,9,HERE << id << " has best essential service at " << essPos);
        pos = essPos;
        return true;
    }

    debugs(93,5,HERE << id << " has no matching services");
    return false;
}