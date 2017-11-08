int link_stat(const char *Path, struct stat *Buffer) 
{
#if SUPPORT_LINKS
    if (copy_links) {
	return stat(Path, Buffer);
    } else {
	return lstat(Path, Buffer);
    }
#else
    return stat(Path, Buffer);
#endif
}