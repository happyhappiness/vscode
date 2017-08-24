(i = 0; i < zip->numFiles; i++) {
		if (!timeBools[i])
			continue;
		if ((p = header_bytes(a, 8)) == NULL)
			goto failed;
		switch (type) {
		case kCTime:
			fileTimeToUtc(archive_le64dec(p),
			    &(entries[i].ctime),
			    &(entries[i].ctime_ns));
			entries[i].flg |= CTIME_IS_SET;
			break;
		case kATime:
			fileTimeToUtc(archive_le64dec(p),
			    &(entries[i].atime),
			    &(entries[i].atime_ns));
			entries[i].flg |= ATIME_IS_SET;
			break;
		case kMTime:
			fileTimeToUtc(archive_le64dec(p),
			    &(entries[i].mtime),
			    &(entries[i].mtime_ns));
			entries[i].flg |= MTIME_IS_SET;
			break;
		}
	}