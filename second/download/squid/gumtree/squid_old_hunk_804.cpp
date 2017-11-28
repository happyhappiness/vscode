    void parseSize(const bool reconfiguring); ///< parses anonymous cache_dir size option
    void validateOptions(); ///< warns of configuration problems; may quit
    bool parseTimeOption(char const *option, const char *value, int reconfiguring);
    void dumpTimeOption(StoreEntry * e) const;
    bool parseRateOption(char const *option, const char *value, int reconfiguring);
    void dumpRateOption(StoreEntry * e) const;

    void rebuild(); ///< starts loading and validating stored entry metadata
    ///< used to add entries successfully loaded during rebuild
    bool addEntry(const int fileno, const DbCellHeader &header, const StoreEntry &from);

    bool full() const; ///< no more entries can be stored without purging
    void trackReferences(StoreEntry &e); ///< add to replacement policy scope
    void ignoreReferences(StoreEntry &e); ///< delete from repl policy scope

    int64_t diskOffset(int filen) const;
    int64_t diskOffsetLimit() const;
    int entryLimit() const { return map->entryLimit(); }

    friend class Rebuild;
    const char *filePath; ///< location of cache storage file inside path/

private:
    DiskIOStrategy *io;
    RefCount<DiskFile> theFile; ///< cache storage for this cache_dir
    DirMap *map;

    /* configurable options */
    DiskFile::Config fileConfig; ///< file-level configuration options

    static const int64_t HeaderSize; ///< on-disk db header size
};
