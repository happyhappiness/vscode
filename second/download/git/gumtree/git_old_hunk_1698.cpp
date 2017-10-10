	if (!progress)
		return;
	if ((++counter % progress) == 0)
		printf("progress %d objects\n", counter);
}

static void export_blob(const unsigned char *sha1)
{
	unsigned long size;
	enum object_type type;
	char *buf;
	struct object *object;
