        storeAppendPrintf(sentry, "\n\n");
        return;
    }

    storeAppendPrintf(sentry, "\t\tCurrent:");

    for (unsigned int i = 0; i < buckets.size(); ++i) {
        storeAppendPrintf(sentry, " %d:", buckets.key_map[i]);
        buckets.values[i].stats(sentry);
    }

    if (!buckets.size())
        storeAppendPrintf(sentry, " Not used yet.");
