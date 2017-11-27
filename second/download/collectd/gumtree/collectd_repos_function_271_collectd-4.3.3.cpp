static int nfs_read (void)
{
	FILE *fh;

	if ((fh = fopen ("/proc/net/rpc/nfs", "r")) != NULL)
	{
		nfs_read_stats_file (fh, "client");
		fclose (fh);
	}

	if ((fh = fopen ("/proc/net/rpc/nfsd", "r")) != NULL)
	{
		nfs_read_stats_file (fh, "server");
		fclose (fh);
	}

#if HAVE_LIBKSTAT && 0
	if (nfs2_ksp_client != NULL)
		nfs2_read_kstat (nfs2_ksp_client, "client");
	if (nfs2_ksp_server != NULL)
		nfs2_read_kstat (nfs2_ksp_server, "server");
#endif /* defined(HAVE_LIBKSTAT) */

	return (0);
}