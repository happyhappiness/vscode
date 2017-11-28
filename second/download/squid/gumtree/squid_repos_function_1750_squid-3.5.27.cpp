static void
statObjectsStart(StoreEntry * sentry, STOBJFLT * filter)
{
    StatObjectsState *state = new StatObjectsState;
    state->sentry = sentry;
    state->filter = filter;

    sentry->lock("statObjects");
    state->theSearch = Store::Root().search(NULL, NULL);

    eventAdd("statObjects", statObjects, state, 0.0, 1);
}