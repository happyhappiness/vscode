static void
free_refreshpattern(RefreshPattern ** head)
{
    RefreshPattern *t;

    while ((t = *head) != NULL) {
        *head = t->next;
        safe_free(t->pattern);
        regfree(&t->compiled_pattern);
        safe_free(t);
    }

#if USE_HTTP_VIOLATIONS
    refresh_nocache_hack = 0;

#endif
}