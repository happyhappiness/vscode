        }
    }
    unlockThreadedIO();
    printf("Not found: %p\n", (void*)o);
    redisAssert(1 != 1); /* We should never reach this */
}

static void *IOThreadEntryPoint(void *arg) {
