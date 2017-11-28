static void
storeLateRelease(void *unused)
{
    StoreEntry *e;
    int i;
    static int n = 0;

    if (StoreController::store_dirs_rebuilding) {
        eventAdd("storeLateRelease", storeLateRelease, NULL, 1.0, 1);
        return;
    }

    for (i = 0; i < 10; i++) {
        e = LateReleaseStack.pop();

        if (e == NULL) {
            /* done! */
            debugs(20, 1, "storeLateRelease: released " << n << " objects");
            return;
        }

        e->unlock();
        n++;
    }

    eventAdd("storeLateRelease", storeLateRelease, NULL, 0.0, 1);
}