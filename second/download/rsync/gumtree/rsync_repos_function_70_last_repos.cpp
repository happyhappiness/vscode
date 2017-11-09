static inline void
free_stat_x(stat_x *sx_p)
{
#ifdef SUPPORT_ACLS
    {
	extern int preserve_acls;
	if (preserve_acls)
		free_acl(sx_p);
    }
#endif
#ifdef SUPPORT_XATTRS
    {
	extern int preserve_xattrs;
	if (preserve_xattrs)
		free_xattr(sx_p);
    }
#endif
}