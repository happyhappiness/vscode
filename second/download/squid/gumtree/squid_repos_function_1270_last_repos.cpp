void
DelayPools::Stats(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "Delay pools configured: %d\n\n", DelayPools::pools());

    for (unsigned short i = 0; i < DelayPools::pools(); ++i) {
        if (DelayPools::delay_data[i].theComposite().getRaw()) {
            storeAppendPrintf(sentry, "Pool: %d\n\tClass: %s\n\n", i + 1, DelayPools::delay_data[i].pool->theClassTypeLabel());
            DelayPools::delay_data[i].theComposite()->stats (sentry);
        } else
            storeAppendPrintf(sentry, "\tMisconfigured pool.\n\n");
    }
}