{
    if (storeIds == NULL) {
        storeAppendPrintf(sentry, "No StoreId helpers defined\n");
        return;
    }

    helperStats(sentry, storeIds, "StoreId helper Statistics");

    if (Config.onoff.store_id_bypass)
        storeAppendPrintf(sentry, "\nNumber of requests bypassed "
                          "because all StoreId helpers were busy: %d\n", storeIdBypassed);
}

