int wildmatch(const char *pattern, const char *text)
{
    static const uchar *nomore[1]; /* A NULL pointer. */
#ifdef WILD_TEST_ITERATIONS
    wildmatch_iteration_count = 0;
#endif
    return dowild((const uchar*)pattern, (const uchar*)text, nomore) == TRUE;
}