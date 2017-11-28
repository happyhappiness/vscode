static void
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
    MemBuf mb;
    mb.init();

    while (statCount++ < static_cast<size_t>(Config.Store.objectsPerBucket) && state->
            theSearch->next()) {
        e = state->theSearch->currentItem();

        if (state->filter && 0 == state->filter(e))
            continue;

        statStoreEntry(&mb, e);
    }

    if (mb.size)
        state->sentry->append(mb.buf, mb.size);
    mb.clean();

    eventAdd("statObjects", statObjects, state, 0.0, 1);
}