void dav_prop_exec(dav_prop_ctx *ctx)
{
    dav_propdb *propdb = ctx->propdb;
    dav_error *err = NULL;
    dav_elem_private *priv = ctx->prop->priv;

    ctx->rollback = apr_pcalloc(propdb->p, sizeof(*ctx->rollback));

    if (ctx->is_liveprop) {
	err = (*priv->provider->patch_exec)(propdb->resource,
					    ctx->prop, ctx->operation,
					    ctx->liveprop_ctx,
					    &ctx->rollback->liveprop);
    }
    else {
        dav_prop_name name;

        if (ctx->prop->ns == APR_XML_NS_NONE)
            name.ns = "";
        else
            name.ns = APR_XML_GET_URI_ITEM(propdb->ns_xlate, ctx->prop->ns);
        name.name = ctx->prop->name;

	/* save the old value so that we can do a rollback. */
	if ((err = (*propdb->db_hooks
                    ->get_rollback)(propdb->db, &name,
                                    &ctx->rollback->deadprop)) != NULL)
	    goto error;

	if (ctx->operation == DAV_PROP_OP_SET) {

	    /* Note: propdb->mapping was set in dav_prop_validate() */
            err = (*propdb->db_hooks->store)(propdb->db, &name, ctx->prop,
                                             propdb->mapping);

	    /*
	    ** If an error occurred, then assume that we didn't change the
	    ** value. Remove the rollback item so that we don't try to set
	    ** its value during the rollback.
	    */
            /* ### euh... where is the removal? */
	}
	else if (ctx->operation == DAV_PROP_OP_DELETE) {

	    /*
	    ** Delete the property. Ignore errors -- the property is there, or
	    ** we are deleting it for a second time.
	    */
	    /* ### but what about other errors? */
	    (void) (*propdb->db_hooks->remove)(propdb->db, &name);
	}
    }

  error:
    /* push a more specific error here */
    if (err != NULL) {
	/*
	** Use HTTP_INTERNAL_SERVER_ERROR because we shouldn't have seen
	** any errors at this point.
	*/
	ctx->err = dav_push_error(propdb->p, HTTP_INTERNAL_SERVER_ERROR,
				  DAV_ERR_PROP_EXEC,
				  "Could not execute PROPPATCH.", err);
    }
}