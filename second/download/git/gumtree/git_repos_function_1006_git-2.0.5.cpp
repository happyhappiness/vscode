static const struct userdiff_funcname *diff_funcname_pattern(struct diff_filespec *one)
{
	diff_filespec_load_driver(one);
	return one->driver->funcname.pattern ? &one->driver->funcname : NULL;
}