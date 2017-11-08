int ap_unregister_extra_mpm_process(pid_t pid)
{
    extra_process_t *cur = extras;
    extra_process_t *prev = NULL;

    while (cur && cur->pid != pid) {
        prev = cur;
        cur = cur->next;
    }

    if (cur) {
        if (prev) {
            prev->next = cur->next;
        }
        else {
            extras = cur->next;
        }
        free(cur);
        return 1; /* found */
    }
    else {
        /* we don't know about any such process */
        return 0;
    }
}