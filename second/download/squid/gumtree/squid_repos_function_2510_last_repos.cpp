static void
storeLateRelease(void *)
{
    StoreEntry *e;
    static int n = 0;

    if (Store::Controller::store_dirs_rebuilding) {
        eventAdd("storeLateRelease", storeLateRelease, NULL, 1.0, 1);
        return;
    }

    // TODO: this works but looks unelegant.
    for (int i = 0; i < 10; ++i) {
        if (LateReleaseStack.empty()) {
            debugs(20, DBG_IMPORTANT, "storeLateRelease: released " << n << " objects");
            return;
        } else {
            e = LateReleaseStack.top();
            LateReleaseStack.pop();
        }

        e->unlock("storeLateRelease");
        ++n;
    }

    eventAdd("storeLateRelease", storeLateRelease, NULL, 0.0, 1);
}