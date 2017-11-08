void dav_prop_validate(dav_prop_ctx *ctx)
{
    dav_propdb *propdb = ctx->propdb;
    apr_xml_elem *prop = ctx->prop;
    dav_elem_private *priv;

    priv = ctx->prop->priv = apr_pcalloc(propdb->p, sizeof(*priv));

    /*
    ** Check to see if this is a live property, and fill the fields
    ** in the XML elem, as appropriate.
    **
    ** Verify that the property is read/write. If not, then it cannot
    ** be SET or DELETEd.
    */
    if (priv->propid == 0) {
        dav_find_liveprop(propdb, prop);

        /* it's a liveprop if a provider was found */
        /* ### actually the "core" props should really be liveprops, but
           ### there is no "provider" for those and the r/w props are
           ### treated as dead props anyhow */
        ctx->is_liveprop = priv->provider != NULL;
    }

    if (!dav_rw_liveprop(propdb, priv)) {
        ctx->err = dav_new_error(propdb->p, HTTP_CONFLICT,
                                 DAV_ERR_PROP_READONLY,
                                 "Property is read-only.");
        return;
    }

    if (ctx->is_liveprop) {
        int defer_to_dead = 0;

        ctx->err = (*priv->provider->patch_validate)(propdb->resource,
                                                     prop, ctx->operation,
                                                     &ctx->liveprop_ctx,
                                                     &defer_to_dead);
        if (ctx->err != NULL || !defer_to_dead)
            return;

        /* clear is_liveprop -- act as a dead prop now */
        ctx->is_liveprop = 0;
    }

    /*
    ** The property is supposed to be stored into the dead-property
    ** database. Make sure the thing is truly open (and writable).
    */
    if (propdb->deferred
        && (ctx->err = dav_really_open_db(propdb, 0 /* ro */)) != NULL) {
        return;
    }

    /*
    ** There should be an open, writable database in here!
    **
    ** Note: the database would be NULL if it was opened readonly and it
    **       did not exist.
    */
    if (propdb->db == NULL) {
        ctx->err = dav_new_error(propdb->p, HTTP_INTERNAL_SERVER_ERROR,
                                 DAV_ERR_PROP_NO_DATABASE,
                                 "Attempted to set/remove a property "
                                 "without a valid, open, read/write "
                                 "property database.");
        return;
    }

    if (ctx->operation == DAV_PROP_OP_SET) {
        /*
        ** Prep the element => propdb namespace index mapping, inserting
        ** namespace URIs into the propdb that don't exist.
        */
        (void) (*propdb->db_hooks->map_namespaces)(propdb->db,
                                                   propdb->ns_xlate,
                                                   &propdb->mapping);
    }
    else if (ctx->operation == DAV_PROP_OP_DELETE) {
        /*
        ** There are no checks to perform here. If a property exists, then
        ** we will delete it. If it does not exist, then it does not matter
        ** (see S12.13.1).
        **
        ** Note that if a property does not exist, that does not rule out
        ** that a SET will occur during this PROPPATCH (thusly creating it).
        */
    }
}