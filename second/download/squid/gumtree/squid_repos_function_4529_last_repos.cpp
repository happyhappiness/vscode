void
Store::Disks::updateLimits()
{
    largestMinimumObjectSize = -1;
    largestMaximumObjectSize = -1;
    secondLargestMaximumObjectSize = -1;

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        const auto &disk = dir(i);
        if (!disk.active())
            continue;

        if (disk.minObjectSize() > largestMinimumObjectSize)
            largestMinimumObjectSize = disk.minObjectSize();

        const auto diskMaxObjectSize = disk.maxObjectSize();
        if (diskMaxObjectSize > largestMaximumObjectSize) {
            if (largestMaximumObjectSize >= 0) // was set
                secondLargestMaximumObjectSize = largestMaximumObjectSize;
            largestMaximumObjectSize = diskMaxObjectSize;
        }
    }
}