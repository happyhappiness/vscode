{
			/* Access time. */
			file->atime = isodate7(data);
			data += 7;
			data_length -= 7;
		}