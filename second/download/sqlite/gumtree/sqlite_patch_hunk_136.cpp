   char **azCol = 0;
   const char *zExpr;
   int nExpr;
   int nCol;
   int ii;
   Fts3Expr *pExpr;
+  char *zBuf = 0;
   sqlite3 *db = sqlite3_context_db_handle(context);
 
   if( argc<3 ){
     sqlite3_result_error(context, 
         "Usage: fts3_exprtest(tokenizer, expr, col1, ...", -1
     );
