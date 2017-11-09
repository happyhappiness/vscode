static void hpux_count_obj(int acl_count, struct acl *aclp, struct hpux_acl_types *acl_type_count)
{
	int i;

	memset(acl_type_count, 0, sizeof(struct hpux_acl_types));

	for(i=0;i<acl_count;i++) {
		switch(aclp[i].a_type) {
		case USER: 
			acl_type_count->n_user++;
			break;
		case USER_OBJ: 
			acl_type_count->n_user_obj++;
			break;
		case DEF_USER_OBJ: 
			acl_type_count->n_def_user_obj++;
			break;
		case GROUP: 
			acl_type_count->n_group++;
			break;
		case GROUP_OBJ: 
			acl_type_count->n_group_obj++;
			break;
		case DEF_GROUP_OBJ: 
			acl_type_count->n_def_group_obj++;
			break;
		case OTHER_OBJ: 
			acl_type_count->n_other_obj++;
			break;
		case DEF_OTHER_OBJ: 
			acl_type_count->n_def_other_obj++;
			break;
		case CLASS_OBJ:
			acl_type_count->n_class_obj++;
			break;
		case DEF_CLASS_OBJ:
			acl_type_count->n_def_class_obj++;
			break;
		case DEF_USER:
			acl_type_count->n_def_user++;
			break;
		case DEF_GROUP:
			acl_type_count->n_def_group++;
			break;
		default: 
			acl_type_count->n_illegal_obj++;
			break;
		}
	}
}