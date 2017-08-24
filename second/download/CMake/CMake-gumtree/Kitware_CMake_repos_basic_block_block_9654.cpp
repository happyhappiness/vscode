(fpathconf(*fd, _PC_MIN_HOLE_SIZE) <= 0)
			return (ARCHIVE_OK);