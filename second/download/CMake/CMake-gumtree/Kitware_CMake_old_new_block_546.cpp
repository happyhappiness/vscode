{
				archive_set_error(&a->archive, errno,
				    "FIEMAP failed");
				exit_sts = ARCHIVE_FAILED;
			}