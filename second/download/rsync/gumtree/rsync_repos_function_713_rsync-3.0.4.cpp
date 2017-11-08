static void hpux_swap_acl_entries(struct acl *aclp0, struct acl *aclp1)
{
	struct acl temp_acl;

	temp_acl.a_type = aclp0->a_type;
	temp_acl.a_id = aclp0->a_id;
	temp_acl.a_perm = aclp0->a_perm;

	aclp0->a_type = aclp1->a_type;
	aclp0->a_id = aclp1->a_id;
	aclp0->a_perm = aclp1->a_perm;

	aclp1->a_type = temp_acl.a_type;
	aclp1->a_id = temp_acl.a_id;
	aclp1->a_perm = temp_acl.a_perm;
}