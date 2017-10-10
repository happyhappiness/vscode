	for_each_replace_ref(show_reference, (void *)&data);

	return 0;
}

typedef int (*each_replace_name_fn)(const char *name, const char *ref,
				    const struct object_id *oid);

static int for_each_replace_name(const char **argv, each_replace_name_fn fn)
{
	const char **p, *full_hex;
	struct strbuf ref = STRBUF_INIT;
	size_t base_len;
	int had_error = 0;
	struct object_id oid;

	strbuf_addstr(&ref, git_replace_ref_base);
	base_len = ref.len;

	for (p = argv; *p; p++) {
		if (get_oid(*p, &oid)) {
			error("Failed to resolve '%s' as a valid ref.", *p);
			had_error = 1;
			continue;
		}

		strbuf_setlen(&ref, base_len);
		strbuf_addstr(&ref, oid_to_hex(&oid));
		full_hex = ref.buf + base_len;

		if (read_ref(ref.buf, oid.hash)) {
			error("replace ref '%s' not found.", full_hex);
			had_error = 1;
			continue;
		}
		if (fn(full_hex, ref.buf, &oid))
			had_error = 1;
	}
	strbuf_release(&ref);
	return had_error;
}

static int delete_replace_ref(const char *name, const char *ref,
			      const struct object_id *oid)
{
	if (delete_ref(NULL, ref, oid->hash, 0))
		return 1;
	printf("Deleted replace ref '%s'\n", name);
	return 0;
}

static void check_ref_valid(struct object_id *object,
			    struct object_id *prev,
			    struct strbuf *ref,
			    int force)
{
	strbuf_reset(ref);
	strbuf_addf(ref, "%s%s", git_replace_ref_base, oid_to_hex(object));
	if (check_refname_format(ref->buf, 0))
		die("'%s' is not a valid ref name.", ref->buf);

	if (read_ref(ref->buf, prev->hash))
		oidclr(prev);
	else if (!force)
		die("replace ref '%s' already exists", ref->buf);
}

static int replace_object_oid(const char *object_ref,
			       struct object_id *object,
			       const char *replace_ref,
			       struct object_id *repl,
			       int force)
{
	struct object_id prev;
	enum object_type obj_type, repl_type;
	struct strbuf ref = STRBUF_INIT;
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	obj_type = sha1_object_info(object->hash, NULL);
	repl_type = sha1_object_info(repl->hash, NULL);
	if (!force && obj_type != repl_type)
		die("Objects must be of the same type.\n"
		    "'%s' points to a replaced object of type '%s'\n"
		    "while '%s' points to a replacement object of type '%s'.",
		    object_ref, typename(obj_type),
		    replace_ref, typename(repl_type));

	check_ref_valid(object, &prev, &ref, force);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, ref.buf, repl->hash, prev.hash,
				   0, NULL, &err) ||
	    ref_transaction_commit(transaction, &err))
		die("%s", err.buf);

	ref_transaction_free(transaction);
	strbuf_release(&ref);
	return 0;
}

static int replace_object(const char *object_ref, const char *replace_ref, int force)
{
	struct object_id object, repl;

	if (get_oid(object_ref, &object))
		die("Failed to resolve '%s' as a valid ref.", object_ref);
	if (get_oid(replace_ref, &repl))
		die("Failed to resolve '%s' as a valid ref.", replace_ref);

	return replace_object_oid(object_ref, &object, replace_ref, &repl, force);
}

/*
 * Write the contents of the object named by "sha1" to the file "filename".
 * If "raw" is true, then the object's raw contents are printed according to
 * "type". Otherwise, we pretty-print the contents for human editing.
 */
static void export_object(const struct object_id *oid, enum object_type type,
			  int raw, const char *filename)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
