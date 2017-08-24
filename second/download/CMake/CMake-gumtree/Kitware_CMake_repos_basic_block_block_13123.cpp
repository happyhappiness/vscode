{
			step = __archive_read_consume(a, step);
			if (step < 0)
				return ((int)step);
			xar->offset += step;
		}