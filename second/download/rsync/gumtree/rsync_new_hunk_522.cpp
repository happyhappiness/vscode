		return -1;
	}

	return 0;
}


int set_perms(char *fname,struct file_struct *file,STRUCT_STAT *st,
	      int report)
{
	int updated = 0;
	STRUCT_STAT st2;
	extern int am_daemon;

	if (dry_run) return 0;
