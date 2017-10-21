
/** Build an exclude structure given a exclude pattern */
static struct exclude_struct *make_exclude(const char *pattern, int include)
{
	struct exclude_struct *ret;

	ret = new(struct exclude_struct);
	if (!ret) out_of_memory("make_exclude");

	memset(ret, 0, sizeof(*ret));

	if (strncmp(pattern,"- ",2) == 0) {
		pattern += 2;
