{
						archive_set_error(a, errno,
						    "Failed to add flag to NFSv4 ACL flagset");
						ret = ARCHIVE_FAILED;
						goto exit_free;
					}