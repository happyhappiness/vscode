{
				archive_set_error(a, errno,
				    "Failed to get flagset from an NFSv4 ACL entry");
				ret = ARCHIVE_FAILED;
				goto exit_free;
			}