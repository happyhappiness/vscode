(a->fd < 0 || fchflags(a->fd, UF_COMPRESSED) != 0)
			a->todo &= ~TODO_HFS_COMPRESSION