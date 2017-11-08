int no_acl_syscall_error(int err)
{
#ifdef HAVE_OSX_ACLS
	if (err == ENOENT)
		return 1; /* Weird problem with directory ACLs. */
#endif
#if defined(ENOSYS)
	if (err == ENOSYS) {
		return 1;
	}
#endif
#if defined(ENOTSUP)
	if (err == ENOTSUP) {
		return 1;
	}
#endif
	return 0;
}