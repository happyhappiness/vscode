(i = 0; i < zip->numFiles; i++) {
		if (h->emptyStreamBools == NULL || h->emptyStreamBools[i] == 0)
			entries[i].flg |= HAS_STREAM;
		/* The high 16 bits of attributes is a posix file mode. */
		entries[i].mode = entries[i].attr >> 16;
		if (entries[i].flg & HAS_STREAM) {
			if ((size_t)sindex >= si->ss.unpack_streams)
				return (-1);
			if (entries[i].mode == 0)
				entries[i].mode = AE_IFREG | 0666;
			if (si->ss.digestsDefined[sindex])
				entries[i].flg |= CRC32_IS_SET;
			entries[i].ssIndex = sindex;
			sindex++;
		} else {
			int dir;
			if (h->emptyFileBools == NULL)
				dir = 1;
			else {
				if (h->emptyFileBools[eindex])
					dir = 0;
				else
					dir = 1;
				eindex++;
			}
			if (entries[i].mode == 0) {
				if (dir)
					entries[i].mode = AE_IFDIR | 0777;
				else
					entries[i].mode = AE_IFREG | 0666;
			} else if (dir &&
			    (entries[i].mode & AE_IFMT) != AE_IFDIR) {
				entries[i].mode &= ~AE_IFMT;
				entries[i].mode |= AE_IFDIR;
			}
			if ((entries[i].mode & AE_IFMT) == AE_IFDIR &&
			    entries[i].name_len >= 2 &&
			    (entries[i].utf16name[entries[i].name_len-2] != '/' ||
			     entries[i].utf16name[entries[i].name_len-1] != 0)) {
				entries[i].utf16name[entries[i].name_len] = '/';
				entries[i].utf16name[entries[i].name_len+1] = 0;
				entries[i].name_len += 2;
			}
			entries[i].ssIndex = -1;
		}
		if (entries[i].attr & 0x01)
			entries[i].mode &= ~0222;/* Read only. */

		if ((entries[i].flg & HAS_STREAM) == 0 && indexInFolder == 0) {
			/*
			 * The entry is an empty file or a directory file,
			 * those both have no contents.
			 */
			entries[i].folderIndex = -1;
			continue;
		}
		if (indexInFolder == 0) {
			for (;;) {
				if (folderIndex >= si->ci.numFolders)
					return (-1);
				if (folders[folderIndex].numUnpackStreams)
					break;
				folderIndex++;
			}
		}
		entries[i].folderIndex = folderIndex;
		if ((entries[i].flg & HAS_STREAM) == 0)
			continue;
		indexInFolder++;
		if (indexInFolder >= folders[folderIndex].numUnpackStreams) {
			folderIndex++;
			indexInFolder = 0;
		}
	}