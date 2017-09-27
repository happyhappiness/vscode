            return 1;
        }
    }
    return 0;
}


/**
 * Get the next task for the given worker. Will block until a task arrives
 * or the max_wait timer expires and more than min workers exist.
 * The previous h2_mplx instance might be passed in and will be served
 * with preference, since we can ask it for the next task without aquiring
