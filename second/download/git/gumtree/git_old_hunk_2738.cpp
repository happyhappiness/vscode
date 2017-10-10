static unsigned long garbage;
static off_t size_garbage;
static int verbose;
static unsigned long loose, packed, packed_loose;
static off_t loose_size;

static void real_report_garbage(const char *desc, const char *path)
{
	struct stat st;
	if (!stat(path, &st))
		size_garbage += st.st_size;
	warning("%s: %s", desc, path);
	garbage++;
}

static void loose_garbage(const char *path)
{
	if (verbose)
		report_garbage("garbage found", path);
}

static int count_loose(const unsigned char *sha1, const char *path, void *data)
{
	struct stat st;

