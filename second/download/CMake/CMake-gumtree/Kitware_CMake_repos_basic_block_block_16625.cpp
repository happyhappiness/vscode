{
			keys &= ~F_UNAME;
			if ((oldkeys & F_UNAME) != 0)
				archive_strcat(&unsetstr, " uname");
		}