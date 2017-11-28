    if (url.size())
        fatal ("Cannot search by url yet\n");

    return new StoreSearchHashIndex (this);
}

bool
StoreHashIndex::smpAware() const
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

CBDATA_CLASS_INIT(StoreSearchHashIndex);

StoreSearchHashIndex::StoreSearchHashIndex(RefCount<StoreHashIndex> aSwapDir) :
    sd(aSwapDir),
    callback(NULL),
    cbdata(NULL),
    _done(false),
    bucket(0)
{}

/* do not link
StoreSearchHashIndex::StoreSearchHashIndex(StoreSearchHashIndex const &);
*/

