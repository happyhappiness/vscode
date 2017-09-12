                else if (o->storage == REDIS_VM_SWAPPING)
                    o->storage = REDIS_VM_MEMORY;
                unlockThreadedIO();
                redisLog(REDIS_DEBUG,"*** DONE");
                return;
            }
        }
    }
    unlockThreadedIO();
    printf("Not found: %p\n", (void*)o);
    redisAssert(1 != 1); /* We should never reach this */
}

static void *IOThreadEntryPoint(void *arg) {
