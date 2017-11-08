static void print_rsync_version(enum logcode f)
{
        char const *got_socketpair = "no ";
        char const *hardlinks = "no ";
        char const *links = "no ";
	char const *ipv6 = "no ";
	STRUCT_STAT *dumstat;

#ifdef HAVE_SOCKETPAIR
        got_socketpair = "";
#endif

#if SUPPORT_HARD_LINKS
        hardlinks = "";
#endif

#if SUPPORT_LINKS
        links = "";
#endif

#if INET6
	ipv6 = "";
#endif       

        rprintf(f, "%s  version %s  protocol version %d\n",
                RSYNC_NAME, RSYNC_VERSION, PROTOCOL_VERSION);
        rprintf(f,
                "Copyright (C) 1996-2002 by Andrew Tridgell and others\n");
	rprintf(f, "<http://rsync.samba.org/>\n");
        rprintf(f, "Capabilities: %d-bit files, %ssocketpairs, "
                "%shard links, %ssymlinks, batchfiles, \n",
                (int) (sizeof(OFF_T) * 8),
                got_socketpair, hardlinks, links);

	/* Note that this field may not have type ino_t.  It depends
	 * on the complicated interaction between largefile feature
	 * macros. */
	rprintf(f, "              %sIPv6, %d-bit system inums, %d-bit internal inums\n",
		ipv6, 
		(int) (sizeof(dumstat->st_ino) * 8),
		(int) (sizeof(INO64_T) * 8));

#ifdef NO_INT64
        rprintf(f, "WARNING: no 64-bit integers on this platform!\n");
#endif

	rprintf(f,
"\n"
"rsync comes with ABSOLUTELY NO WARRANTY.  This is free software, and you\n"
"are welcome to redistribute it under certain conditions.  See the GNU\n"
"General Public Licence for details.\n"
		);
}