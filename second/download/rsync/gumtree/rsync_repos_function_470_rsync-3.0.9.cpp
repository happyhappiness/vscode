static void send_rsync_acl(int f, rsync_acl *racl, SMB_ACL_TYPE_T type,
			   item_list *racl_list)
{
	int ndx = find_matching_rsync_acl(racl, type, racl_list);

	/* Send 0 (-1 + 1) to indicate that literal ACL data follows. */
	write_varint(f, ndx + 1);

	if (ndx < 0) {
		rsync_acl *new_racl = EXPAND_ITEM_LIST(racl_list, rsync_acl, 1000);
		uchar flags = 0;

		if (racl->user_obj != NO_ENTRY)
			flags |= XMIT_USER_OBJ;
		if (racl->group_obj != NO_ENTRY)
			flags |= XMIT_GROUP_OBJ;
		if (racl->mask_obj != NO_ENTRY)
			flags |= XMIT_MASK_OBJ;
		if (racl->other_obj != NO_ENTRY)
			flags |= XMIT_OTHER_OBJ;
		if (racl->names.count)
			flags |= XMIT_NAME_LIST;

		write_byte(f, flags);

		if (flags & XMIT_USER_OBJ)
			write_varint(f, racl->user_obj);
		if (flags & XMIT_GROUP_OBJ)
			write_varint(f, racl->group_obj);
		if (flags & XMIT_MASK_OBJ)
			write_varint(f, racl->mask_obj);
		if (flags & XMIT_OTHER_OBJ)
			write_varint(f, racl->other_obj);
		if (flags & XMIT_NAME_LIST)
			send_ida_entries(f, &racl->names);

		/* Give the allocated data to the new list object. */
		*new_racl = *racl;
		*racl = empty_rsync_acl;
	}
}