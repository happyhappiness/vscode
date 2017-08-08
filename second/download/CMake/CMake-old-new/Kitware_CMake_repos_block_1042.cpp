{
#if HAVE_SUN_ACL
			errno = EINVAL;
#endif
			archive_set_error(a, errno,
			    "Failed to set ACL entry type");
			ret = ARCHIVE_FAILED;
			goto exit_free;
		}