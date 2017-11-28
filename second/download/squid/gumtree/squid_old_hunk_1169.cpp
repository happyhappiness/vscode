{
    if (redirectors == NULL) {
        storeAppendPrintf(sentry, "No redirectors defined\n");
        return;
    }

    helperStats(sentry, redirectors, "Redirector Statistics");

    if (Config.onoff.redirector_bypass)
        storeAppendPrintf(sentry, "\nNumber of requests bypassed "
                          "because all redirectors were busy: %d\n", redirectorBypassed);
}

