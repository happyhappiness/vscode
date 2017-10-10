
volatile show_early_output_fn_t show_early_output;

static const char *term_bad;
static const char *term_good;

void show_object_with_name(FILE *out, struct object *obj, const char *name)
{
	const char *p;

	fprintf(out, "%s ", oid_to_hex(&obj->oid));
	for (p = name; *p && *p != '\n'; p++)
		fputc(*p, out);
	fputc('\n', out);
}

static void mark_blob_uninteresting(struct blob *blob)
{
	if (!blob)
