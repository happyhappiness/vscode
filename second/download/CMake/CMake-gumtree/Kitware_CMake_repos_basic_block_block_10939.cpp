(zip->folder_index >= zip->si.ci.numFolders) {
			/*
			 * We have consumed all folders and its pack streams.
			 */
			*buff = NULL;
			return (0);
		}