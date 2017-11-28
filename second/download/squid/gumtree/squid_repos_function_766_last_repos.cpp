static void
dump_cachedir(StoreEntry * entry, const char *name, const Store::DiskConfig &swap)
{
    SwapDir *s;
    int i;
    assert (entry);

    for (i = 0; i < swap.n_configured; ++i) {
        s = dynamic_cast<SwapDir *>(swap.swapDirs[i].getRaw());
        if (!s) continue;
        storeAppendPrintf(entry, "%s %s %s", name, s->type(), s->path);
        s->dump(*entry);
        storeAppendPrintf(entry, "\n");
    }
}