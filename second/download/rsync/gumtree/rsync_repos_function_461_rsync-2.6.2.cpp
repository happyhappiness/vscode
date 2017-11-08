int wildmatch(const char *p, const char *t)
{
#ifdef WILD_TEST_ITERATIONS
    wildmatch_iteration_count = 0;
#endif
    return domatch((const unsigned char*)p, (const unsigned char*)t) == TRUE;
}