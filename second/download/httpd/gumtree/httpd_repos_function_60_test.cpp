static void handle_signed_tag(struct commit *parent, struct commit_extra_header ***tail)
{
	struct merge_remote_desc *desc;
	struct commit_extra_header *mergetag;
	char *buf;
	unsigned long size, len;
	enum object_type type;

	desc = merge_remote_util(parent);
	if (!desc || !desc->obj)
		return;
	buf = read_sha1_file(desc->obj->sha1, &type, &size);
	if (!buf || type != OBJ_TAG)
		goto free_return;
	len = parse_signature(buf, size);
	if (size == len)
		goto free_return;
	/*
	 * We could verify this signature and either omit the tag when
	 * it does not validate, but the integrator may not have the
	 * public key of the signer of the tag he is merging, while a
	 * later auditor may have it while auditing, so let's not run
	 * verify-signed-buffer here for now...
	 *
	 * if (verify_signed_buffer(buf, len, buf + len, size - len, ...))
	 *	warn("warning: signed tag unverified.");
	 */
	mergetag = xcalloc(1, sizeof(*mergetag));
	mergetag->key = xstrdup("mergetag");
	mergetag->value = buf;
	mergetag->len = size;

	**tail = mergetag;
	*tail = &mergetag->next;
	return;

free_return:
	free(buf);
}