{
	int i;
	const char *subpos = NULL, *bodypos = NULL, *sigpos = NULL;
	unsigned long sublen = 0, bodylen = 0, nonsiglen = 0, siglen = 0;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i];
		struct atom_value *v = &val[i];
		const char *valp = NULL;
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (strcmp(name, "subject") &&
		    strcmp(name, "body") &&
		    strcmp(name, "contents") &&
		    strcmp(name, "contents:subject") &&
		    strcmp(name, "contents:body") &&
		    strcmp(name, "contents:signature") &&
		    !starts_with(name, "contents:lines="))
			continue;
		if (!subpos)
			find_subpos(buf, sz,
				    &subpos, &sublen,
				    &bodypos, &bodylen, &nonsiglen,
				    &sigpos, &siglen);

		if (!strcmp(name, "subject"))
			v->s = copy_subject(subpos, sublen);
		else if (!strcmp(name, "contents:subject"))
			v->s = copy_subject(subpos, sublen);
		else if (!strcmp(name, "body"))
			v->s = xmemdupz(bodypos, bodylen);
		else if (!strcmp(name, "contents:body"))
			v->s = xmemdupz(bodypos, nonsiglen);
		else if (!strcmp(name, "contents:signature"))
			v->s = xmemdupz(sigpos, siglen);
		else if (!strcmp(name, "contents"))
			v->s = xstrdup(subpos);
		else if (skip_prefix(name, "contents:lines=", &valp)) {
			struct strbuf s = STRBUF_INIT;
			const char *contents_end = bodylen + bodypos - siglen;

			if (strtoul_ui(valp, 10, &v->u.contents.lines))
				die(_("positive value expected contents:lines=%s"), valp);
			/*  Size is the length of the message after removing the signature */
			append_lines(&s, subpos, contents_end - subpos, v->u.contents.lines);
			v->s = strbuf_detach(&s, NULL);
		}
	}
}

/*
 * We want to have empty print-string for field requests
 * that do not apply (e.g. "authordate" for a tag object)
