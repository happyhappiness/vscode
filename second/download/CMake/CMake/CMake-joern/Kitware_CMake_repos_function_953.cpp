static int
make_fflags_entry(struct archive_write *a, xmlTextWriterPtr writer,
    const char *element, const char *fflags_text)
{
	static const struct flagentry {
		const char	*name;
		const char	*xarname;
	}
	flagbsd[] = {
		{ "sappnd",	"SystemAppend"},
		{ "sappend",	"SystemAppend"},
		{ "arch",	"SystemArchived"},
		{ "archived",	"SystemArchived"},
		{ "schg",	"SystemImmutable"},
		{ "schange",	"SystemImmutable"},
		{ "simmutable",	"SystemImmutable"},
		{ "nosunlnk",	"SystemNoUnlink"},
		{ "nosunlink",	"SystemNoUnlink"},
		{ "snapshot",	"SystemSnapshot"},
		{ "uappnd",	"UserAppend"},
		{ "uappend",	"UserAppend"},
		{ "uchg",	"UserImmutable"},
		{ "uchange",	"UserImmutable"},
		{ "uimmutable",	"UserImmutable"},
		{ "nodump",	"UserNoDump"},
		{ "noopaque",	"UserOpaque"},
		{ "nouunlnk",	"UserNoUnlink"},
		{ "nouunlink",	"UserNoUnlink"},
		{ NULL, NULL}
	},
	flagext2[] = {
		{ "sappnd",	"AppendOnly"},
		{ "sappend",	"AppendOnly"},
		{ "schg",	"Immutable"},
		{ "schange",	"Immutable"},
		{ "simmutable",	"Immutable"},
		{ "nodump",	"NoDump"},
		{ "nouunlnk",	"Undelete"},
		{ "nouunlink",	"Undelete"},
		{ "btree",	"BTree"},
		{ "comperr",	"CompError"},
		{ "compress",	"Compress"},
		{ "noatime",	"NoAtime"},
		{ "compdirty",	"CompDirty"},
		{ "comprblk",	"CompBlock"},
		{ "dirsync",	"DirSync"},
		{ "hashidx",	"HashIndexed"},
		{ "imagic",	"iMagic"},
		{ "journal",	"Journaled"},
		{ "securedeletion",	"SecureDeletion"},
		{ "sync",	"Synchronous"},
		{ "notail",	"NoTail"},
		{ "topdir",	"TopDir"},
		{ "reserved",	"Reserved"},
		{ NULL, NULL}
	};
	const struct flagentry *fe, *flagentry;
#define FLAGENTRY_MAXSIZE ((sizeof(flagbsd)+sizeof(flagext2))/sizeof(flagbsd))
	const struct flagentry *avail[FLAGENTRY_MAXSIZE];
	const char *p;
	int i, n, r;

	if (strcmp(element, "ext2") == 0)
		flagentry = flagext2;
	else
		flagentry = flagbsd;
	n = 0;
	p = fflags_text;
	do {
		const char *cp;

		cp = strchr(p, ',');
		if (cp == NULL)
			cp = p + strlen(p);

		for (fe = flagentry; fe->name != NULL; fe++) {
			if (fe->name[cp - p] != '\0'
			    || p[0] != fe->name[0])
				continue;
			if (strncmp(p, fe->name, cp - p) == 0) {
				avail[n++] = fe;
				break;
			}
		}
		if (*cp == ',')
			p = cp + 1;
		else
			p = NULL;
	} while (p != NULL);

	if (n > 0) {
		r = xmlTextWriterStartElement(writer, BAD_CAST_CONST(element));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		for (i = 0; i < n; i++) {
			r = xmlwrite_string(a, writer,
			    avail[i]->xarname, NULL);
			if (r != ARCHIVE_OK)
				return (r);
		}

		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}
	return (ARCHIVE_OK);
}