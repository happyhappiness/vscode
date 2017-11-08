void abts_run_test(abts_suite *ts, test_func f, void *value)
{
    abts_case tc;
    sub_suite *ss;

    if (!should_test_run(ts->tail->name)) {
        return;
    }
    ss = ts->tail;

    tc.failed = 0;
    tc.suite = ss;
    
    ss->num_test++;
    update_status();

    f(&tc, value);
    
    if (tc.failed) {
        ss->failed++;
    }
}