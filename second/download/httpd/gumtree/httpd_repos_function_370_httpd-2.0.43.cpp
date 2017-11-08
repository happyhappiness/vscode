void dav_prop_rollback(dav_prop_ctx *ctx)
{
    dav_error *err = NULL;
    dav_elem_private *priv = ctx->prop->priv;

    /* do nothing if there is no rollback information. */
    if (ctx->rollback == NULL)
	return;

    /*
    ** ### if we have an error, and a rollback occurs, then the namespace
    ** ### mods should not happen at all. Basically, the namespace management
    ** ### is simply a bitch.
    */

    if (ctx->is_liveprop) {
	err = (*priv->provider->patch_rollback)(ctx->propdb->resource,
						ctx->operation,
						ctx->liveprop_ctx,
						ctx->rollback->liveprop);
    }
    else {
        err = (*ctx->propdb->db_hooks
               ->apply_rollback)(ctx->propdb->db, ctx->rollback->deadprop);
    }

    if (err != NULL) {
	if (ctx->err == NULL)
	    ctx->err = err;
	else {
	    dav_error *scan = err;

	    /* hook previous errors at the end of the rollback error */
	    while (scan->prev != NULL)
		scan = scan->prev;
	    scan->prev = ctx->err;
	    ctx->err = err;
	}
    }
}