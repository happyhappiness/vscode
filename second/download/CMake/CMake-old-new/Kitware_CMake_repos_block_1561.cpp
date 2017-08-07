{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed Solaris ACL attribute (count too large)");
			return (ARCHIVE_WARN);
		}