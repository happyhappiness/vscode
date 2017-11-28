void
SwapDir::stat(StoreEntry &output) const
{
    if (!doReportStat())
        return;

    storeAppendPrintf(&output, "Store Directory #%d (%s): %s\n", index, type(),
                      path);
    storeAppendPrintf(&output, "FS Block Size %d Bytes\n",
                      fs.blksize);
    statfs(output);

    if (repl) {
        storeAppendPrintf(&output, "Removal policy: %s\n", repl->_type);

        if (repl->Stats)
            repl->Stats(repl, &output);
    }
}