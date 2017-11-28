statObjects(void *data)
{
    StatObjectsState *state = static_cast<StatObjectsState *>(data);
    StoreEntry *e;

    if (state->theSearch->isDone()) {
        state->sentry->complete();
        state->sentry->unlock();
        cbdataFree(state);
        return;
    } else if (EBIT_TEST(state->sentry->flags, ENTRY_ABORTED)) {
        state->sentry->unlock();
        cbdataFree(state);
        return;
    } else if (state->sentry->checkDeferRead(-1)) {
        eventAdd("statObjects", statObjects, state, 0.1, 1);
        return;
    }

    state->sentry->buffer();
    size_t statCount = 0;
