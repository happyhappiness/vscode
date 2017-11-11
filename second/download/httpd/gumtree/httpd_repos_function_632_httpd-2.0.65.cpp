static void split(void *first_p, void *last_p, compare_t compare,
                  table_compare_t user_compare, table_t * table_p)
{
    void *pivot_p, *left_p, *right_p, *left_last_p, *right_first_p;
    void *firsts[MAX_SORT_SPLITS], *lasts[MAX_SORT_SPLITS];
    int split_c = 0;

    for (;;) {

        /* no need to split the list if it is < 2 elements */
        while (first_p >= last_p) {
            if (split_c == 0) {
                /* we are done */
                return;
            }
            split_c--;
            first_p = firsts[split_c];
            last_p = lasts[split_c];
        }

        left_p = first_p;
        right_p = last_p;
        pivot_p = first_p;

        do {
            /* scan from right hand side */
            while (right_p > left_p
                   && compare(right_p, pivot_p, user_compare, table_p) > 0)
                right_p = (char *) right_p - sizeof(table_entry_t *);
            /* scan from left hand side */
            while (right_p > left_p
                   && compare(pivot_p, left_p, user_compare, table_p) >= 0)
                left_p = (char *) left_p + sizeof(table_entry_t *);
            /* if the pointers haven't met then swap values */
            if (right_p > left_p) {
                /* swap_bytes(left_p, right_p) */
                table_entry_t *temp;

                temp = *(table_entry_t **) left_p;
                *(table_entry_t **) left_p = *(table_entry_t **) right_p;
                *(table_entry_t **) right_p = temp;
            }
        } while (right_p > left_p);

        /* now we swap the pivot with the right-hand side */
        {
            /* swap_bytes(pivot_p, right_p); */
            table_entry_t *temp;

            temp = *(table_entry_t **) pivot_p;
            *(table_entry_t **) pivot_p = *(table_entry_t **) right_p;
            *(table_entry_t **) right_p = temp;
        }
        pivot_p = right_p;

        /* save the section to the right of the pivot in our stack */
        right_first_p = (char *) pivot_p + sizeof(table_entry_t *);
        left_last_p = (char *) pivot_p - sizeof(table_entry_t *);

        /* do we need to save the righthand side? */
        if (right_first_p < last_p) {
            if (split_c >= MAX_SORT_SPLITS) {
                /* sanity check here -- we should never get here */
                abort();
            }
            firsts[split_c] = right_first_p;
            lasts[split_c] = last_p;
            split_c++;
        }

        /* do the left hand side of the pivot */
        /* first_p = first_p */
        last_p = left_last_p;
    }
}