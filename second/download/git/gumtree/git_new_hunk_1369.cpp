		CLEANUP_NONE,
		CLEANUP_SPACE,
		CLEANUP_ALL
	} cleanup_mode;
};

static void create_tag(const struct object_id *object, const char *tag,
		       struct strbuf *buf, struct create_tag_options *opt,
		       struct object_id *prev, struct object_id *result)
{
	enum object_type type;
	struct strbuf header = STRBUF_INIT;
	char *path = NULL;

	type = sha1_object_info(object->hash, NULL);
	if (type <= OBJ_NONE)
	    die(_("bad object type."));

	strbuf_addf(&header,
		    "object %s\n"
		    "type %s\n"
		    "tag %s\n"
		    "tagger %s\n\n",
		    oid_to_hex(object),
		    typename(type),
		    tag,
		    git_committer_info(IDENT_STRICT));

	if (!opt->message_given) {
		int fd;
