int xdi_diff_outf(mmfile_t *mf1, mmfile_t *mf2,
		  xdiff_emit_consume_fn fn, void *consume_callback_data,
		  xpparam_t const *xpp, xdemitconf_t const *xecfg)
{
	int ret;
	struct xdiff_emit_state state;
	xdemitcb_t ecb;

	memset(&state, 0, sizeof(state));
	state.consume = fn;
	state.consume_callback_data = consume_callback_data;
	memset(&ecb, 0, sizeof(ecb));
	ecb.outf = xdiff_outf;
	ecb.priv = &state;
	strbuf_init(&state.remainder, 0);
	ret = xdi_diff(mf1, mf2, xpp, xecfg, &ecb);
	strbuf_release(&state.remainder);
	return ret;
}