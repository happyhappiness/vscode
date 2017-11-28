void
parse_wccp2_amethod(int *method)
{
    char *t;

    /* Snarf the method */
    if ((t = ConfigParser::NextToken()) == NULL) {
        debugs(80, DBG_CRITICAL, "wccp2_assignment_method: missing setting.");
        self_destruct();
    }

    /* update configuration if its valid */
    if (strcmp(t, "hash") == 0 || strcmp(t, "1") == 0) {
        *method = WCCP2_ASSIGNMENT_METHOD_HASH;
    } else if (strcmp(t, "mask") == 0 || strcmp(t, "2") == 0) {
        *method = WCCP2_ASSIGNMENT_METHOD_MASK;
    } else {
        debugs(80, DBG_CRITICAL, "wccp2_assignment_method: unknown setting, got " << t );
        self_destruct();
    }
}