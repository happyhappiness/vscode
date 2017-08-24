(flag & 0x80) {
		/* Use 17-byte time format. */
		if ((flag & 1) && data_length >= 17) {
			/* Create time. */
			file->birthtime_is_set = 1;
			file->birthtime = isodate17(data);
			data += 17;
			data_length -= 17;
		}
		if ((flag & 2) && data_length >= 17) {
			/* Modify time. */
			file->mtime = isodate17(data);
			data += 17;
			data_length -= 17;
		}
		if ((flag & 4) && data_length >= 17) {
			/* Access time. */
			file->atime = isodate17(data);
			data += 17;
			data_length -= 17;
		}
		if ((flag & 8) && data_length >= 17) {
			/* Attribute change time. */
			file->ctime = isodate17(data);
		}
	} else {
		/* Use 7-byte time format. */
		if ((flag & 1) && data_length >= 7) {
			/* Create time. */
			file->birthtime_is_set = 1;
			file->birthtime = isodate7(data);
			data += 7;
			data_length -= 7;
		}
		if ((flag & 2) && data_length >= 7) {
			/* Modify time. */
			file->mtime = isodate7(data);
			data += 7;
			data_length -= 7;
		}
		if ((flag & 4) && data_length >= 7) {
			/* Access time. */
			file->atime = isodate7(data);
			data += 7;
			data_length -= 7;
		}
		if ((flag & 8) && data_length >= 7) {
			/* Attribute change time. */
			file->ctime = isodate7(data);
		}
	}