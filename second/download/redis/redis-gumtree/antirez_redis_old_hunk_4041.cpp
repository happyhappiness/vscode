        }
    }
    unlockThreadedIO();
    assert(1 != 1); /* We should never reach this */
}

static void *IOThreadEntryPoint(void *arg) {
