bool
Store::Disks::smpAware() const
{
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        // A mix is not supported, but we conservatively check every
        // dir because features like collapsed revalidation should
        // currently be disabled if any dir is SMP-aware
        if (dir(i).smpAware())
            return true;
    }
    return false;
}