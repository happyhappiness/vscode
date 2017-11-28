void
StoreController::createOneStore(Store &aStore)
{
    /*
     * On Windows, fork() is not available.
     * The following is a workaround for create store directories sequentially
     * when running on native Windows port.
     */
#if !_SQUID_WINDOWS_

    if (fork())
        return;

#endif

    aStore.create();

#if !_SQUID_WINDOWS_

    exit(0);

#endif
}