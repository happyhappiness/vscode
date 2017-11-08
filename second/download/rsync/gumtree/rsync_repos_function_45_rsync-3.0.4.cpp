static inline char *
d_name(struct dirent *di)
{
#ifdef HAVE_BROKEN_READDIR
	return (di->d_name - 2);
#else
	return di->d_name;
#endif
}