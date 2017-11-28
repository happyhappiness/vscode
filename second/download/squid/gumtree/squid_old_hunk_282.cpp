}

void
SwapDir::unlink(StoreEntry &) {}

void
SwapDir::stat(StoreEntry &output) const
{
    storeAppendPrintf(&output, "Store Directory #%d (%s): %s\n", index, type(),
                      path);
    storeAppendPrintf(&output, "FS Block Size %d Bytes\n",
                      fs.blksize);
    statfs(output);

