{
			/* We tried, but couldn't get rid of it. */
			archive_set_error(&a->archive, errno,
			    "Could not unlink");
			return(ARCHIVE_FAILED);
		}