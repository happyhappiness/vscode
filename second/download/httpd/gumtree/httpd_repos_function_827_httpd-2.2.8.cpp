static SHMCBIndex *shmcb_get_index(
    const SHMCBQueue *queue, unsigned int idx)
{
    /* bounds check */
    if (idx > queue->header->index_num)
        return NULL;

    /* Return a pointer to the index. NB: I am being horribly pendantic
     * here so as to avoid any potential data-alignment assumptions being
     * placed on the pointer arithmetic by the compiler (sigh). */
    return (SHMCBIndex *)(((unsigned char *) queue->indexes) +
                          (idx * sizeof(SHMCBIndex)));
}