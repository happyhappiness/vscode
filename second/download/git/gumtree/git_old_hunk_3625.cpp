	error("%s", err.buf);
	strbuf_release(&err);
	return df_conflict ? STORE_REF_ERROR_DF_CONFLICT
			   : STORE_REF_ERROR_OTHER;
}

#define REFCOL_WIDTH  10

static int update_local_ref(struct ref *ref,
			    const char *remote,
			    const struct ref *remote_ref,
			    struct strbuf *display)
{
