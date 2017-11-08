static BOOL hpux_acl_call_presence(void)
{

	shl_t handle = NULL;
	void *value;
	int ret_val=0;
	static BOOL already_checked=0;

	if(already_checked)
		return True;


	ret_val = shl_findsym(&handle, "acl", TYPE_PROCEDURE, &value);

	if(ret_val != 0) {
		DEBUG(5, ("hpux_acl_call_presence: shl_findsym() returned %d, errno = %d, error %s\n",
			ret_val, errno, strerror(errno)));
		DEBUG(5,("hpux_acl_call_presence: acl() system call is not present. Check if you have JFS 3.3 and above?\n"));
		return False;
	}

	DEBUG(10,("hpux_acl_call_presence: acl() system call is present. We have JFS 3.3 or above \n"));

	already_checked = True;
	return True;
}