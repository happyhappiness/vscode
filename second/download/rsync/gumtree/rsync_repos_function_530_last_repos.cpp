static struct file_struct *send_file_name(int f, struct file_list *flist,
					  const char *fname, STRUCT_STAT *stp,
					  int flags, int filter_level)
{
	struct file_struct *file;

	file = make_file(fname, flist, stp, flags, filter_level);
	if (!file)
		return NULL;

	if (chmod_modes && !S_ISLNK(file->mode) && file->mode)
		file->mode = tweak_mode(file->mode, chmod_modes);

	if (f >= 0) {
		char fbuf[MAXPATHLEN];
#ifdef SUPPORT_LINKS
		const char *symlink_name;
		int symlink_len;
#ifdef ICONV_OPTION
		char symlink_buf[MAXPATHLEN];
#endif
#endif
#if defined SUPPORT_ACLS || defined SUPPORT_XATTRS
		stat_x sx;
		init_stat_x(&sx);
#endif

#ifdef SUPPORT_LINKS
		if (preserve_links && S_ISLNK(file->mode)) {
			symlink_name = F_SYMLINK(file);
			symlink_len = strlen(symlink_name);
			if (symlink_len == 0) {
				io_error |= IOERR_GENERAL;
				f_name(file, fbuf);
				rprintf(FERROR_XFER,
				    "skipping symlink with 0-length value: %s\n",
				    full_fname(fbuf));
				return NULL;
			}
		} else {
			symlink_name = NULL;
			symlink_len = 0;
		}
#endif

#ifdef ICONV_OPTION
		if (ic_send != (iconv_t)-1) {
			xbuf outbuf, inbuf;

			INIT_CONST_XBUF(outbuf, fbuf);

			if (file->dirname) {
				INIT_XBUF_STRLEN(inbuf, (char*)file->dirname);
				outbuf.size -= 2; /* Reserve room for '/' & 1 more char. */
				if (iconvbufs(ic_send, &inbuf, &outbuf, ICB_INIT) < 0)
					goto convert_error;
				outbuf.size += 2;
				fbuf[outbuf.len++] = '/';
			}

			INIT_XBUF_STRLEN(inbuf, (char*)file->basename);
			if (iconvbufs(ic_send, &inbuf, &outbuf, ICB_INIT) < 0) {
			  convert_error:
				io_error |= IOERR_GENERAL;
				rprintf(FERROR_XFER,
				    "[%s] cannot convert filename: %s (%s)\n",
				    who_am_i(), f_name(file, fbuf), strerror(errno));
				return NULL;
			}
			fbuf[outbuf.len] = '\0';

#ifdef SUPPORT_LINKS
			if (symlink_len && sender_symlink_iconv) {
				INIT_XBUF(inbuf, (char*)symlink_name, symlink_len, (size_t)-1);
				INIT_CONST_XBUF(outbuf, symlink_buf);
				if (iconvbufs(ic_send, &inbuf, &outbuf, ICB_INIT) < 0) {
					io_error |= IOERR_GENERAL;
					f_name(file, fbuf);
					rprintf(FERROR_XFER,
					    "[%s] cannot convert symlink data for: %s (%s)\n",
					    who_am_i(), full_fname(fbuf), strerror(errno));
					return NULL;
				}
				symlink_buf[outbuf.len] = '\0';

				symlink_name = symlink_buf;
				symlink_len = outbuf.len;
			}
#endif
		} else
#endif
			f_name(file, fbuf);

#ifdef SUPPORT_ACLS
		if (preserve_acls && !S_ISLNK(file->mode)) {
			sx.st.st_mode = file->mode;
			if (get_acl(fname, &sx) < 0) {
				io_error |= IOERR_GENERAL;
				return NULL;
			}
		}
#endif
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs) {
			sx.st.st_mode = file->mode;
			if (get_xattr(fname, &sx) < 0) {
				io_error |= IOERR_GENERAL;
				return NULL;
			}
		}
#endif

		send_file_entry(f, fbuf, file,
#ifdef SUPPORT_LINKS
				symlink_name, symlink_len,
#endif
				flist->used, flist->ndx_start);

#ifdef SUPPORT_ACLS
		if (preserve_acls && !S_ISLNK(file->mode)) {
			send_acl(f, &sx);
			free_acl(&sx);
		}
#endif
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs) {
			F_XATTR(file) = send_xattr(f, &sx);
			free_xattr(&sx);
		}
#endif
	}

	maybe_emit_filelist_progress(flist->used + flist_count_offset);

	flist_expand(flist, 1);
	flist->files[flist->used++] = file;

	return file;
}