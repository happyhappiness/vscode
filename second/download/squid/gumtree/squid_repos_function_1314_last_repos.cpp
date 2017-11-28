static void
statObjectsStart(StoreEntry * sentry, STOBJFLT * filter)
{
    StatObjectsState *state = new StatObjectsState;
    state->sentry = sentry;
    state->filter = filter;

    sentry->lock("statObjects");
    state->theSearch = Store::Root().search();

    eventAdd("statObjects", statObjects, state, 0.0, 1);
}