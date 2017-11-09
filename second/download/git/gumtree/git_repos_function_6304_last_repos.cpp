static int pack_options_allow_reuse(void)
{
	return pack_to_stdout &&
	       allow_ofs_delta &&
	       !ignore_packed_keep &&
	       (!local || !have_non_local_packs) &&
	       !incremental;
}