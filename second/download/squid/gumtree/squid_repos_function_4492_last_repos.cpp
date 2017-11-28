void
Store::Disk::maxObjectSize(int64_t newMax)
{
    // negative values mean no limit (-1)
    if (newMax < 0) {
        max_objsize = -1; // set explicitly in case it had a non-default value previously
        return;
    }

    // prohibit values greater than total storage area size
    // but set max_objsize to the maximum allowed to override maximum_object_size global config
    if (static_cast<uint64_t>(newMax) > maxSize()) {
        debugs(47, DBG_PARSE_NOTE(2), "WARNING: Ignoring 'max-size' option for " << path <<
               " which is larger than total cache_dir size of " << maxSize() << " bytes.");
        max_objsize = maxSize();
        return;
    }

    max_objsize = newMax;
}