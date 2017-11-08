int wildmatch(const char *p, const char *t)
{
#ifdef WILD_TEST_ITERATIONS
    wildmatch_iteration_count = 0;
#endif
    return domatch((const uchar*)p, (const uchar*)t) == TRUE;
}