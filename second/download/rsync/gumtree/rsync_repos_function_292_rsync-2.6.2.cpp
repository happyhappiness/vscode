void init_flist(void)
{
	struct file_struct f;

	/* Figure out how big the file_struct is without trailing padding */
	file_struct_len = offsetof(struct file_struct, flags) + sizeof f.flags;
}