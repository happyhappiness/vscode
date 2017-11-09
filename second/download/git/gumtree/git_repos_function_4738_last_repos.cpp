static void add_non_note(struct notes_tree *t, char *path,
		unsigned int mode, const unsigned char *sha1)
{
	struct non_note *p = t->prev_non_note, *n;
	n = (struct non_note *) xmalloc(sizeof(struct non_note));
	n->next = NULL;
	n->path = path;
	n->mode = mode;
	hashcpy(n->oid.hash, sha1);
	t->prev_non_note = n;

	if (!t->first_non_note) {
		t->first_non_note = n;
		return;
	}

	if (non_note_cmp(p, n) < 0)
		; /* do nothing  */
	else if (non_note_cmp(t->first_non_note, n) <= 0)
		p = t->first_non_note;
	else {
		/* n sorts before t->first_non_note */
		n->next = t->first_non_note;
		t->first_non_note = n;
		return;
	}

	/* n sorts equal or after p */
	while (p->next && non_note_cmp(p->next, n) <= 0)
		p = p->next;

	if (non_note_cmp(p, n) == 0) { /* n ~= p; overwrite p with n */
		assert(strcmp(p->path, n->path) == 0);
		p->mode = n->mode;
		oidcpy(&p->oid, &n->oid);
		free(n);
		t->prev_non_note = p;
		return;
	}

	/* n sorts between p and p->next */
	n->next = p->next;
	p->next = n;
}