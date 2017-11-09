static inline void
init_stat_x(stat_x *sx_p)
{
#ifdef SUPPORT_ACLS
	sx_p->acc_acl = sx_p->def_acl = NULL;
#endif
#ifdef SUPPORT_XATTRS
	sx_p->xattr = NULL;
#endif
}