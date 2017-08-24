(memcmp(p, "PK\006\006", 4) == 0
		    || memcmp(p, "PK\005\006", 4) == 0) {
			break;
		} else if (memcmp(p, "PK\001\002", 4) != 0) {
			archive_set_error(&a->archive,
			    -1, "Invalid central directory signature");
			return ARCHIVE_FATAL;
		}