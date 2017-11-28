    if (url.size())
        fatal ("Cannot search by url yet\n");

    return new StoreSearchHashIndex (this);
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

