{
			archive_set_error(a, errno,
			    "Failed to clear ACL permissions");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}