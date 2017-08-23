{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Username too long");
			ret = ARCHIVE_FAILED;
			copy_length = USTAR_uname_size;
		}