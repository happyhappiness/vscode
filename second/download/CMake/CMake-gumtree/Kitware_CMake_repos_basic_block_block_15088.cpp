(st->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		*mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH