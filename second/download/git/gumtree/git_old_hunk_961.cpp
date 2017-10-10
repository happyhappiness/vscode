	for_each_replace_ref(show_reference, (void *)&data);

	return 0;
}

typedef int (*each_replace_name_fn)(const char *name, const char *ref,
				    const unsigned char *sha1);

static int for_each_replace_name(const char **argv, each_replace_name_fn fn)
{
	const char **p, *full_hex;
	char ref[PATH_MAX];
	int had_error = 0;
	unsigned char sha1[20];

	for (p = argv; *p; p++) {
		if (get_sha1(*p, sha1)) {
			error("Failed to resolve '%s' as a valid ref.", *p);
			had_error = 1;
			continue;
		}
		full_hex = sha1_to_hex(sha1);
		snprintf(ref, sizeof(ref), "%s%s", git_replace_ref_base, full_hex);
		/* read_ref() may reuse the buffer */
		full_hex = ref + strlen(git_replace_ref_base);
		if (read_ref(ref, sha1)) {
			error("replace ref '%s' not found.", full_hex);
			had_error = 1;
			continue;
		}
		if (fn(full_hex, ref, sha1))
			had_error = 1;
	}
	return had_error;
}

static int delete_replace_ref(const char *name, const char *ref,
			      const unsigned char *sha1)
{
	if (delete_ref(ref, sha1, 0))
		return 1;
	printf("Deleted replace ref '%s'\n", name);
	return 0;
}

static void check_ref_valid(unsigned char object[20],
			    unsigned char prev[20],
			    char *ref,
			    int ref_size,
			    int force)
{
	if (snprintf(ref, ref_size,
		     "%s%s", git_replace_ref_base,
		     sha1_to_hex(object)) > ref_size - 1)
		die("replace ref name too long: %.*s...", 50, ref);
	if (check_refname_format(ref, 0))
		die("'%s' is not a valid ref name.", ref);

	if (read_ref(ref, prev))
		hashclr(prev);
	else if (!force)
		die("replace ref '%s' already exists", ref);
}

static int replace_object_sha1(const char *object_ref,
			       unsigned char object[20],
			       const char *replace_ref,
			       unsigned char repl[20],
			       int force)
{
	unsigned char prev[20];
	enum object_type obj_type, repl_type;
	char ref[PATH_MAX];
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	obj_type = sha1_object_info(object, NULL);
	repl_type = sha1_object_info(repl, NULL);
	if (!force && obj_type != repl_type)
		die("Objects must be of the same type.\n"
		    "'%s' points to a replaced object of type '%s'\n"
		    "while '%s' points to a replacement object of type '%s'.",
		    object_ref, typename(obj_type),
		    replace_ref, typename(repl_type));

	check_ref_valid(object, prev, ref, sizeof(ref), force);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, ref, repl, prev,
				   0, NULL, &err) ||
	    ref_transaction_commit(transaction, &err))
		die("%s", err.buf);

	ref_transaction_free(transaction);
	return 0;
}

static int replace_object(const char *object_ref, const char *replace_ref, int force)
{
	unsigned char object[20], repl[20];

	if (get_sha1(object_ref, object))
		die("Failed to resolve '%s' as a valid ref.", object_ref);
	if (get_sha1(replace_ref, repl))
		die("Failed to resolve '%s' as a valid ref.", replace_ref);

	return replace_object_sha1(object_ref, object, replace_ref, repl, force);
}

/*
 * Write the contents of the object named by "sha1" to the file "filename".
 * If "raw" is true, then the object's raw contents are printed according to
 * "type". Otherwise, we pretty-print the contents for human editing.
 */
static void export_object(const unsigned char *sha1, enum object_type type,
			  int raw, const char *filename)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
