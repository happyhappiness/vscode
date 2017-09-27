         case APL_REQ_FUNTYPE_INT:{
                 req_field_int_f func = (req_field_int_f)rft->fun;
                 int rs;
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01489)
                               "request_rec->dispatching %s -> int", name);
                 rs = (*func) (r);
-                lua_pushnumber(L, rs);
+                lua_pushinteger(L, rs);
                 return 1;
             }
         case APL_REQ_FUNTYPE_BOOLEAN:{
                 req_field_int_f func = (req_field_int_f)rft->fun;
                 int rs;
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01490)
