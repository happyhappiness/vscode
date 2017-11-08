static const char *userdiff_word_regex(struct diff_filespec *one)
{
	diff_filespec_load_driver(one);
	return one->driver->word_regex;
}