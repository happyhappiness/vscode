{
			/* Modify time. */
			file->mtime = isodate17(data);
			data += 17;
			data_length -= 17;
		}