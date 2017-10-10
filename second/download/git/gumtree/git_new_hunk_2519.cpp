#include "builtin.h"
#include "cache.h"
#include "refs.h"
#include "object.h"
#include "parse-options.h"
#include "ref-filter.h"

static char const * const for_each_ref_usage[] = {
	N_("git for-each-ref [<options>] [<pattern>]"),
	NULL
};

int cmd_for_each_ref(int argc, const char **argv, const char *prefix)
{
	int i;
	const char *format = "%(objectname) %(objecttype)\t%(refname)";
	struct ref_sorting *sorting = NULL, **sorting_tail = &sorting;
	int maxcount = 0, quote_style = 0;
	struct ref_array array;
	struct ref_filter filter;

	struct option opts[] = {
		OPT_BIT('s', "shell", &quote_style,
			N_("quote placeholders suitably for shells"), QUOTE_SHELL),
		OPT_BIT('p', "perl",  &quote_style,
			N_("quote placeholders suitably for perl"), QUOTE_PERL),
