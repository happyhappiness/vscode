void itemize(struct file_struct *file, int ndx, int statret, STRUCT_STAT *st,
	     int32 iflags, uchar fnamecmp_type, char *xname)
{
	if (statret == 0) {
		if (S_ISREG(file->mode) && file->length != st->st_size)
			iflags |= ITEM_REPORT_SIZE;
		if (!(iflags & ITEM_NO_DEST_AND_NO_UPDATE)) {
			int keep_time = !preserve_times ? 0
			    : S_ISDIR(file->mode) ? !omit_dir_times
			    : !S_ISLNK(file->mode);

			if ((iflags & (ITEM_TRANSFER|ITEM_LOCAL_CHANGE) && !keep_time
			     && (!(iflags & ITEM_XNAME_FOLLOWS) || *xname))
			    || (keep_time && cmp_modtime(file->modtime, st->st_mtime) != 0))
				iflags |= ITEM_REPORT_TIME;
			if (preserve_perms
			 && (file->mode & CHMOD_BITS) != (st->st_mode & CHMOD_BITS))
				iflags |= ITEM_REPORT_PERMS;
			if (preserve_uid && am_root && file->uid != st->st_uid)
				iflags |= ITEM_REPORT_OWNER;
			if (preserve_gid && file->gid != GID_NONE
			    && st->st_gid != file->gid)
				iflags |= ITEM_REPORT_GROUP;
		}
	} else
		iflags |= ITEM_IS_NEW;

	iflags &= 0xffff;
	if ((iflags & SIGNIFICANT_ITEM_FLAGS || verbose > 1
	  || (xname && *xname)) && !read_batch) {
		if (protocol_version >= 29) {
			if (ndx >= 0)
				write_int(sock_f_out, ndx);
			write_shortint(sock_f_out, iflags);
			if (iflags & ITEM_BASIS_TYPE_FOLLOWS)
				write_byte(sock_f_out, fnamecmp_type);
			if (iflags & ITEM_XNAME_FOLLOWS)
				write_vstring(sock_f_out, xname, strlen(xname));
		} else if (ndx >= 0)
			log_item(file, &stats, iflags, xname);
	}
}