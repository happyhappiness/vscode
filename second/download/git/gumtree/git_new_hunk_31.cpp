				sizeof(struct commit_graft *)
				* (commit_graft_nr - pos - 1));
	commit_graft_nr--;
	return 0;
}

struct commit_buffer {
	void *buffer;
	unsigned long size;
};
define_commit_slab(buffer_slab, struct commit_buffer);
static struct buffer_slab buffer_slab = COMMIT_SLAB_INIT(1, buffer_slab);

void set_commit_buffer(struct commit *commit, void *buffer, unsigned long size)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	v->buffer = buffer;
	v->size = size;
}

const void *get_cached_commit_buffer(const struct commit *commit, unsigned long *sizep)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	if (sizep)
		*sizep = v->size;
	return v->buffer;
}

const void *get_commit_buffer(const struct commit *commit, unsigned long *sizep)
{
	const void *ret = get_cached_commit_buffer(commit, sizep);
	if (!ret) {
		enum object_type type;
		unsigned long size;
		ret = read_sha1_file(commit->object.sha1, &type, &size);
		if (!ret)
			die("cannot read commit object %s",
			    sha1_to_hex(commit->object.sha1));
		if (type != OBJ_COMMIT)
			die("expected commit for %s, got %s",
			    sha1_to_hex(commit->object.sha1), typename(type));
		if (sizep)
			*sizep = size;
	}
	return ret;
}

void unuse_commit_buffer(const struct commit *commit, const void *buffer)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	if (v->buffer != buffer)
		free((void *)buffer);
}

void free_commit_buffer(struct commit *commit)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	free(v->buffer);
	v->buffer = NULL;
	v->size = 0;
}

const void *detach_commit_buffer(struct commit *commit, unsigned long *sizep)
{
	struct commit_buffer *v = buffer_slab_at(&buffer_slab, commit);
	void *ret;

	ret = v->buffer;
	if (sizep)
		*sizep = v->size;

	v->buffer = NULL;
	v->size = 0;
	return ret;
}

int parse_commit_buffer(struct commit *item, const void *buffer, unsigned long size)
{
	const char *tail = buffer;
	const char *bufptr = buffer;
	unsigned char parent[20];
	struct commit_list **pptr;
