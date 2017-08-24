(uname_length > 31 || has_non_ASCII(uname)) {
			add_pax_attr(&(pax->pax_header), "uname", uname);
			need_extension = 1;
		}