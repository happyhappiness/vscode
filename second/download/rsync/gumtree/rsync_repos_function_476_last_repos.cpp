static const char *str_acl_type(SMB_ACL_TYPE_T type)
{
	switch (type) {
	case SMB_ACL_TYPE_ACCESS:
#ifdef HAVE_OSX_ACLS
		return "ACL_TYPE_EXTENDED";
#else
		return "ACL_TYPE_ACCESS";
#endif
	case SMB_ACL_TYPE_DEFAULT:
		return "ACL_TYPE_DEFAULT";
	default:
		break;
	}
	return "unknown ACL type!";
}