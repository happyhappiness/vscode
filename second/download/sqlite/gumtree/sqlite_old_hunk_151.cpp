    }
  }
  
  sqlite3_result_text(ctx, zText, -1, sqlite3_free);
}

static void rtreedepth(sqlite3_context *ctx, int nArg, sqlite3_value **apArg){
  if( sqlite3_value_type(apArg[0])!=SQLITE_BLOB 
   || sqlite3_value_bytes(apArg[0])<2
  ){
    sqlite3_result_error(ctx, "Invalid argument to rtreedepth()", -1); 
  }else{
    u8 *zBlob = (u8 *)sqlite3_value_blob(apArg[0]);
