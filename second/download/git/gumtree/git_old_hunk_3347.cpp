				continue;
		}

		strbuf_add(base, entry.path, te_len);

		if (S_ISREG(entry.mode)) {
			hit |= grep_sha1(opt, entry.sha1, base->buf, tn_len,
					 check_attr ? base->buf + tn_len : NULL);
		}
		else if (S_ISDIR(entry.mode)) {
			enum object_type type;
			struct tree_desc sub;
			void *data;
			unsigned long size;

			data = lock_and_read_sha1_file(entry.sha1, &type, &size);
			if (!data)
				die(_("unable to read tree (%s)"),
				    sha1_to_hex(entry.sha1));

			strbuf_addch(base, '/');
			init_tree_desc(&sub, data, size);
			hit |= grep_tree(opt, pathspec, &sub, base, tn_len,
					 check_attr);
			free(data);
