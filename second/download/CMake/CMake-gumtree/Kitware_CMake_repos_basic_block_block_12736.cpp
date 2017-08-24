{
			a->archive.archive_format = ARCHIVE_FORMAT_TAR;
			a->archive.archive_format_name = "tar (non-POSIX)";
			err = header_old_tar(a, tar, entry, h);
		}