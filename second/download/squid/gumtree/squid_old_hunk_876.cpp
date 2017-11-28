                      store_check_cachable_hist.no.too_many_open_fds);
    storeAppendPrintf(sentry, "yes.default\t%d\n",
                      store_check_cachable_hist.yes.Default);
}

void
StoreEntry::complete()
{
    debugs(20, 3, "storeComplete: '" << getMD5Text() << "'");

    if (store_status != STORE_PENDING) {
        /*
