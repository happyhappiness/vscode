void dav_prop_commit(dav_prop_ctx *ctx)
{
    dav_elem_private *priv = ctx->prop->priv;

    /*
    ** Note that a commit implies ctx->err is NULL. The caller should assume
    ** a status of HTTP_OK for this case.
    */

    if (ctx->is_liveprop) {
        (*priv->provider->patch_commit)(ctx->propdb->resource,
                                        ctx->operation,
                                        ctx->liveprop_ctx,
                                        ctx->rollback->liveprop);
    }
}