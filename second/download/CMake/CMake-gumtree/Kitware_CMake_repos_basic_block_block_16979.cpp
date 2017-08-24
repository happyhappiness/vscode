(gname_length > 31 || has_non_ASCII(gname)) {
			add_pax_attr(&(pax->pax_header), "gname", gname);
			need_extension = 1;
		}