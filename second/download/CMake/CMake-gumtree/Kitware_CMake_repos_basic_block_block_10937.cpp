{
		if (zip->header_is_being_read) {
			/* Invalid sequence. This might happen when
			 * reading a malformed archive. */
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC, "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/*
		 * All current folder's pack streams have been
		 * consumed. Switch to next folder.
		 */
		if (zip->folder_index == 0 &&
		    (zip->si.ci.folders[zip->entry->folderIndex].skipped_bytes
		     || zip->folder_index != zip->entry->folderIndex)) {
			zip->folder_index = zip->entry->folderIndex;
			skip_bytes =
			    zip->si.ci.folders[zip->folder_index].skipped_bytes;
		}

		if (zip->folder_index >= zip->si.ci.numFolders) {
			/*
			 * We have consumed all folders and its pack streams.
			 */
			*buff = NULL;
			return (0);
		}
		r = setup_decode_folder(a,
			&(zip->si.ci.folders[zip->folder_index]), 0);
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);

		zip->folder_index++;
	}