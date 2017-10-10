	if (!progress)
		return;
	if ((++counter % progress) == 0)
		printf("progress %d objects\n", counter);
}

/*
 * Ideally we would want some transformation of the blob data here
 * that is unreversible, but would still be the same size and have
 * the same data relationship to other blobs (so that we get the same
 * delta and packing behavior as the original). But the first and last
 * requirements there are probably mutually exclusive, so let's take
 * the easy way out for now, and just generate arbitrary content.
 *
 * There's no need to cache this result with anonymize_mem, since
 * we already handle blob content caching with marks.
 */
static char *anonymize_blob(unsigned long *size)
{
	static int counter;
	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "anonymous blob %d", counter++);
	*size = out.len;
	return strbuf_detach(&out, NULL);
}

static void export_blob(const unsigned char *sha1)
{
	unsigned long size;
	enum object_type type;
	char *buf;
	struct object *object;
