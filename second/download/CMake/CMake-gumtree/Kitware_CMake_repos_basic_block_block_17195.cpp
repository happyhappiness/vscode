(strlen(p) > USTAR_gname_size) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Group name too long");
			ret = ARCHIVE_FAILED;
			copy_length = USTAR_gname_size;
		}