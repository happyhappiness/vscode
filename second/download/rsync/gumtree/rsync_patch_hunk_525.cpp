 			io_printf(fd,"@ERROR: max connections (%d) reached - try again later\n", lp_max_connections());
 		}
 		return -1;
 	}
 
 	
-	user = auth_server(fd, i, addr, "@RSYNCD: AUTHREQD ");
+	auth_user = auth_server(fd, i, addr, "@RSYNCD: AUTHREQD ");
 
-	if (!user) {
+	if (!auth_user) {
 		rprintf(FERROR,"auth failed on module %s from %s (%s)\n",
 			name, client_name(fd), client_addr(fd));
 		io_printf(fd,"@ERROR: auth failed on module %s\n",name);
 		return -1;		
 	}
 
