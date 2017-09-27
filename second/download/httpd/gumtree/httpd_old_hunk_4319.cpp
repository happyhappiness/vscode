

/* A simple garbage-collecter to remove unused clients. It removes the
 * last entry in each bucket and updates the counters. Returns the
 * number of removed entries.
 */
static long gc(void)
{
    client_entry *entry, *prev;
    unsigned long num_removed = 0, idx;

    /* garbage collect all last entries */

    for (idx = 0; idx < client_list->tbl_len; idx++) {
        entry = client_list->table[idx];
        prev  = NULL;
        while (entry->next) {   /* find last entry */
            prev  = entry;
            entry = entry->next;
        }
        if (prev) {
            prev->next = NULL;   /* cut list */
        }
        else {
            client_list->table[idx] = NULL;
        }
        if (entry) {                    /* remove entry */
            apr_rmm_free(client_rmm, apr_rmm_offset_get(client_rmm, entry));
            num_removed++;
        }
    }

    /* update counters and log */

    client_list->num_entries -= num_removed;
