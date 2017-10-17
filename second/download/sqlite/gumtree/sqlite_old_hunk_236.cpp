**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This file contains code use to implement APIs that are part of the
** VDBE.
**
** $Id: vdbeapi.c,v 1.165 2009/06/06 14:13:27 danielk1977 Exp $
*/
#include "sqliteInt.h"
#include "vdbeInt.h"

#if 0 && defined(SQLITE_ENABLE_MEMORY_MANAGEMENT)
/*
** The following structure contains pointers to the end points of a
** doubly-linked list of all compiled SQL statements that may be holding
** buffers eligible for release when the sqlite3_release_memory() interface is
** invoked. Access to this list is protected by the SQLITE_MUTEX_STATIC_LRU2
** mutex.
**
** Statements are added to the end of this list when sqlite3_reset() is
** called. They are removed either when sqlite3_step() or sqlite3_finalize()
** is called. When statements are added to this list, the associated 
** register array (p->aMem[1..p->nMem]) may contain dynamic buffers that
** can be freed using sqlite3VdbeReleaseMemory().
**
** When statements are added or removed from this list, the mutex
** associated with the Vdbe being added or removed (Vdbe.db->mutex) is
** already held. The LRU2 mutex is then obtained, blocking if necessary,
** the linked-list pointers manipulated and the LRU2 mutex relinquished.
*/
struct StatementLruList {
  Vdbe *pFirst;
  Vdbe *pLast;
};
static struct StatementLruList sqlite3LruStatements;

/*
** Check that the list looks to be internally consistent. This is used
** as part of an assert() statement as follows:
**
**   assert( stmtLruCheck() );
*/
#ifndef NDEBUG
static int stmtLruCheck(){
  Vdbe *p;
  for(p=sqlite3LruStatements.pFirst; p; p=p->pLruNext){
    assert(p->pLruNext || p==sqlite3LruStatements.pLast);
    assert(!p->pLruNext || p->pLruNext->pLruPrev==p);
    assert(p->pLruPrev || p==sqlite3LruStatements.pFirst);
    assert(!p->pLruPrev || p->pLruPrev->pLruNext==p);
  }
  return 1;
}
#endif

/*
** Add vdbe p to the end of the statement lru list. It is assumed that
** p is not already part of the list when this is called. The lru list
** is protected by the SQLITE_MUTEX_STATIC_LRU mutex.
*/
static void stmtLruAdd(Vdbe *p){
  sqlite3_mutex_enter(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_LRU2));

  if( p->pLruPrev || p->pLruNext || sqlite3LruStatements.pFirst==p ){
    sqlite3_mutex_leave(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_LRU2));
    return;
  }

  assert( stmtLruCheck() );

  if( !sqlite3LruStatements.pFirst ){
    assert( !sqlite3LruStatements.pLast );
    sqlite3LruStatements.pFirst = p;
    sqlite3LruStatements.pLast = p;
  }else{
    assert( !sqlite3LruStatements.pLast->pLruNext );
    p->pLruPrev = sqlite3LruStatements.pLast;
    sqlite3LruStatements.pLast->pLruNext = p;
    sqlite3LruStatements.pLast = p;
  }

  assert( stmtLruCheck() );

  sqlite3_mutex_leave(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_LRU2));
}

/*
** Assuming the SQLITE_MUTEX_STATIC_LRU2 mutext is already held, remove
** statement p from the least-recently-used statement list. If the 
** statement is not currently part of the list, this call is a no-op.
*/
static void stmtLruRemoveNomutex(Vdbe *p){
  if( p->pLruPrev || p->pLruNext || p==sqlite3LruStatements.pFirst ){
    assert( stmtLruCheck() );
    if( p->pLruNext ){
      p->pLruNext->pLruPrev = p->pLruPrev;
    }else{
      sqlite3LruStatements.pLast = p->pLruPrev;
    }
    if( p->pLruPrev ){
      p->pLruPrev->pLruNext = p->pLruNext;
    }else{
      sqlite3LruStatements.pFirst = p->pLruNext;
    }
    p->pLruNext = 0;
    p->pLruPrev = 0;
    assert( stmtLruCheck() );
  }
}

/*
** Assuming the SQLITE_MUTEX_STATIC_LRU2 mutext is not held, remove
** statement p from the least-recently-used statement list. If the 
** statement is not currently part of the list, this call is a no-op.
*/
static void stmtLruRemove(Vdbe *p){
  sqlite3_mutex_enter(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_LRU2));
  stmtLruRemoveNomutex(p);
  sqlite3_mutex_leave(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_LRU2));
}

/*
** Try to release n bytes of memory by freeing buffers associated 
** with the memory registers of currently unused vdbes.
*/
int sqlite3VdbeReleaseMemory(int n){
  Vdbe *p;
  Vdbe *pNext;
  int nFree = 0;

  sqlite3_mutex_enter(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_LRU2));
  for(p=sqlite3LruStatements.pFirst; p && nFree<n; p=pNext){
    pNext = p->pLruNext;

    /* For each statement handle in the lru list, attempt to obtain the
    ** associated database mutex. If it cannot be obtained, continue
    ** to the next statement handle. It is not possible to block on
    ** the database mutex - that could cause deadlock.
    */
    if( SQLITE_OK==sqlite3_mutex_try(p->db->mutex) ){
      nFree += sqlite3VdbeReleaseBuffers(p);
      stmtLruRemoveNomutex(p);
      sqlite3_mutex_leave(p->db->mutex);
    }
  }
  sqlite3_mutex_leave(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_LRU2));

  return nFree;
}

/*
** Call sqlite3Reprepare() on the statement. Remove it from the
** lru list before doing so, as Reprepare() will free all the
** memory register buffers anyway.
*/
int vdbeReprepare(Vdbe *p){
  stmtLruRemove(p);
  return sqlite3Reprepare(p);
}

#else       /* !SQLITE_ENABLE_MEMORY_MANAGEMENT */
  #define stmtLruRemove(x)
  #define stmtLruAdd(x)
  #define vdbeReprepare(x) sqlite3Reprepare(x)
#endif


#ifndef SQLITE_OMIT_DEPRECATED
/*
** Return TRUE (non-zero) of the statement supplied as an argument needs
** to be recompiled.  A statement needs to be recompiled whenever the
** execution environment changes in a way that would alter the program
** that sqlite3_prepare() generates.  For example, if new functions or
** collating sequences are registered or if an authorizer function is
** added or changed.
*/
int sqlite3_expired(sqlite3_stmt *pStmt){
  Vdbe *p = (Vdbe*)pStmt;
  return p==0 || p->expired;
}
#endif

/*
** The following routine destroys a virtual machine that is created by
** the sqlite3_compile() routine. The integer returned is an SQLITE_
** success/failure code that describes the result of executing the virtual
