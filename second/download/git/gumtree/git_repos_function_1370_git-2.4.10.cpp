static int xdiff_outf(void *priv_, mmbuffer_t *mb, int nbuf)
{
	struct xdiff_emit_state *priv = priv_;
	int i;

	for (i = 0; i < nbuf; i++) {
		if (mb[i].ptr[mb[i].size-1] != '\n') {
			/* Incomplete line */
			strbuf_add(&priv->remainder, mb[i].ptr, mb[i].size);
			continue;
		}

		/* we have a complete line */
		if (!priv->remainder.len) {
			consume_one(priv, mb[i].ptr, mb[i].size);
			continue;
		}
		strbuf_add(&priv->remainder, mb[i].ptr, mb[i].size);
		consume_one(priv, priv->remainder.buf, priv->remainder.len);
		strbuf_reset(&priv->remainder);
	}
	if (priv->remainder.len) {
		consume_one(priv, priv->remainder.buf, priv->remainder.len);
		strbuf_reset(&priv->remainder);
	}
	return 0;
}