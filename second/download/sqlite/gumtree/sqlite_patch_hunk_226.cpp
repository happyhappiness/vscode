     }
     rc = Tcl_EvalObjEx(p->interp, pCmd, TCL_EVAL_DIRECT);
     Tcl_DecrRefCount(pCmd);
   }
 
   if( rc && rc!=TCL_RETURN ){
-    sqlite3_result_error(context, Tcl_GetStringResult(p->interp), -1); 
+    sqlite3_result_error(context, Tcl_GetStringResult(p->interp), -1);
   }else{
     Tcl_Obj *pVar = Tcl_GetObjResult(p->interp);
     int n;
     u8 *data;
-    char *zType = pVar->typePtr ? pVar->typePtr->name : "";
+    const char *zType = (pVar->typePtr ? pVar->typePtr->name : "");
     char c = zType[0];
     if( c=='b' && strcmp(zType,"bytearray")==0 && pVar->bytes==0 ){
       /* Only return a BLOB type if the Tcl variable is a bytearray and
       ** has no string representation. */
       data = Tcl_GetByteArrayFromObj(pVar, &n);
       sqlite3_result_blob(context, data, n, SQLITE_TRANSIENT);
