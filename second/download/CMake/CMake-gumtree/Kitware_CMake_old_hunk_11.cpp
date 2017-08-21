	if (a_eno)
		*a_eno = err;
	if (a_estr)
		archive_string_sprintf(a_estr, errstr, path);
}

/*
