static void sort_revindex(struct revindex_entry *entries, unsigned n, off_t max)
{
	/*
	 * We use a "digit" size of 16 bits. That keeps our memory
	 * usage reasonable, and we can generally (for a 4G or smaller
	 * packfile) quit after two rounds of radix-sorting.
	 */
#define DIGIT_SIZE (16)
#define BUCKETS (1 << DIGIT_SIZE)
	/*
	 * We want to know the bucket that a[i] will go into when we are using
	 * the digit that is N bits from the (least significant) end.
	 */
#define BUCKET_FOR(a, i, bits) (((a)[(i)].offset >> (bits)) & (BUCKETS-1))

	/*
	 * We need O(n) temporary storage. Rather than do an extra copy of the
	 * partial results into "entries", we sort back and forth between the
	 * real array and temporary storage. In each iteration of the loop, we
	 * keep track of them with alias pointers, always sorting from "from"
	 * to "to".
	 */
	struct revindex_entry *tmp, *from, *to;
	int bits;
	unsigned *pos;

	ALLOC_ARRAY(pos, BUCKETS);
	ALLOC_ARRAY(tmp, n);
	from = entries;
	to = tmp;

	/*
	 * If (max >> bits) is zero, then we know that the radix digit we are
	 * on (and any higher) will be zero for all entries, and our loop will
	 * be a no-op, as everybody lands in the same zero-th bucket.
	 */
	for (bits = 0; max >> bits; bits += DIGIT_SIZE) {
		unsigned i;

		memset(pos, 0, BUCKETS * sizeof(*pos));

		/*
		 * We want pos[i] to store the index of the last element that
		 * will go in bucket "i" (actually one past the last element).
		 * To do this, we first count the items that will go in each
		 * bucket, which gives us a relative offset from the last
		 * bucket. We can then cumulatively add the index from the
		 * previous bucket to get the true index.
		 */
		for (i = 0; i < n; i++)
			pos[BUCKET_FOR(from, i, bits)]++;
		for (i = 1; i < BUCKETS; i++)
			pos[i] += pos[i-1];

		/*
		 * Now we can drop the elements into their correct buckets (in
		 * our temporary array).  We iterate the pos counter backwards
		 * to avoid using an extra index to count up. And since we are
		 * going backwards there, we must also go backwards through the
		 * array itself, to keep the sort stable.
		 *
		 * Note that we use an unsigned iterator to make sure we can
		 * handle 2^32-1 objects, even on a 32-bit system. But this
		 * means we cannot use the more obvious "i >= 0" loop condition
		 * for counting backwards, and must instead check for
		 * wrap-around with UINT_MAX.
		 */
		for (i = n - 1; i != UINT_MAX; i--)
			to[--pos[BUCKET_FOR(from, i, bits)]] = from[i];

		/*
		 * Now "to" contains the most sorted list, so we swap "from" and
		 * "to" for the next iteration.
		 */
		SWAP(from, to);
	}

	/*
	 * If we ended with our data in the original array, great. If not,
	 * we have to move it back from the temporary storage.
	 */
	if (from != entries)
		COPY_ARRAY(entries, tmp, n);
	free(tmp);
	free(pos);

#undef BUCKET_FOR
#undef BUCKETS
#undef DIGIT_SIZE
}