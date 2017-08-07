{
				archive_set_error(a, errno,
				    "Failed to clear flags from an NFSv4 ACL flagset");
				ret = ARCHIVE_FAILED;
				goto exit_free;
			}