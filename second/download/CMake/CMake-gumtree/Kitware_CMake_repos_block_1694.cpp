{
			archive_set_error(&a->archive, ENAMETOOLONG,
			    "Link contents too long");
			ret = ARCHIVE_FAILED;
			copy_length = V7TAR_linkname_size;
		}