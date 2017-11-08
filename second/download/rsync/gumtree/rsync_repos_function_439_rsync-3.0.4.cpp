static BOOL rsync_acl_equal(const rsync_acl *racl1, const rsync_acl *racl2)
{
	return racl1->user_obj == racl2->user_obj
	    && racl1->group_obj == racl2->group_obj
	    && racl1->mask_obj == racl2->mask_obj
	    && racl1->other_obj == racl2->other_obj
	    && ida_entries_equal(&racl1->names, &racl2->names);
}