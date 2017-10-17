 **
 ** The error code stored in database p->db is overwritten with the return
 ** value in any case.
 */
 static int vdbeUnbind(Vdbe *p, int i){
   Mem *pVar;
-  if( p==0 ) return SQLITE_MISUSE;
+  if( vdbeSafetyNotNull(p) ){
+    return SQLITE_MISUSE_BKPT;
+  }
   sqlite3_mutex_enter(p->db->mutex);
   if( p->magic!=VDBE_MAGIC_RUN || p->pc>=0 ){
-    sqlite3Error(p->db, SQLITE_MISUSE, 0);
+    sqlite3Error(p->db, SQLITE_MISUSE);
     sqlite3_mutex_leave(p->db->mutex);
-    return SQLITE_MISUSE;
+    sqlite3_log(SQLITE_MISUSE, 
+        "bind on a busy prepared statement: [%s]", p->zSql);
+    return SQLITE_MISUSE_BKPT;
   }
   if( i<1 || i>p->nVar ){
-    sqlite3Error(p->db, SQLITE_RANGE, 0);
+    sqlite3Error(p->db, SQLITE_RANGE);
     sqlite3_mutex_leave(p->db->mutex);
     return SQLITE_RANGE;
   }
   i--;
   pVar = &p->aVar[i];
   sqlite3VdbeMemRelease(pVar);
   pVar->flags = MEM_Null;
-  sqlite3Error(p->db, SQLITE_OK, 0);
+  sqlite3Error(p->db, SQLITE_OK);
+
+  /* If the bit corresponding to this variable in Vdbe.expmask is set, then 
+  ** binding a new value to this variable invalidates the current query plan.
+  **
+  ** IMPLEMENTATION-OF: R-48440-37595 If the specific value bound to host
+  ** parameter in the WHERE clause might influence the choice of query plan
+  ** for a statement, then the statement will be automatically recompiled,
+  ** as if there had been a schema change, on the first sqlite3_step() call
+  ** following any change to the bindings of that parameter.
+  */
+  assert( (p->prepFlags & SQLITE_PREPARE_SAVESQL)!=0 || p->expmask==0 );
+  if( p->expmask!=0 && (p->expmask & (i>=31 ? 0x80000000 : (u32)1<<i))!=0 ){
+    p->expired = 1;
+  }
   return SQLITE_OK;
 }
 
 /*
 ** Bind a text or BLOB value.
 */
