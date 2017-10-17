     zConflict = Tcl_GetStringFromObj(objv[2], 0);
     zTable = Tcl_GetStringFromObj(objv[3], 0);
     zFile = Tcl_GetStringFromObj(objv[4], 0);
     nSep = strlen30(zSep);
     nNull = strlen30(zNull);
     if( nSep==0 ){
-      Tcl_AppendResult(interp,"Error: non-null separator required for copy",0);
+      Tcl_AppendResult(interp,"Error: non-null separator required for copy",
+                       (char*)0);
       return TCL_ERROR;
     }
     if(strcmp(zConflict, "rollback") != 0 &&
        strcmp(zConflict, "abort"   ) != 0 &&
        strcmp(zConflict, "fail"    ) != 0 &&
        strcmp(zConflict, "ignore"  ) != 0 &&
        strcmp(zConflict, "replace" ) != 0 ) {
-      Tcl_AppendResult(interp, "Error: \"", zConflict, 
+      Tcl_AppendResult(interp, "Error: \"", zConflict,
             "\", conflict-algorithm must be one of: rollback, "
-            "abort, fail, ignore, or replace", 0);
+            "abort, fail, ignore, or replace", (char*)0);
       return TCL_ERROR;
     }
     zSql = sqlite3_mprintf("SELECT * FROM '%q'", zTable);
     if( zSql==0 ){
-      Tcl_AppendResult(interp, "Error: no such table: ", zTable, 0);
+      Tcl_AppendResult(interp, "Error: no such table: ", zTable, (char*)0);
       return TCL_ERROR;
     }
     nByte = strlen30(zSql);
     rc = sqlite3_prepare(pDb->db, zSql, -1, &pStmt, 0);
     sqlite3_free(zSql);
     if( rc ){
-      Tcl_AppendResult(interp, "Error: ", sqlite3_errmsg(pDb->db), 0);
+      Tcl_AppendResult(interp, "Error: ", sqlite3_errmsg(pDb->db), (char*)0);
       nCol = 0;
     }else{
       nCol = sqlite3_column_count(pStmt);
     }
     sqlite3_finalize(pStmt);
     if( nCol==0 ) {
       return TCL_ERROR;
     }
     zSql = malloc( nByte + 50 + nCol*2 );
     if( zSql==0 ) {
-      Tcl_AppendResult(interp, "Error: can't malloc()", 0);
+      Tcl_AppendResult(interp, "Error: can't malloc()", (char*)0);
       return TCL_ERROR;
     }
     sqlite3_snprintf(nByte+50, zSql, "INSERT OR %q INTO '%q' VALUES(?",
          zConflict, zTable);
     j = strlen30(zSql);
     for(i=1; i<nCol; i++){
