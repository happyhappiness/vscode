	} else {
		if (apply_verbosely)
			error(_("while searching for:\n%.*s"),
			      (int)(old - oldlines), oldlines);
	}

out:
	free(oldlines);
	strbuf_release(&newlines);
	free(preimage.line_allocated);
	free(postimage.line_allocated);

	return (applied_pos < 0);
