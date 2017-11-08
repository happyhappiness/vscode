static BOOL hpux_prohibited_duplicate_type(int acl_type)
{
	switch(acl_type) {
		case USER:
		case GROUP:
		case DEF_USER: 
		case DEF_GROUP:
			return True;
		default:
			return False;
	}
}