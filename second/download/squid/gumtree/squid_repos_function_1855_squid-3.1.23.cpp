void
StoreController::createOneStore(Store &aStore)
{
    /*
     * On Windows, fork() is not available.
     * The following is a workaround for create store directories sequentially
     * when running on native Windows port.
     */
#ifndef _SQUID_MSWIN_

    if (fork())
        return;

#endif

    aStore.create();

#ifndef _SQUID_MSWIN_

    exit(0);

#endif
}