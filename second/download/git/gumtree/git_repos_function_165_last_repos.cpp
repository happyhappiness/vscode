static void upload_pack(void)
{
	struct string_list symref = STRING_LIST_INIT_DUP;

	head_ref_namespaced(find_symref, &symref);

	if (advertise_refs || !stateless_rpc) {
		reset_timeout();
		head_ref_namespaced(send_ref, &symref);
		for_each_namespaced_ref(send_ref, &symref);
		advertise_shallow_grafts(1);
		packet_flush(1);
	} else {
		head_ref_namespaced(check_ref, NULL);
		for_each_namespaced_ref(check_ref, NULL);
	}
	string_list_clear(&symref, 1);
	if (advertise_refs)
		return;

	receive_needs();
	if (want_obj.nr) {
		get_common_commits();
		create_pack_file();
	}
}