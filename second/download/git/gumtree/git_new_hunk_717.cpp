			      int(*compar)(const void *, const void *))
{
	if (nmemb > 1)
		qsort(base, nmemb, size, compar);
}

#ifndef HAVE_ISO_QSORT_S
int git_qsort_s(void *base, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *, void *), void *ctx);
#define qsort_s git_qsort_s
#endif

#define QSORT_S(base, n, compar, ctx) do {			\
	if (qsort_s((base), (n), sizeof(*(base)), compar, ctx))	\
		die("BUG: qsort_s() failed");			\
} while (0)

#ifndef REG_STARTEND
#error "Git requires REG_STARTEND support. Compile with NO_REGEX=NeedsStartEnd"
#endif

static inline int regexec_buf(const regex_t *preg, const char *buf, size_t size,
			      size_t nmatch, regmatch_t pmatch[], int eflags)
