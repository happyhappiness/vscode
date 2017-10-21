 #ifdef ICONV_OPTION
 char *iconv_opt = ICONV_OPTION;
 #endif
 
 struct chmod_mode_struct *chmod_modes = NULL;
 
+static const char *debug_verbosity[] = {
+	/*0*/ NULL,
+	/*1*/ NULL,
+	/*2*/ "BIND,CMD,CONNECT,DEL,DELTASUM,DUP,FILTER,FLIST,ICONV",
+	/*3*/ "ACL,BACKUP,CONNECT2,DELTASUM2,DEL2,EXIT,FILTER2,FLIST2,FUZZY,GENR,OWN,RECV,SEND,TIME",
+	/*4*/ "CMD2,DELTASUM3,DEL3,EXIT2,FLIST3,ICONV2,OWN2,PROTO,TIME2",
+	/*5*/ "CHDIR,DELTASUM4,FLIST4,FUZZY2,HASH,HLINK",
+};
+
+#define MAX_VERBOSITY ((int)(sizeof debug_verbosity / sizeof debug_verbosity[0]) - 1)
+
+static const char *info_verbosity[1+MAX_VERBOSITY] = {
+	/*0*/ NULL,
+	/*1*/ "COPY,DEL,FLIST,MISC,NAME,STATS,SYMSAFE",
+	/*2*/ "BACKUP,MISC2,MOUNT,NAME2,REMOVE,SKIP",
+};
+
+#define MAX_OUT_LEVEL 4 /* The largest N allowed for any flagN word. */
+
+short info_levels[COUNT_INFO], debug_levels[COUNT_DEBUG];
+
+#define DEFAULT_PRIORITY 0 	/* Default/implied/--verbose set values. */
+#define HELP_PRIORITY 1		/* The help output uses this level. */
+#define USER_PRIORITY 2		/* User-specified via --info or --debug */
+#define LIMIT_PRIORITY 3	/* Overriding priority when limiting values. */
+
+#define W_CLI (1<<0)	/* client side */
+#define W_SRV (1<<1)	/* server side */
+#define W_SND (1<<2)	/* sending side */
+#define W_REC (1<<3)	/* receiving side */
+
+struct output_struct {
+	char *name;	/* The name of the info/debug flag. */
+	char *help;	/* The description of the info/debug flag. */
+	uchar namelen;  /* The length of the name string. */
+	uchar flag;	/* The flag's value, for consistency check. */
+	uchar where;	/* Bits indicating where the flag is used. */
+	uchar priority; /* See *_PRIORITY defines. */
+};
+
+#define INFO_WORD(flag, where, help) { #flag, help, sizeof #flag - 1, INFO_##flag, where, 0 }
+
+static struct output_struct info_words[COUNT_INFO+1] = {
+	INFO_WORD(BACKUP, W_REC, "Mention files backed up"),
+	INFO_WORD(COPY, W_REC, "Mention files copied locally on the receiving side"),
+	INFO_WORD(DEL, W_REC, "Mention deletions on the receiving side"),
+	INFO_WORD(FLIST, W_CLI, "Mention file-list receiving/sending (levels 1-2)"),
+	INFO_WORD(MISC, W_SND|W_REC, "Mention miscellaneous information (levels 1-2)"),
+	INFO_WORD(MOUNT, W_SND|W_REC, "Mention mounts that were found or skipped"),
+	INFO_WORD(NAME, W_SND|W_REC, "Mention 1) updated file/dir names, 2) unchanged names"),
+	INFO_WORD(PROGRESS, W_CLI, "Mention 1) per-file progress or 2) total transfer progress"),
+	INFO_WORD(REMOVE, W_SND, "Mention files removed on the sending side"),
+	INFO_WORD(SKIP, W_REC, "Mention files that are skipped due to options used"),
+	INFO_WORD(STATS, W_CLI|W_SRV, "Mention statistics at end of run (levels 1-3)"),
+	INFO_WORD(SYMSAFE, W_SND|W_REC, "Mention symlinks that are unsafe"),
+	{ NULL, "--info", 0, 0, 0, 0 }
+};
+
+#define DEBUG_WORD(flag, where, help) { #flag, help, sizeof #flag - 1, DEBUG_##flag, where, 0 }
+
+static struct output_struct debug_words[COUNT_DEBUG+1] = {
+	DEBUG_WORD(ACL, W_SND|W_REC, "Debug extra ACL info"),
+	DEBUG_WORD(BACKUP, W_REC, "Debug backup actions (levels 1-2)"),
+	DEBUG_WORD(BIND, W_CLI, "Debug socket bind actions"),
+	DEBUG_WORD(CHDIR, W_CLI|W_SRV, "Debug when the current directory changes"),
+	DEBUG_WORD(CONNECT, W_CLI, "Debug connection events (levels 1-2)"),
+	DEBUG_WORD(CMD, W_CLI, "Debug commands+options that are issued (levels 1-2)"),
+	DEBUG_WORD(DEL, W_REC, "Debug delete actions (levels 1-3)"),
+	DEBUG_WORD(DELTASUM, W_SND|W_REC, "Debug delta-transfer checksumming (levels 1-4)"),
+	DEBUG_WORD(DUP, W_REC, "Debug weeding of duplicate names"),
+	DEBUG_WORD(EXIT, W_CLI|W_SRV, "Debug exit events (levels 1-3)"),
+	DEBUG_WORD(FILTER, W_SND|W_REC, "Debug filter actions (levels 1-2)"),
+	DEBUG_WORD(FLIST, W_SND|W_REC, "Debug file-list operations (levels 1-4)"),
+	DEBUG_WORD(FUZZY, W_REC, "Debug fuzzy scoring (levels 1-2)"),
+	DEBUG_WORD(GENR, W_REC, "Debug generator functions"),
+	DEBUG_WORD(HASH, W_SND|W_REC, "Debug hashtable code"),
+	DEBUG_WORD(HLINK, W_SND|W_REC, "Debug hard-link actions (levels 1-3)"),
+	DEBUG_WORD(ICONV, W_CLI|W_SRV, "Debug iconv character conversions (levels 1-2)"),
+	DEBUG_WORD(IO, W_CLI|W_SRV, "Debug I/O routines (levels 1-4)"),
+	DEBUG_WORD(OWN, W_REC, "Debug ownership changes in users & groups (levels 1-2)"),
+	DEBUG_WORD(PROTO, W_CLI|W_SRV, "Debug protocol information"),
+	DEBUG_WORD(RECV, W_REC, "Debug receiver functions"),
+	DEBUG_WORD(SEND, W_SND, "Debug sender functions"),
+	DEBUG_WORD(TIME, W_REC, "Debug setting of modified times (levels 1-2)"),
+	{ NULL, "--debug", 0, 0, 0, 0 }
+};
+
+static int verbose = 0;
+static int do_stats = 0;
+static int do_progress = 0;
 static int daemon_opt;   /* sets am_daemon after option error-reporting */
 static int omit_dir_times = 0;
+static int omit_link_times = 0;
 static int F_option_cnt = 0;
 static int modify_window_set;
 static int itemize_changes = 0;
 static int refused_delete, refused_archive_part, refused_compress;
 static int refused_partial, refused_progress, refused_delete_before;
 static int refused_delete_during;
 static int refused_inplace, refused_no_iconv;
-static char *max_size_arg, *min_size_arg;
+static BOOL usermap_via_chown, groupmap_via_chown;
+#ifdef HAVE_SETVBUF
+static char *outbuf_mode;
+#endif
+static char *bwlimit_arg, *max_size_arg, *min_size_arg;
 static char tmp_partialdir[] = ".~tmp~";
 
 /** Local address to bind.  As a character string because it's
  * interpreted by the IPv6 layer: should be a numeric IP4 or IP6
  * address, or a hostname. **/
 char *bind_address;
 
+static void output_item_help(struct output_struct *words);
+
+/* This constructs a string that represents all the options set for either
+ * the --info or --debug setting, skipping any implied options (by -v, etc.).
+ * This is used both when conveying the user's options to the server, and
+ * when the help output wants to tell the user what options are implied. */
+static char *make_output_option(struct output_struct *words, short *levels, uchar where)
+{
+	char *str = words == info_words ? "--info=" : "--debug=";
+	int j, counts[MAX_OUT_LEVEL+1], pos, skipped = 0, len = 0, max = 0, lev = 0;
+	int word_count = words == info_words ? COUNT_INFO : COUNT_DEBUG;
+	char *buf;
+
+	memset(counts, 0, sizeof counts);
+
+	for (j = 0; words[j].name; j++) {
+		if (words[j].flag != j) {
+			rprintf(FERROR, "rsync: internal error on %s%s: %d != %d\n",
+				words == info_words ? "INFO_" : "DEBUG_",
+				words[j].name, words[j].flag, j);
+			exit_cleanup(RERR_UNSUPPORTED);
+		}
+		if (!(words[j].where & where))
+			continue;
+		if (words[j].priority == DEFAULT_PRIORITY) {
+			/* Implied items don't need to be mentioned. */
+			skipped++;
+			continue;
+		}
+		len += len ? 1 : strlen(str);
+		len += strlen(words[j].name);
+		len += levels[j] == 1 ? 0 : 1;
+
+		if (words[j].priority == HELP_PRIORITY)
+			continue; /* no abbreviating for help */
+
+		assert(levels[j] <= MAX_OUT_LEVEL);
+		if (++counts[levels[j]] > max) {
+			/* Determine which level has the most items. */
+			lev = levels[j];
+			max = counts[lev];
+		}
+	}
+
+	/* Sanity check the COUNT_* define against the length of the table. */
+	if (j != word_count) {
+		rprintf(FERROR, "rsync: internal error: %s is wrong! (%d != %d)\n",
+			words == info_words ? "COUNT_INFO" : "COUNT_DEBUG",
+			j, word_count);
+		exit_cleanup(RERR_UNSUPPORTED);
+	}
+
+	if (!len)
+		return NULL;
+
+	len++;
+	if (!(buf = new_array(char, len)))
+		out_of_memory("make_output_option");
+	pos = 0;
+
+	if (skipped || max < 5)
+		lev = -1;
+	else {
+		if (lev == 0)
+			pos += snprintf(buf, len, "%sNONE", str);
+		else if (lev == 1)
+			pos += snprintf(buf, len, "%sALL", str);
+		else
+			pos += snprintf(buf, len, "%sALL%d", str, lev);
+	}
+
+	for (j = 0; words[j].name && pos < len; j++) {
+		if (words[j].priority == DEFAULT_PRIORITY || levels[j] == lev || !(words[j].where & where))
+			continue;
+		if (pos)
+			buf[pos++] = ',';
+		else
+			pos += strlcpy(buf+pos, str, len-pos);
+		if (pos < len)
+			pos += strlcpy(buf+pos, words[j].name, len-pos);
+		/* Level 1 is implied by the name alone. */
+		if (levels[j] != 1 && pos < len)
+			buf[pos++] = '0' + levels[j];
+	}
+
+	buf[pos] = '\0';
+
+	return buf;
+}
+
+static void parse_output_words(struct output_struct *words, short *levels,
+			       const char *str, uchar priority)
+{
+	const char *s;
+	int j, len, lev;
+
+	if (!str)
+		return;
+
+	while (*str) {
+		if ((s = strchr(str, ',')) != NULL)
+			len = s++ - str;
+		else
+			len = strlen(str);
+		while (len && isDigit(str+len-1))
+			len--;
+		lev = isDigit(str+len) ? atoi(str+len) : 1;
+		if (lev > MAX_OUT_LEVEL)
+			lev = MAX_OUT_LEVEL;
+		if (len == 4 && strncasecmp(str, "help", 4) == 0) {
+			output_item_help(words);
+			exit_cleanup(0);
+		}
+		if (len == 4 && strncasecmp(str, "none", 4) == 0)
+			len = lev = 0;
+		else if (len == 3 && strncasecmp(str, "all", 3) == 0)
+			len = 0;
+		for (j = 0; words[j].name; j++) {
+			if (!len
+			 || (len == words[j].namelen && strncasecmp(str, words[j].name, len) == 0)) {
+				if (priority >= words[j].priority) {
+					words[j].priority = priority;
+					levels[j] = lev;
+				}
+				if (len)
+					break;
+			}
+		}
+		if (len && !words[j].name) {
+			rprintf(FERROR, "Unknown %s item: \"%.*s\"\n",
+				words[j].help, len, str);
+			exit_cleanup(RERR_SYNTAX);
+		}
+		if (!s)
+			break;
+		str = s;
+	}
+}
+
+/* Tell the user what all the info or debug flags mean. */
+static void output_item_help(struct output_struct *words)
+{
+	short *levels = words == info_words ? info_levels : debug_levels;
+	const char **verbosity = words == info_words ? info_verbosity : debug_verbosity;
+	char buf[128], *opt, *fmt = "%-10s %s\n";
+	int j;
+
+	reset_output_levels();
+
+	rprintf(FINFO, "Use OPT or OPT1 for level 1 output, OPT2 for level 2, etc.; OPT0 silences.\n");
+	rprintf(FINFO, "\n");
+	for (j = 0; words[j].name; j++)
+		rprintf(FINFO, fmt, words[j].name, words[j].help);
+	rprintf(FINFO, "\n");
+
+	snprintf(buf, sizeof buf, "Set all %s options (e.g. all%d)",
+		 words[j].help, MAX_OUT_LEVEL);
+	rprintf(FINFO, fmt, "ALL", buf);
+
+	snprintf(buf, sizeof buf, "Silence all %s options (same as all0)",
+		 words[j].help);
+	rprintf(FINFO, fmt, "NONE", buf);
+
+	rprintf(FINFO, fmt, "HELP", "Output this help message");
+	rprintf(FINFO, "\n");
+	rprintf(FINFO, "Options added for each increase in verbose level:\n");
+
+	for (j = 1; j <= MAX_VERBOSITY; j++) {
+		parse_output_words(words, levels, verbosity[j], HELP_PRIORITY);
+		opt = make_output_option(words, levels, W_CLI|W_SRV|W_SND|W_REC);
+		if (opt) {
+			rprintf(FINFO, "%d) %s\n", j, strchr(opt, '=')+1);
+			free(opt);
+		}
+		reset_output_levels();
+	}
+}
+
+/* The --verbose option now sets info+debug flags. */
+static void set_output_verbosity(int level, uchar priority)
+{
+	int j;
+
+	if (level > MAX_VERBOSITY)
+		level = MAX_VERBOSITY;
+
+	for (j = 1; j <= level; j++) {
+		parse_output_words(info_words, info_levels, info_verbosity[j], priority);
+		parse_output_words(debug_words, debug_levels, debug_verbosity[j], priority);
+	}
+}
+
+/* Limit the info+debug flag levels given a verbose-option level limit. */
+void limit_output_verbosity(int level)
+{
+	short info_limits[COUNT_INFO], debug_limits[COUNT_DEBUG];
+	int j;
+
+	if (level > MAX_VERBOSITY)
+		return;
+
+	memset(info_limits, 0, sizeof info_limits);
+	memset(debug_limits, 0, sizeof debug_limits);
+
+	/* Compute the level limits in the above arrays. */
+	for (j = 1; j <= level; j++) {
+		parse_output_words(info_words, info_limits, info_verbosity[j], LIMIT_PRIORITY);
+		parse_output_words(debug_words, debug_limits, debug_verbosity[j], LIMIT_PRIORITY);
+	}
+
+	for (j = 0; j < COUNT_INFO; j++) {
+		if (info_levels[j] > info_limits[j])
+			info_levels[j] = info_limits[j];
+	}
+
+	for (j = 0; j < COUNT_DEBUG; j++) {
+		if (debug_levels[j] > debug_limits[j])
+			debug_levels[j] = debug_limits[j];
+	}
+}
+
+void reset_output_levels(void)
+{
+	int j;
+
+	memset(info_levels, 0, sizeof info_levels);
+	memset(debug_levels, 0, sizeof debug_levels);
+
+	for (j = 0; j < COUNT_INFO; j++)
+		info_words[j].priority = DEFAULT_PRIORITY;
+
+	for (j = 0; j < COUNT_DEBUG; j++)
+		debug_words[j].priority = DEFAULT_PRIORITY;
+}
+
+void negate_output_levels(void)
+{
+	int j;
+
+	for (j = 0; j < COUNT_INFO; j++)
+		info_levels[j] *= -1;
+
+	for (j = 0; j < COUNT_DEBUG; j++)
+		debug_levels[j] *= -1;
+}
 
 static void print_rsync_version(enum logcode f)
 {
 	char *subprotocol = "";
 	char const *got_socketpair = "no ";
 	char const *have_inplace = "no ";
 	char const *hardlinks = "no ";
+	char const *prealloc = "no ";
 	char const *symtimes = "no ";
 	char const *acls = "no ";
 	char const *xattrs = "no ";
 	char const *links = "no ";
 	char const *iconv = "no ";
 	char const *ipv6 = "no ";
