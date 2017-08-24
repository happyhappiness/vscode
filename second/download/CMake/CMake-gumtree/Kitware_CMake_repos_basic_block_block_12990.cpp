{
			/* populate entry object */
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_copy_pathname(entry, fnam.str);
			archive_entry_set_size(entry, cntlen);
			archive_entry_set_perm(entry, 0644);
			/* rtime is the new ctime, mtime stays mtime */
			archive_entry_set_ctime(entry, rtime, 0L);
			archive_entry_set_mtime(entry, mtime, 0L);
			break;
		}