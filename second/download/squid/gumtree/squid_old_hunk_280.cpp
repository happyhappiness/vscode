}

void
storeLogTagsHist(StoreEntry *e)
{
    int tag;
    for (tag = 0; tag <= STORE_LOG_SWAPOUTFAIL; tag++) {
        storeAppendPrintf(e, "%s %d\n",
                          storeLogTags[tag],
                          storeLogTagsCounts[tag]);
    }
}
