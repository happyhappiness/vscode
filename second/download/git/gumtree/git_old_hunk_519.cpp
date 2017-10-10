		if (!skip || !string_list_has_string(skip, extra_refname))
			return extra_refname;
	}
	return NULL;
}

int rename_ref_available(const char *oldname, const char *newname)
{
	struct string_list skip = STRING_LIST_INIT_NODUP;
	struct strbuf err = STRBUF_INIT;
	int ret;

	string_list_insert(&skip, oldname);
	ret = !verify_refname_available(newname, NULL, &skip, &err);
	if (!ret)
		error("%s", err.buf);

	string_list_clear(&skip, 0);
	strbuf_release(&err);
	return ret;
}

int head_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	struct object_id oid;
	int flag;
