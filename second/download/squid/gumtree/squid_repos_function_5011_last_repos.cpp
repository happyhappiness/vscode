bool
Rock::Rebuild::importEntry(Ipc::StoreMapAnchor &anchor, const sfileno fileno, const DbCellHeader &header)
{
    cache_key key[SQUID_MD5_DIGEST_LENGTH];
    StoreEntry loadedE;
    const uint64_t knownSize = header.entrySize > 0 ?
                               header.entrySize : anchor.basics.swap_file_sz.load();
    if (!storeRebuildParseEntry(buf, loadedE, key, counts, knownSize))
        return false;

    // the entry size may be unknown, but if it is known, it is authoritative

    debugs(47, 8, "importing basics for entry " << fileno <<
           " inode.entrySize: " << header.entrySize <<
           " swap_file_sz: " << loadedE.swap_file_sz);
    anchor.set(loadedE);

    // we have not validated whether all db cells for this entry were loaded
    EBIT_CLR(anchor.basics.flags, ENTRY_VALIDATED);

    // loadedE->dump(5);

    return true;
}