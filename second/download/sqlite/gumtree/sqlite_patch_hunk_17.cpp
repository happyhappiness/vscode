     }
   }
   
   sqlite3_result_text(ctx, zText, -1, sqlite3_free);
 }
 
-/* This routine implements an SQL function that returns the "depth" parameter
-** from the front of a blob that is an r-tree node.  For example:
-**
-**     SELECT rtreedepth(data) FROM rt_node WHERE nodeno=1;
-**
-** The depth value is 0 for all nodes other than the root node, and the root
-** node always has nodeno=1, so the example above is the primary use for this
-** routine.  This routine is intended for testing and analysis only.
-*/
 static void rtreedepth(sqlite3_context *ctx, int nArg, sqlite3_value **apArg){
-  UNUSED_PARAMETER(nArg);
   if( sqlite3_value_type(apArg[0])!=SQLITE_BLOB 
    || sqlite3_value_bytes(apArg[0])<2
   ){
     sqlite3_result_error(ctx, "Invalid argument to rtreedepth()", -1); 
   }else{
     u8 *zBlob = (u8 *)sqlite3_value_blob(apArg[0]);
