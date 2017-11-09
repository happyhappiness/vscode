void receive_acl(int f, struct file_struct *file)
{
	F_ACL(file) = recv_rsync_acl(f, &access_acl_list, SMB_ACL_TYPE_ACCESS, file->mode);

	if (S_ISDIR(file->mode))
		F_DIR_DEFACL(file) = recv_rsync_acl(f, &default_acl_list, SMB_ACL_TYPE_DEFAULT, 0);
}