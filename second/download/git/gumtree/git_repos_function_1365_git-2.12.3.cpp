void *
create_delta(const struct delta_index *index,
	     const void *trg_buf, unsigned long trg_size,
	     unsigned long *delta_size, unsigned long max_size)
{
	unsigned int i, outpos, outsize, moff, msize, val;
	int inscnt;
	const unsigned char *ref_data, *ref_top, *data, *top;
	unsigned char *out;

	if (!trg_buf || !trg_size)
		return NULL;

	outpos = 0;
	outsize = 8192;
	if (max_size && outsize >= max_size)
		outsize = max_size + MAX_OP_SIZE + 1;
	out = malloc(outsize);
	if (!out)
		return NULL;

	/* store reference buffer size */
	i = index->src_size;
	while (i >= 0x80) {
		out[outpos++] = i | 0x80;
		i >>= 7;
	}
	out[outpos++] = i;

	/* store target buffer size */
	i = trg_size;
	while (i >= 0x80) {
		out[outpos++] = i | 0x80;
		i >>= 7;
	}
	out[outpos++] = i;

	ref_data = index->src_buf;
	ref_top = ref_data + index->src_size;
	data = trg_buf;
	top = (const unsigned char *) trg_buf + trg_size;

	outpos++;
	val = 0;
	for (i = 0; i < RABIN_WINDOW && data < top; i++, data++) {
		out[outpos++] = *data;
		val = ((val << 8) | *data) ^ T[val >> RABIN_SHIFT];
	}
	inscnt = i;

	moff = 0;
	msize = 0;
	while (data < top) {
		if (msize < 4096) {
			struct index_entry *entry;
			val ^= U[data[-RABIN_WINDOW]];
			val = ((val << 8) | *data) ^ T[val >> RABIN_SHIFT];
			i = val & index->hash_mask;
			for (entry = index->hash[i]; entry < index->hash[i+1]; entry++) {
				const unsigned char *ref = entry->ptr;
				const unsigned char *src = data;
				unsigned int ref_size = ref_top - ref;
				if (entry->val != val)
					continue;
				if (ref_size > top - src)
					ref_size = top - src;
				if (ref_size <= msize)
					break;
				while (ref_size-- && *src++ == *ref)
					ref++;
				if (msize < ref - entry->ptr) {
					/* this is our best match so far */
					msize = ref - entry->ptr;
					moff = entry->ptr - ref_data;
					if (msize >= 4096) /* good enough */
						break;
				}
			}
		}

		if (msize < 4) {
			if (!inscnt)
				outpos++;
			out[outpos++] = *data++;
			inscnt++;
			if (inscnt == 0x7f) {
				out[outpos - inscnt - 1] = inscnt;
				inscnt = 0;
			}
			msize = 0;
		} else {
			unsigned int left;
			unsigned char *op;

			if (inscnt) {
				while (moff && ref_data[moff-1] == data[-1]) {
					/* we can match one byte back */
					msize++;
					moff--;
					data--;
					outpos--;
					if (--inscnt)
						continue;
					outpos--;  /* remove count slot */
					inscnt--;  /* make it -1 */
					break;
				}
				out[outpos - inscnt - 1] = inscnt;
				inscnt = 0;
			}

			/* A copy op is currently limited to 64KB (pack v2) */
			left = (msize < 0x10000) ? 0 : (msize - 0x10000);
			msize -= left;

			op = out + outpos++;
			i = 0x80;

			if (moff & 0x000000ff)
				out[outpos++] = moff >> 0,  i |= 0x01;
			if (moff & 0x0000ff00)
				out[outpos++] = moff >> 8,  i |= 0x02;
			if (moff & 0x00ff0000)
				out[outpos++] = moff >> 16, i |= 0x04;
			if (moff & 0xff000000)
				out[outpos++] = moff >> 24, i |= 0x08;

			if (msize & 0x00ff)
				out[outpos++] = msize >> 0, i |= 0x10;
			if (msize & 0xff00)
				out[outpos++] = msize >> 8, i |= 0x20;

			*op = i;

			data += msize;
			moff += msize;
			msize = left;

			if (msize < 4096) {
				int j;
				val = 0;
				for (j = -RABIN_WINDOW; j < 0; j++)
					val = ((val << 8) | data[j])
					      ^ T[val >> RABIN_SHIFT];
			}
		}

		if (outpos >= outsize - MAX_OP_SIZE) {
			void *tmp = out;
			outsize = outsize * 3 / 2;
			if (max_size && outsize >= max_size)
				outsize = max_size + MAX_OP_SIZE + 1;
			if (max_size && outpos > max_size)
				break;
			out = realloc(out, outsize);
			if (!out) {
				free(tmp);
				return NULL;
			}
		}
	}

	if (inscnt)
		out[outpos - inscnt - 1] = inscnt;

	if (max_size && outpos > max_size) {
		free(out);
		return NULL;
	}

	*delta_size = outpos;
	return out;
}