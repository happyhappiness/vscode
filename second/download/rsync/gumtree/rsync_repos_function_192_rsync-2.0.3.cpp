int link_stat(const char *Path, STRUCT_STAT *Buffer) 
{
#if SUPPORT_LINKS
    if (copy_links) {
	return do_stat(Path, Buffer);
    } else {
	return do_lstat(Path, Buffer);
    }
#else
    return do_stat(Path, Buffer);
#endif
}