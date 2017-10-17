     /* Fill the index with data and reparse the schema. Code an OP_Expire
     ** to invalidate all pre-compiled statements.
     */
     if( pTblName ){
       sqlite3RefillIndex(pParse, pIndex, iMem);
       sqlite3ChangeCookie(pParse, iDb);
-      sqlite3VdbeAddParseSchemaOp(v, iDb,
-         sqlite3MPrintf(db, "name='%q' AND type='index'", pIndex->zName));
-      sqlite3VdbeAddOp0(v, OP_Expire);
+      sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 0, 0,
+         sqlite3MPrintf(db, "name='%q'", pIndex->zName), P4_DYNAMIC);
+      sqlite3VdbeAddOp1(v, OP_Expire, 0);
     }
-
-    sqlite3VdbeJumpHere(v, pIndex->tnum);
   }
 
   /* When adding an index to the list of indices for a table, make
   ** sure all indices labeled OE_Replace come after all those labeled
   ** OE_Ignore.  This is necessary for the correct constraint check
   ** processing (in sqlite3GenerateConstraintChecks()) as part of
