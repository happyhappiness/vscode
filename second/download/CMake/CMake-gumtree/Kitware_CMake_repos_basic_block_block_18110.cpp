do {
			dict->buf[dict->pos] = dict_get(dict, distance);
			++dict->pos;
		} while (--left > 0);