static void print_rsync_version(enum logcode f)
{
	char const *got_socketpair = "no ";
	char const *have_inplace = "no ";
	char const *hardlinks = "no ";
	char const *links = "no ";
	char const *ipv6 = "no ";
	STRUCT_STAT *dumstat;

#ifdef HAVE_SOCKETPAIR
	got_socketpair = "";
#endif

#ifdef HAVE_FTRUNCATE
	have_inplace = "";
#endif

#ifdef SUPPORT_HARD_LINKS
	hardlinks = "";
#endif

#ifdef SUPPORT_LINKS
	links = "";
#endif

#ifdef INET6
	ipv6 = "";
#endif

	rprintf(f, "%s  version %s  protocol version %d\n",
		RSYNC_NAME, RSYNC_VERSION, PROTOCOL_VERSION);
	rprintf(f, "Copyright (C) 1996-2006 by Andrew Tridgell, Wayne Davison, and others.\n");
	rprintf(f, "<http://rsync.samba.org/>\n");
	rprintf(f, "Capabilities: %d-bit files, %ssocketpairs, "
		"%shard links, %ssymlinks, batchfiles,\n",
		(int) (sizeof (OFF_T) * 8),
		got_socketpair, hardlinks, links);

	/* Note that this field may not have type ino_t.  It depends
	 * on the complicated interaction between largefile feature
	 * macros. */
	rprintf(f, "              %sinplace, %sIPv6, "
		"%d-bit system inums, %d-bit internal inums\n",
		have_inplace, ipv6,
		(int) (sizeof dumstat->st_ino * 8),
		(int) (sizeof (int64) * 8));
#ifdef MAINTAINER_MODE
	rprintf(f, "Panic Action: \"%s\"\n", get_panic_action());
#endif

#if SIZEOF_INT64 < 8
	rprintf(f, "WARNING: no 64-bit integers on this platform!\n");
#endif
	if (sizeof (int64) != SIZEOF_INT64) {
		rprintf(f,
			"WARNING: size mismatch in SIZEOF_INT64 define (%d != %d)\n",
			(int) SIZEOF_INT64, (int) sizeof (int64));
	}

	rprintf(f,"\nrsync comes with ABSOLUTELY NO WARRANTY.  This is free software, and you\n");
	rprintf(f,"are welcome to redistribute it under certain conditions.  See the GNU\n");
	rprintf(f,"General Public Licence for details.\n");
}