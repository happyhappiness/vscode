static BOOL shmcb_get_division(
    SHMCBHeader *header, SHMCBQueue *queue,
    SHMCBCache *cache, unsigned int idx)
{
    unsigned char *pQueue;
    unsigned char *pCache;

    /* bounds check */
    if (idx > (unsigned int) header->division_mask)
        return FALSE;

    /* Locate the blocks of memory storing the corresponding data */
    pQueue = ((unsigned char *) header) + header->division_offset +
        (idx * header->division_size);
    pCache = pQueue + header->queue_size;

    /* Populate the structures with appropriate pointers */
    queue->first_pos = (unsigned int *) pQueue;

    /* Our structures stay packed, no matter what the system's
     * data-alignment regime is. */
    queue->pos_count = (unsigned int *) (pQueue + sizeof(unsigned int));
    queue->indexes = (SHMCBIndex *) (pQueue + (2 * sizeof(unsigned int)));
    cache->first_pos = (unsigned int *) pCache;
    cache->pos_count = (unsigned int *) (pCache + sizeof(unsigned int));
    cache->data = (unsigned char *) (pCache + (2 * sizeof(unsigned int)));
    queue->header = cache->header = header;

    return TRUE;
}