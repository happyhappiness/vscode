void
parse_wccp2_method(int *method)
{
    char *t;

    /* Snarf the method */
    if ((t = ConfigParser::NextToken()) == NULL) {
        debugs(80, DBG_CRITICAL, "wccp2_*_method: missing setting.");
        self_destruct();
    }

    /* update configuration if its valid */
    if (strcmp(t, "gre") == 0 || strcmp(t, "1") == 0) {
        *method = WCCP2_METHOD_GRE;
    } else if (strcmp(t, "l2") == 0 || strcmp(t, "2") == 0) {
        *method = WCCP2_METHOD_L2;
    } else {
        debugs(80, DBG_CRITICAL, "wccp2_*_method: unknown setting, got " << t );
        self_destruct();
    }
}