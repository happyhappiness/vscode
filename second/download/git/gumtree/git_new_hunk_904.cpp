		df_conflict = (ret == TRANSACTION_NAME_CONFLICT);
		goto fail;
	}

	ref_transaction_free(transaction);
	strbuf_release(&err);
	free(msg);
	return 0;
fail:
	ref_transaction_free(transaction);
	error("%s", err.buf);
	strbuf_release(&err);
	free(msg);
	return df_conflict ? STORE_REF_ERROR_DF_CONFLICT
			   : STORE_REF_ERROR_OTHER;
}

static int refcol_width = 10;
static int compact_format;
