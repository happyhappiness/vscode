{
			memmove(dict->buf + dict->pos, dict->buf + copy_pos,
					left);
			dict->pos += left;
		}