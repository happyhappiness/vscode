int do_lstat(const char *fname, STRUCT_STAT *st)
{
#if HAVE_OFF64_T
	return lstat64(fname, st);
#else
	return lstat(fname, st);
#endif
}