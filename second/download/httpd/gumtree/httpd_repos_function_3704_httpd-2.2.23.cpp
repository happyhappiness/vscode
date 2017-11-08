static apr_status_t random_cleanup(void *data)
{
    apr_random_t *remove_this = data,
                 *cur = all_random,
                 **prev_ptr = &all_random;
    while (cur) {
        if (cur == remove_this) {
            *prev_ptr = cur->next;
            break;
        }
        prev_ptr = &cur->next;
        cur = cur->next;
    }
    return APR_SUCCESS;
}