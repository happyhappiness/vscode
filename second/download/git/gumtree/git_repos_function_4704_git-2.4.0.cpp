static void write_head_info(void)
{
	struct sha1_array sa = SHA1_ARRAY_INIT;
	for_each_alternate_ref(collect_one_alternate_ref, &sa);
	sha1_array_for_each_unique(&sa, show_one_alternate_sha1, NULL);
	sha1_array_clear(&sa);
	for_each_ref(show_ref_cb, NULL);
	if (!sent_capabilities)
		show_ref("capabilities^{}", null_sha1);

	advertise_shallow_grafts(1);

	/* EOF */
	packet_flush(1);
}