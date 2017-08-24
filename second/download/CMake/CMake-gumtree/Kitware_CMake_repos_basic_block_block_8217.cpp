(pool->ptr == pool->end && !poolGrow(pool))
    return NULL;