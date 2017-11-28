static void
wccp2SortCacheList(struct wccp2_cache_list_t *head)
{
    struct wccp2_cache_list_t tmp;
    struct wccp2_cache_list_t *this_item;
    struct wccp2_cache_list_t *find_item;
    struct wccp2_cache_list_t *next_lowest;

    /* Go through each position in the list one at a time */
    for (this_item = head; this_item->next; this_item = this_item->next) {
        /* Find the item with the lowest IP */
        next_lowest = this_item;

        for (find_item = this_item; find_item->next; find_item = find_item->next) {
            if (find_item->cache_ip.s_addr < next_lowest->cache_ip.s_addr) {
                next_lowest = find_item;
            }
        }
        /* Swap if we need to */
        if (next_lowest != this_item) {
            /* First make a copy of the current item */
            memcpy(&tmp, this_item, sizeof(struct wccp2_cache_list_t));

            /* Next update the pointers to maintain the linked list */
            tmp.next = next_lowest->next;
            next_lowest->next = this_item->next;

            /* Finally copy the updated items to their correct location */
            memcpy(this_item, next_lowest, sizeof(struct wccp2_cache_list_t));
            memcpy(next_lowest, &tmp, sizeof(struct wccp2_cache_list_t));
        }
    }
}