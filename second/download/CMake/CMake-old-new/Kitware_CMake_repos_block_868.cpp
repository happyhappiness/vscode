{
			archive_set_error(&a->archive, errno,
			    "Couldn't translate "
#if !HAVE_SUN_ACL
			    "NFSv4 "
#endif
			    "ACLs");
		}