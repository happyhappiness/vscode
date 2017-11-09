static int hpux_get_needed_class_perm(struct acl *aclp)
{
	switch(aclp->a_type) {
		case USER: 
		case GROUP_OBJ: 
		case GROUP: 
		case DEF_USER_OBJ: 
		case DEF_USER:
		case DEF_GROUP_OBJ: 
		case DEF_GROUP:
		case DEF_CLASS_OBJ:
		case DEF_OTHER_OBJ: 
			return aclp->a_perm;
		default: 
			return 0;
	}
}