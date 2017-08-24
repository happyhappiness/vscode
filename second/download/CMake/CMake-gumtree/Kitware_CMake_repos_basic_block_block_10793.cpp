((entries[i].flg & HAS_STREAM) == 0 && indexInFolder == 0) {
			/*
			 * The entry is an empty file or a directory file,
			 * those both have no contents.
			 */
			entries[i].folderIndex = -1;
			continue;
		}