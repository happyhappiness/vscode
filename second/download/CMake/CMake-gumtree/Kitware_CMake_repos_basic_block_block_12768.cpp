(*p < '0' || *p > '7') {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed Solaris ACL attribute (invalid digit)");
			return(ARCHIVE_WARN);
		}