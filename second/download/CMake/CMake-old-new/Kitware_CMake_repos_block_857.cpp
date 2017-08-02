{
				archive_set_error(&a->archive, errno,
				    "Couldn't read link data");
				free(linkbuffer);
				return (ARCHIVE_FAILED);
			}