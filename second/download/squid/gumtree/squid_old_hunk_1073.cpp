    bool full() const; ///< no more entries can be stored without purging
    void trackReferences(StoreEntry &e); ///< add to replacement policy scope
    void ignoreReferences(StoreEntry &e); ///< delete from repl policy scope

    int64_t diskOffsetLimit() const;

    void anchorEntry(StoreEntry &e, const sfileno filen, const Ipc::StoreMapAnchor &anchor);
    bool updateCollapsedWith(StoreEntry &collapsed, const Ipc::StoreMapAnchor &anchor);

    friend class Rebuild;
    friend class IoState;
    const char *filePath; ///< location of cache storage file inside path/
    DirMap *map; ///< entry key/sfileno to MaxExtras/inode mapping

private:
    void createError(const char *const msg);

