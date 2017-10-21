 			io_printf(f_out, "@ERROR: max connections (%d) reached -- try again later\n",
 				lp_max_connections(i));
 		}
 		return -1;
 	}
 
-	auth_user = auth_server(f_in, f_out, i, addr, "@RSYNCD: AUTHREQD ");
+	auth_user = auth_server(f_in, f_out, i, host, addr, "@RSYNCD: AUTHREQD ");
 
 	if (!auth_user) {
-		rprintf(FLOG, "auth failed on module %s from %s (%s)\n",
-			name, host, addr);
 		io_printf(f_out, "@ERROR: auth failed on module %s\n", name);
 		return -1;
 	}
 
 	module_id = i;
 
