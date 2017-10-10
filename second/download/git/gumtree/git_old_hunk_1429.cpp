			root->tree = t = grow_tree_content(t, t->entry_count);
		t->entries[t->entry_count++] = e;

		e->tree = NULL;
		c = get_mode(c, &e->versions[1].mode);
		if (!c)
			die("Corrupt mode in %s", sha1_to_hex(sha1));
		e->versions[0].mode = e->versions[1].mode;
		e->name = to_atom(c, strlen(c));
		c += e->name->str_len + 1;
		hashcpy(e->versions[0].sha1, (unsigned char *)c);
		hashcpy(e->versions[1].sha1, (unsigned char *)c);
		c += 20;
	}
	free(buf);
}

static int tecmp0 (const void *_a, const void *_b)
{
