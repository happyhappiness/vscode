int sys_acl_get_tag_type( SMB_ACL_ENTRY_T entry_d, SMB_ACL_TAG_T *tag_type_p)
{
	/* Initialize tag type */

	*tag_type_p = -1;
	DEBUG(10,("the tagtype is %d\n",entry_d->ace_id->id_type));

	/* Depending on what type of entry we have, *
	 * return tag type.                         */
	switch(entry_d->ace_id->id_type) {
	case ACEID_USER:
		*tag_type_p = SMB_ACL_USER;
		break;
	case ACEID_GROUP:
		*tag_type_p = SMB_ACL_GROUP;
		break;

	case SMB_ACL_USER_OBJ:
	case SMB_ACL_GROUP_OBJ:
	case SMB_ACL_OTHER:
		*tag_type_p = entry_d->ace_id->id_type;
		break;

	default:
		return(-1);
	}

	return(0);
}