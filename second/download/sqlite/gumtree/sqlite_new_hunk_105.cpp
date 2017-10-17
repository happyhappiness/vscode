**
** The error code stored in database p->db is overwritten with the return
** value in any case.
*/
static int vdbeUnbind(Vdbe *p, int i){
  Mem *pVar;
  if( p==0 ) return SQLITE_MISUSE;
  sqlite3_mutex_enter(p->db->mutex);
  if( p->magic!=VDBE_MAGIC_RUN || p->pc>=0 ){
    sqlite3Error(p->db, SQLITE_MISUSE, 0);
    sqlite3_mutex_leave(p->db->mutex);
    return SQLITE_MISUSE;
  }
  if( i<1 || i>p->nVar ){
    sqlite3Error(p->db, SQLITE_RANGE, 0);
    sqlite3_mutex_leave(p->db->mutex);
    return SQLITE_RANGE;
  }
  i--;
  pVar = &p->aVar[i];
  sqlite3VdbeMemRelease(pVar);
  pVar->flags = MEM_Null;
  sqlite3Error(p->db, SQLITE_OK, 0);
  return SQLITE_OK;
}

/*
** Bind a text or BLOB value.
*/
