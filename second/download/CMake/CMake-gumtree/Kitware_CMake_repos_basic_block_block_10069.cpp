(((old_offset = lseek(mine->fd, 0, SEEK_CUR)) >= 0) &&
	    ((new_offset = lseek(mine->fd, skip, SEEK_CUR)) >= 0))
		return (new_offset - old_offset);