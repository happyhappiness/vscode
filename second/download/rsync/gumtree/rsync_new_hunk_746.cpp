					return -1;
				if (!r1 && len)
					continue;
			}
		}
		if (r1 <= 0) {
			if (ret > 0)
				return ret;
			return r1;
		}
		len -= r1;
		buf += r1;
		ret += r1;
	}
	return ret;
}


/* This provides functionality somewhat similar to mmap() but using read().
 * It gives sliding window access to a file.  mmap() is not used because of
 * the possibility of another program (such as a mailer) truncating the
 * file thus giving us a SIGBUS. */
struct map_struct *map_file(int fd, OFF_T len, OFF_T map_size,
			    size_t block_size)
{
	struct map_struct *map;

	if (!(map = new(struct map_struct)))
		out_of_memory("map_file");

	if (block_size && (map_size % block_size))
		map_size += block_size - (map_size % block_size);

	memset(map, 0, sizeof map[0]);
	map->fd = fd;
	map->file_size = len;
	map->def_window_size = map_size;

	return map;
}


/* slide the read window in the file */
char *map_ptr(struct map_struct *map,OFF_T offset,int len)
{
	int nread;
	OFF_T window_start, read_start;
	int window_size, read_size, read_offset;
