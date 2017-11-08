abts_suite *abts_add_suite(abts_suite *suite, const char *suite_name_full)
{
    sub_suite *subsuite;
    char *p;
    const char *suite_name;
    curr_char = 0;
    
    /* Only end the suite if we actually ran it */
    if (suite && suite->tail &&!suite->tail->not_run) {
        end_suite(suite);
    }

    subsuite = malloc(sizeof(*subsuite));
    subsuite->num_test = 0;
    subsuite->failed = 0;
    subsuite->next = NULL;
    /* suite_name_full may be an absolute path depending on __FILE__ 
     * expansion */
    suite_name = strrchr(suite_name_full, '/');
    if (!suite_name) {
        suite_name = strrchr(suite_name_full, '\\');
    }
    if (suite_name) {
        suite_name++;
    } else {
        suite_name = suite_name_full;
    }
    p = strrchr(suite_name, '.');
    if (p) {
        subsuite->name = memcpy(calloc(p - suite_name + 1, 1),
                                suite_name, p - suite_name);
    }
    else {
        subsuite->name = suite_name;
    }

    if (list_tests) {
        fprintf(stdout, "%s\n", subsuite->name);
    }
    
    subsuite->not_run = 0;

    if (suite == NULL) {
        suite = malloc(sizeof(*suite));
        suite->head = subsuite;
        suite->tail = subsuite;
    }
    else {
        suite->tail->next = subsuite;
        suite->tail = subsuite;
    }

    if (!should_test_run(subsuite->name)) {
        subsuite->not_run = 1;
        return suite;
    }

    reset_status();
    fprintf(stdout, "%-20s:  ", subsuite->name);
    update_status();
    fflush(stdout);

    return suite;
}