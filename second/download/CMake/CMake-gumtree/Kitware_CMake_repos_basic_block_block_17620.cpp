(val == NULL || !(val[0] >= '0' && val[0] <= '9') || val[1] != '\0') {
			return ARCHIVE_WARN;
		}