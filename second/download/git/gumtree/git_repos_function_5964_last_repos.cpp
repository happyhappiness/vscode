static size_t sizeof_union(struct packed_git *p1, struct packed_git *p2)
{
	size_t ret = 0;
	unsigned long p1_off = 0, p2_off = 0, p1_step, p2_step;
	const unsigned char *p1_base, *p2_base;

	p1_base = p1->index_data;
	p2_base = p2->index_data;
	p1_base += 256 * 4 + ((p1->index_version < 2) ? 4 : 8);
	p2_base += 256 * 4 + ((p2->index_version < 2) ? 4 : 8);
	p1_step = (p1->index_version < 2) ? 24 : 20;
	p2_step = (p2->index_version < 2) ? 24 : 20;

	while (p1_off < p1->num_objects * p1_step &&
	       p2_off < p2->num_objects * p2_step)
	{
		int cmp = hashcmp(p1_base + p1_off, p2_base + p2_off);
		/* cmp ~ p1 - p2 */
		if (cmp == 0) {
			ret++;
			p1_off += p1_step;
			p2_off += p2_step;
			continue;
		}
		if (cmp < 0) { /* p1 has the object, p2 doesn't */
			p1_off += p1_step;
		} else { /* p2 has the object, p1 doesn't */
			p2_off += p2_step;
		}
	}
	return ret;
}