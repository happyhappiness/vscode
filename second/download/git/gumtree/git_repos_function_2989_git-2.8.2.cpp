void sha1write(struct sha1file *f, const void *buf, unsigned int count)
{
	while (count) {
		unsigned offset = f->offset;
		unsigned left = sizeof(f->buffer) - offset;
		unsigned nr = count > left ? left : count;
		const void *data;

		if (f->do_crc)
			f->crc32 = crc32(f->crc32, buf, nr);

		if (nr == sizeof(f->buffer)) {
			/* process full buffer directly without copy */
			data = buf;
		} else {
			memcpy(f->buffer + offset, buf, nr);
			data = f->buffer;
		}

		count -= nr;
		offset += nr;
		buf = (char *) buf + nr;
		left -= nr;
		if (!left) {
			git_SHA1_Update(&f->ctx, data, offset);
			flush(f, data, offset);
			offset = 0;
		}
		f->offset = offset;
	}
}