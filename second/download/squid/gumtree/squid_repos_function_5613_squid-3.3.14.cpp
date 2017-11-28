bool
DiskdIOStrategy::shedLoad()
{
    /*
     * Fail on open() if there are too many requests queued.
     */

    if (away > magic1) {
        debugs(79, 3, "storeDiskdIO::shedLoad: Shedding, too many requests away");

        return true;
    }

    return false;
}