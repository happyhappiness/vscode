static void
free_refreshpattern(refresh_t ** head)
{
    refresh_t *t;

    while ((t = *head) != NULL) {
        *head = t->next;
        safe_free(t->pattern);
        regfree(&t->compiled_pattern);
        safe_free(t);
    }

#if HTTP_VIOLATIONS
    refresh_nocache_hack = 0;

#endif
}