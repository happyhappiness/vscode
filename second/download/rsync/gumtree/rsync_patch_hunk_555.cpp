 		io_printf(fd,"@ERROR: auth failed on module %s\n",name);
 		return -1;		
 	}
 
 	module_id = i;
 
-	if (lp_read_only(i))
-		read_only = 1;
-
 	am_root = (getuid() == 0);
 
 	if (am_root) {
 		p = lp_uid(i);
 		if (!name_to_uid(p, &uid)) {
 			if (!isdigit(*p)) {
