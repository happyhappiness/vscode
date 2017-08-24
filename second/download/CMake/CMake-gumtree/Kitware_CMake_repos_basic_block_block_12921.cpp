{
		if (gnu_add_sparse_entry(a, tar,
		    tar_atol(sparse->offset, sizeof(sparse->offset)),
		    tar_atol(sparse->numbytes, sizeof(sparse->numbytes)))
		    != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		sparse++;
		length--;
	}