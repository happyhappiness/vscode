{
		tmp = con;
		con = con->next;
		free(tmp);
	}