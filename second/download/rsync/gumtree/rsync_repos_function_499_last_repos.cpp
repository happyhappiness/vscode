static int recv_rsync_acl(int f, item_list *racl_list, SMB_ACL_TYPE_T type, mode_t mode)
{
	uchar computed_mask_bits = 0;
	acl_duo *duo_item;
	uchar flags;
	int ndx = read_varint(f);

	if (ndx < 0 || (size_t)ndx > racl_list->count) {
		rprintf(FERROR_XFER, "recv_acl_index: %s ACL index %d > %d\n",
			str_acl_type(type), ndx, (int)racl_list->count);
		exit_cleanup(RERR_STREAMIO);
	}

	if (ndx != 0)
		return ndx - 1;

	ndx = racl_list->count;
	duo_item = EXPAND_ITEM_LIST(racl_list, acl_duo, 1000);
	duo_item->racl = empty_rsync_acl;

	flags = read_byte(f);

	if (flags & XMIT_USER_OBJ)
		duo_item->racl.user_obj = recv_acl_access(f, NULL);
	if (flags & XMIT_GROUP_OBJ)
		duo_item->racl.group_obj = recv_acl_access(f, NULL);
	if (flags & XMIT_MASK_OBJ)
		duo_item->racl.mask_obj = recv_acl_access(f, NULL);
	if (flags & XMIT_OTHER_OBJ)
		duo_item->racl.other_obj = recv_acl_access(f, NULL);
	if (flags & XMIT_NAME_LIST)
		computed_mask_bits |= recv_ida_entries(f, &duo_item->racl.names);

#ifdef HAVE_OSX_ACLS
	/* If we received a superfluous mask, throw it away. */
	duo_item->racl.mask_obj = NO_ENTRY;
#else
	if (duo_item->racl.names.count && duo_item->racl.mask_obj == NO_ENTRY) {
		/* Mask must be non-empty with lists. */
		if (type == SMB_ACL_TYPE_ACCESS)
			computed_mask_bits = (mode >> 3) & 7;
		else
			computed_mask_bits |= duo_item->racl.group_obj & ~NO_ENTRY;
		duo_item->racl.mask_obj = computed_mask_bits;
	}
#endif

	duo_item->sacl = NULL;

	return ndx;
}