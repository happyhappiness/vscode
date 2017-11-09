int iwildmatch(const char *pattern, const char *text)
{
    static const uchar *nomore[1]; /* A NULL pointer. */
    int ret;
#ifdef WILD_TEST_ITERATIONS
    wildmatch_iteration_count = 0;
#endif
    force_lower_case = 1;
    ret = dowild((const uchar*)pattern, (const uchar*)text, nomore) == TRUE;
    force_lower_case = 0;
    return ret;
}