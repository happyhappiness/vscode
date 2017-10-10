			root->tree = t = grow_tree_content(t, t->entry_count);
		t->entries[t->entry_count++] = e;

		e->tree = NULL;
		c = get_mode(c, &e->versions[1].mode);
		if (!c)
			die("Corrupt mode in %s", oid_to_hex(oid));
		e->versions[0].mode = e->versions[1].mode;
		e->name = to_atom(c, strlen(c));
		c += e->name->str_len + 1;
		hashcpy(e->versions[0].oid.hash, (unsigned char *)c);
		hashcpy(e->versions[1].oid.hash, (unsigned char *)c);
		c += GIT_SHA1_RAWSZ;
	}
	free(buf);
}

static int tecmp0 (const void *_a, const void *_b)
{
