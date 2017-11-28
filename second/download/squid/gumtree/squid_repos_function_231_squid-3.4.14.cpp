static void processActivity(const char *user_key)
{
    time_t now = time(NULL);
    time_t lastActivity;
    time_t activityLength;
    time_t periodStart;
    time_t periodLength;
    time_t userPeriodLength;
    time_t timeBudgetCurrent;
    time_t timeBudgetConfigured;
    char message[TQ_BUFFERSIZE];

    log_debug("processActivity(\"%s\")\n", user_key);

    // [1] Reset period if over
    periodStart = readTime(user_key, KEY_PERIOD_START);
    if ( periodStart == 0 ) {
        // This is the first period ever.
        periodStart = now;
        writeTime(user_key, KEY_PERIOD_START, periodStart);
    }

    periodLength = now - periodStart;
    userPeriodLength = readTime(user_key, KEY_PERIOD_LENGTH_CONFIGURED);
    if ( userPeriodLength == 0 ) {
        // This user is not configured. Allow anything.
        log_debug("No period length found for user \"%s\". Quota for this user disabled.\n", user_key);
        writeTime(user_key, KEY_TIME_BUDGET_LEFT, pauseLength);
    } else {
        if ( periodLength >= userPeriodLength ) {
            // a new period has started.
            log_debug("New time period started for user \"%s\".\n", user_key);
            while ( periodStart < now ) {
                periodStart += periodLength;
            }
            writeTime(user_key, KEY_PERIOD_START, periodStart);
            timeBudgetConfigured = readTime(user_key, KEY_TIME_BUDGET_CONFIGURED);
            if ( timeBudgetConfigured == 0 ) {
                log_debug("No time budget configured for user \"%s\". Quota for this user disabled.\n", user_key);
                writeTime(user_key, KEY_TIME_BUDGET_LEFT, pauseLength);
            } else {
                writeTime(user_key, KEY_TIME_BUDGET_LEFT, timeBudgetConfigured);
            }
        }
    }

    // [2] Decrease time budget iff activity
    lastActivity = readTime(user_key, KEY_LAST_ACTIVITY);
    if ( lastActivity == 0 ) {
        // This is the first request ever
        writeTime(user_key, KEY_LAST_ACTIVITY, now);
    } else {
        activityLength = now - lastActivity;
        if ( activityLength >= pauseLength ) {
            // This is an activity pause.
            log_debug("Activity pause detected for user \"%s\".\n", user_key);
            writeTime(user_key, KEY_LAST_ACTIVITY, now);
        } else {
            // This is real usage.
            writeTime(user_key, KEY_LAST_ACTIVITY, now);

            log_debug("Time budget reduced by %ld for user \"%s\".\n",
                      activityLength, user_key);
            timeBudgetCurrent = readTime(user_key, KEY_TIME_BUDGET_LEFT);
            timeBudgetCurrent -= activityLength;
            writeTime(user_key, KEY_TIME_BUDGET_LEFT, timeBudgetCurrent);
        }
    }

    timeBudgetCurrent = readTime(user_key, KEY_TIME_BUDGET_LEFT);
    snprintf(message, TQ_BUFFERSIZE, "message=\"Remaining quota for '%s' is %d seconds.\"", user_key, (int)timeBudgetCurrent);
    if ( timeBudgetCurrent > 0 ) {
        log_debug("OK %s.\n", message);
        SEND_OK(message);
    } else {
        log_debug("ERR %s\n", message);
        SEND_ERR("Time budget exceeded.");
    }

    db->sync(db, 0);
}