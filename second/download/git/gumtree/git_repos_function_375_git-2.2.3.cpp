static int has_changes(mmfile_t *one, mmfile_t *two,
		       struct diff_options *o,
		       regex_t *regexp, kwset_t kws)
{
	unsigned int one_contains = one ? contains(one, regexp, kws) : 0;
	unsigned int two_contains = two ? contains(two, regexp, kws) : 0;
	return one_contains != two_contains;
}