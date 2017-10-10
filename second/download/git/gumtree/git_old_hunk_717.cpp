			      int(*compar)(const void *, const void *))
{
	if (nmemb > 1)
		qsort(base, nmemb, size, compar);
}

#ifndef REG_STARTEND
#error "Git requires REG_STARTEND support. Compile with NO_REGEX=NeedsStartEnd"
#endif

static inline int regexec_buf(const regex_t *preg, const char *buf, size_t size,
			      size_t nmatch, regmatch_t pmatch[], int eflags)
