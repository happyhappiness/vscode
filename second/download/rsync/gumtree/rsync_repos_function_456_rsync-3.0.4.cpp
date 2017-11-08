void receive_acl(struct file_struct *file, int f)
{
	F_ACL(file) = recv_rsync_acl(&access_acl_list, SMB_ACL_TYPE_ACCESS, f);

	if (S_ISDIR(file->mode))
		F_DIR_DEFACL(file) = recv_rsync_acl(&default_acl_list, SMB_ACL_TYPE_DEFAULT, f);
}