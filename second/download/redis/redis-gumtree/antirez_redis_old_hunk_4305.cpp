    return REDIS_ERR;
}

/* Swap the 'val' object relative to 'key' into disk. Store all the information
 * needed to later retrieve the object into the key object.
 * If we can't find enough contiguous empty pages to swap the object on disk
