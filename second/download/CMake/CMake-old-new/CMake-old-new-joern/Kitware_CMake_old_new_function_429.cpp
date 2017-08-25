static int
write_mtree_entry(struct archive_write *a, struct mtree_entry *me)
{
	struct mtree_writer *mtree = a->format_data;
	struct archive_string *str;
	int keys, ret;

	if (me->dir_info) {
		if (mtree->classic) {
			/*
			 * Output a comment line to describe the full
			 * pathname of the entry as mtree utility does
			 * while generating classic format.
			 */
			if (!mtree->dironly)
				archive_strappend_char(&mtree->buf, '\n');
			if (me->parentdir.s)
				archive_string_sprintf(&mtree->buf,
				    "# %s/%s\n",
				    me->parentdir.s, me->basename.s);
			else
				archive_string_sprintf(&mtree->buf,
				    "# %s\n",
				    me->basename.s);
		}
		if (mtree->output_global_set)
			write_global(mtree);
	}
	archive_string_empty(&mtree->ebuf);
	str = (mtree->indent || mtree->classic)? &mtree->ebuf : &mtree->buf;

	if (!mtree->classic && me->parentdir.s) {
		/*
		 * If generating format is not classic one(v1), output
		 * a full pathname.
		 */
		mtree_quote(str, me->parentdir.s);
		archive_strappend_char(str, '/');
	}
	mtree_quote(str, me->basename.s);

	keys = get_global_set_keys(mtree, me);
	if ((keys & F_NLINK) != 0 &&
	    me->nlink != 1 && me->filetype != AE_IFDIR)
		archive_string_sprintf(str, " nlink=%u", me->nlink);

	if ((keys & F_GNAME) != 0 && archive_strlen(&me->gname) > 0) {
		archive_strcat(str, " gname=");
		mtree_quote(str, me->gname.s);
	}
	if ((keys & F_UNAME) != 0 && archive_strlen(&me->uname) > 0) {
		archive_strcat(str, " uname=");
		mtree_quote(str, me->uname.s);
	}
	if ((keys & F_FLAGS) != 0) {
		if (archive_strlen(&me->fflags_text) > 0) {
			archive_strcat(str, " flags=");
			mtree_quote(str, me->fflags_text.s);
		} else if (mtree->set.processing &&
		    (mtree->set.keys & F_FLAGS) != 0)
			/* Overwrite the global parameter. */
			archive_strcat(str, " flags=none");
	}
	if ((keys & F_TIME) != 0)
		archive_string_sprintf(str, " time=%jd.%jd",
		    (intmax_t)me->mtime, (intmax_t)me->mtime_nsec);
	if ((keys & F_MODE) != 0)
		archive_string_sprintf(str, " mode=%o", (unsigned int)me->mode);
	if ((keys & F_GID) != 0)
		archive_string_sprintf(str, " gid=%jd", (intmax_t)me->gid);
	if ((keys & F_UID) != 0)
		archive_string_sprintf(str, " uid=%jd", (intmax_t)me->uid);

	switch (me->filetype) {
	case AE_IFLNK:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=link");
		if ((keys & F_SLINK) != 0) {
			archive_strcat(str, " link=");
			mtree_quote(str, me->symlink.s);
		}
		break;
	case AE_IFSOCK:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=socket");
		break;
	case AE_IFCHR:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=char");
		if ((keys & F_DEV) != 0) {
			archive_string_sprintf(str,
			    " device=native,%ju,%ju",
			    (uintmax_t)me->rdevmajor,
			    (uintmax_t)me->rdevminor);
		}
		break;
	case AE_IFBLK:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=block");
		if ((keys & F_DEV) != 0) {
			archive_string_sprintf(str,
			    " device=native,%ju,%ju",
			    (uintmax_t)me->rdevmajor,
			    (uintmax_t)me->rdevminor);
		}
		break;
	case AE_IFDIR:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=dir");
		break;
	case AE_IFIFO:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=fifo");
		break;
	case AE_IFREG:
	default:	/* Handle unknown file types as regular files. */
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=file");
		if ((keys & F_SIZE) != 0)
			archive_string_sprintf(str, " size=%jd",
			    (intmax_t)me->size);
		break;
	}

	/* Write a bunch of sum. */
	if (me->reg_info)
		sum_write(str, me->reg_info);

	archive_strappend_char(str, '\n');
	if (mtree->indent || mtree->classic)
		mtree_indent(mtree);

	if (mtree->buf.length > 32768) {
		ret = __archive_write_output(
			a, mtree->buf.s, mtree->buf.length);
		archive_string_empty(&mtree->buf);
	} else
		ret = ARCHIVE_OK;
	return (ret);
}