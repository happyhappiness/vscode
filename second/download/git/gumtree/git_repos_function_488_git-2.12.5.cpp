static void grab_sub_body_contents(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	int i;
	const char *subpos = NULL, *bodypos = NULL, *sigpos = NULL;
	unsigned long sublen = 0, bodylen = 0, nonsiglen = 0, siglen = 0;

	for (i = 0; i < used_atom_cnt; i++) {
		struct used_atom *atom = &used_atom[i];
		const char *name = atom->name;
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (strcmp(name, "subject") &&
		    strcmp(name, "body") &&
		    strcmp(name, "trailers") &&
		    !starts_with(name, "contents"))
			continue;
		if (!subpos)
			find_subpos(buf, sz,
				    &subpos, &sublen,
				    &bodypos, &bodylen, &nonsiglen,
				    &sigpos, &siglen);

		if (atom->u.contents.option == C_SUB)
			v->s = copy_subject(subpos, sublen);
		else if (atom->u.contents.option == C_BODY_DEP)
			v->s = xmemdupz(bodypos, bodylen);
		else if (atom->u.contents.option == C_BODY)
			v->s = xmemdupz(bodypos, nonsiglen);
		else if (atom->u.contents.option == C_SIG)
			v->s = xmemdupz(sigpos, siglen);
		else if (atom->u.contents.option == C_LINES) {
			struct strbuf s = STRBUF_INIT;
			const char *contents_end = bodylen + bodypos - siglen;

			/*  Size is the length of the message after removing the signature */
			append_lines(&s, subpos, contents_end - subpos, atom->u.contents.nlines);
			v->s = strbuf_detach(&s, NULL);
		} else if (atom->u.contents.option == C_TRAILERS) {
			struct trailer_info info;

			/* Search for trailer info */
			trailer_info_get(&info, subpos);
			v->s = xmemdupz(info.trailer_start,
					info.trailer_end - info.trailer_start);
			trailer_info_release(&info);
		} else if (atom->u.contents.option == C_BARE)
			v->s = xstrdup(subpos);
	}
}