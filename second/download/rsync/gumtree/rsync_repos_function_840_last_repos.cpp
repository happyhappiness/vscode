int wildmatch_array(const char *pattern, const char*const *texts, int where)
{
    const uchar *p = (const uchar*)pattern;
    const uchar*const *a = (const uchar*const*)texts;
    const uchar *text;
    int matched;

#ifdef WILD_TEST_ITERATIONS
    wildmatch_iteration_count = 0;
#endif

    if (where > 0)
	text = trailing_N_elements(&a, where);
    else
	text = *a++;
    if (!text)
	return FALSE;

    if ((matched = dowild(p, text, a)) != TRUE && where < 0
     && matched != ABORT_ALL) {
	while (1) {
	    if (*text == '\0') {
		if ((text = (uchar*)*a++) == NULL)
		    return FALSE;
		continue;
	    }
	    if (*text++ == '/' && (matched = dowild(p, text, a)) != FALSE
	     && matched != ABORT_TO_STARSTAR)
		break;
	}
    }
    return matched == TRUE;
}