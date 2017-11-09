void free_acl(stat_x *sxp)
{
	if (sxp->acc_acl) {
		rsync_acl_free(sxp->acc_acl);
		free(sxp->acc_acl);
		sxp->acc_acl = NULL;
	}
	if (sxp->def_acl) {
		rsync_acl_free(sxp->def_acl);
		free(sxp->def_acl);
		sxp->def_acl = NULL;
	}
}