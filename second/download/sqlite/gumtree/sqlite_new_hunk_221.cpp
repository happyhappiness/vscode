  TriggerStep *step_list; /* Link list of trigger program steps             */
  Trigger *pNext;         /* Next trigger associated with the table */
};

/*
** A trigger is either a BEFORE or an AFTER trigger.  The following constants
** determine which.
**
** If there are multiple triggers, you might of some BEFORE and some AFTER.
** In that cases, the constants below can be ORed together.
*/
#define TRIGGER_BEFORE  1
#define TRIGGER_AFTER   2

/*
 * An instance of struct TriggerStep is used to store a single SQL statement
 * that is a part of a trigger-program.
 *
 * Instances of struct TriggerStep are stored in a singly linked list (linked
 * using the "pNext" member) referenced by the "step_list" member of the
 * associated struct Trigger instance. The first element of the linked list is
 * the first step of the trigger-program.
 *
 * The "op" member indicates whether this is a "DELETE", "INSERT", "UPDATE" or
 * "SELECT" statement. The meanings of the other members is determined by the
 * value of "op" as follows:
 *
 * (op == TK_INSERT)
 * orconf    -> stores the ON CONFLICT algorithm
 * pSelect   -> If this is an INSERT INTO ... SELECT ... statement, then
 *              this stores a pointer to the SELECT statement. Otherwise NULL.
 * zTarget   -> Dequoted name of the table to insert into.
 * pExprList -> If this is an INSERT INTO ... VALUES ... statement, then
 *              this stores values to be inserted. Otherwise NULL.
 * pIdList   -> If this is an INSERT INTO ... (<column-names>) VALUES ...
 *              statement, then this stores the column-names to be
 *              inserted into.
 *
 * (op == TK_DELETE)
 * zTarget   -> Dequoted name of the table to delete from.
 * pWhere    -> The WHERE clause of the DELETE statement if one is specified.
 *              Otherwise NULL.
 *
 * (op == TK_UPDATE)
 * zTarget   -> Dequoted name of the table to update.
 * pWhere    -> The WHERE clause of the UPDATE statement if one is specified.
 *              Otherwise NULL.
 * pExprList -> A list of the columns to update and the expressions to update
 *              them to. See sqlite3Update() documentation of "pChanges"
 *              argument.
 *
 */
struct TriggerStep {
  u8 op;               /* One of TK_DELETE, TK_UPDATE, TK_INSERT, TK_SELECT */
  u8 orconf;           /* OE_Rollback etc. */
  Trigger *pTrig;      /* The trigger that this step is a part of */
  Select *pSelect;     /* SELECT statement or RHS of INSERT INTO SELECT ... */
  char *zTarget;       /* Target table for DELETE, UPDATE, INSERT */
  Expr *pWhere;        /* The WHERE clause for DELETE or UPDATE steps */
  ExprList *pExprList; /* SET clause for UPDATE. */
  IdList *pIdList;     /* Column names for INSERT */
  TriggerStep *pNext;  /* Next in the link-list */
  TriggerStep *pLast;  /* Last element in link-list. Valid for 1st elem only */
};

/*
** The following structure contains information used by the sqliteFix...
** routines as they walk the parse tree to make database references
** explicit.
*/
typedef struct DbFixer DbFixer;
struct DbFixer {
  Parse *pParse;      /* The parsing context.  Error messages written here */
  Schema *pSchema;    /* Fix items to this schema */
  int bVarOnly;       /* Check for variable references only */
  const char *zDb;    /* Make sure all objects are contained in this database */
  const char *zType;  /* Type of the container - used for error messages */
  const Token *pName; /* Name of the container - used for error messages */
};

/*
** An objected used to accumulate the text of a string where we
** do not necessarily know how big the string will be in the end.
*/
struct StrAccum {
  sqlite3 *db;         /* Optional database for lookaside.  Can be NULL */
  char *zText;         /* The string collected so far */
  u32  nAlloc;         /* Amount of space allocated in zText */
  u32  mxAlloc;        /* Maximum allowed allocation.  0 for no malloc usage */
  u32  nChar;          /* Length of the string so far */
  u8   accError;       /* STRACCUM_NOMEM or STRACCUM_TOOBIG */
  u8   printfFlags;    /* SQLITE_PRINTF flags below */
};
#define STRACCUM_NOMEM   1
#define STRACCUM_TOOBIG  2
#define SQLITE_PRINTF_INTERNAL 0x01  /* Internal-use-only converters allowed */
#define SQLITE_PRINTF_SQLFUNC  0x02  /* SQL function arguments to VXPrintf */
#define SQLITE_PRINTF_MALLOCED 0x04  /* True if xText is allocated space */

#define isMalloced(X)  (((X)->printfFlags & SQLITE_PRINTF_MALLOCED)!=0)


/*
** A pointer to this structure is used to communicate information
** from sqlite3Init and OP_ParseSchema into the sqlite3InitCallback.
*/
typedef struct {
  sqlite3 *db;        /* The database being initialized */
  char **pzErrMsg;    /* Error message stored here */
  int iDb;            /* 0 for main database.  1 for TEMP, 2.. for ATTACHed */
  int rc;             /* Result code stored here */
} InitData;

/*
** Structure containing global configuration data for the SQLite library.
**
** This structure also contains some state information.
*/
struct Sqlite3Config {
  int bMemstat;                     /* True to enable memory status */
  int bCoreMutex;                   /* True to enable core mutexing */
  int bFullMutex;                   /* True to enable full mutexing */
  int bOpenUri;                     /* True to interpret filenames as URIs */
  int bUseCis;                      /* Use covering indices for full-scans */
  int bSmallMalloc;                 /* Avoid large memory allocations if true */
  int mxStrlen;                     /* Maximum string length */
  int neverCorrupt;                 /* Database is always well-formed */
  int szLookaside;                  /* Default lookaside buffer size */
  int nLookaside;                   /* Default lookaside buffer count */
  int nStmtSpill;                   /* Stmt-journal spill-to-disk threshold */
  sqlite3_mem_methods m;            /* Low-level memory allocation interface */
  sqlite3_mutex_methods mutex;      /* Low-level mutex interface */
  sqlite3_pcache_methods2 pcache2;  /* Low-level page-cache interface */
  void *pHeap;                      /* Heap storage space */
  int nHeap;                        /* Size of pHeap[] */
  int mnReq, mxReq;                 /* Min and max heap requests sizes */
  sqlite3_int64 szMmap;             /* mmap() space per open file */
  sqlite3_int64 mxMmap;             /* Maximum value for szMmap */
  void *pPage;                      /* Page cache memory */
  int szPage;                       /* Size of each page in pPage[] */
  int nPage;                        /* Number of pages in pPage[] */
  int mxParserStack;                /* maximum depth of the parser stack */
  int sharedCacheEnabled;           /* true if shared-cache mode enabled */
  u32 szPma;                        /* Maximum Sorter PMA size */
  /* The above might be initialized to non-zero.  The following need to always
  ** initially be zero, however. */
  int isInit;                       /* True after initialization has finished */
  int inProgress;                   /* True while initialization in progress */
  int isMutexInit;                  /* True after mutexes are initialized */
  int isMallocInit;                 /* True after malloc is initialized */
  int isPCacheInit;                 /* True after malloc is initialized */
  int nRefInitMutex;                /* Number of users of pInitMutex */
  sqlite3_mutex *pInitMutex;        /* Mutex used by sqlite3_initialize() */
  void (*xLog)(void*,int,const char*); /* Function for logging */
  void *pLogArg;                       /* First argument to xLog() */
#ifdef SQLITE_ENABLE_SQLLOG
  void(*xSqllog)(void*,sqlite3*,const char*, int);
  void *pSqllogArg;
#endif
#ifdef SQLITE_VDBE_COVERAGE
  /* The following callback (if not NULL) is invoked on every VDBE branch
  ** operation.  Set the callback using SQLITE_TESTCTRL_VDBE_COVERAGE.
  */
  void (*xVdbeBranch)(void*,int iSrcLine,u8 eThis,u8 eMx);  /* Callback */
  void *pVdbeBranchArg;                                     /* 1st argument */
#endif
#ifndef SQLITE_UNTESTABLE
  int (*xTestCallback)(int);        /* Invoked by sqlite3FaultSim() */
#endif
  int bLocaltimeFault;              /* True to fail localtime() calls */
  int iOnceResetThreshold;          /* When to reset OP_Once counters */
};

/*
** This macro is used inside of assert() statements to indicate that
** the assert is only valid on a well-formed database.  Instead of:
**
**     assert( X );
**
** One writes:
**
**     assert( X || CORRUPT_DB );
**
** CORRUPT_DB is true during normal operation.  CORRUPT_DB does not indicate
** that the database is definitely corrupt, only that it might be corrupt.
** For most test cases, CORRUPT_DB is set to false using a special
** sqlite3_test_control().  This enables assert() statements to prove
** things that are always true for well-formed databases.
*/
#define CORRUPT_DB  (sqlite3Config.neverCorrupt==0)

/*
** Context pointer passed down through the tree-walk.
*/
struct Walker {
  Parse *pParse;                            /* Parser context.  */
  int (*xExprCallback)(Walker*, Expr*);     /* Callback for expressions */
  int (*xSelectCallback)(Walker*,Select*);  /* Callback for SELECTs */
  void (*xSelectCallback2)(Walker*,Select*);/* Second callback for SELECTs */
  int walkerDepth;                          /* Number of subqueries */
  u8 eCode;                                 /* A small processing code */
  union {                                   /* Extra data for callback */
    NameContext *pNC;                         /* Naming context */
    int n;                                    /* A counter */
    int iCur;                                 /* A cursor number */
    SrcList *pSrcList;                        /* FROM clause */
    struct SrcCount *pSrcCount;               /* Counting column references */
    struct CCurHint *pCCurHint;               /* Used by codeCursorHint() */
    int *aiCol;                               /* array of column indexes */
    struct IdxCover *pIdxCover;               /* Check for index coverage */
    struct IdxExprTrans *pIdxTrans;           /* Convert indexed expr to column */
    ExprList *pGroupBy;                       /* GROUP BY clause */
    struct HavingToWhereCtx *pHavingCtx;      /* HAVING to WHERE clause ctx */
  } u;
};

/* Forward declarations */
int sqlite3WalkExpr(Walker*, Expr*);
int sqlite3WalkExprList(Walker*, ExprList*);
int sqlite3WalkSelect(Walker*, Select*);
int sqlite3WalkSelectExpr(Walker*, Select*);
int sqlite3WalkSelectFrom(Walker*, Select*);
int sqlite3ExprWalkNoop(Walker*, Expr*);
int sqlite3SelectWalkNoop(Walker*, Select*);
int sqlite3SelectWalkFail(Walker*, Select*);
#ifdef SQLITE_DEBUG
void sqlite3SelectWalkAssert2(Walker*, Select*);
#endif

/*
** Return code from the parse-tree walking primitives and their
** callbacks.
*/
#define WRC_Continue    0   /* Continue down into children */
#define WRC_Prune       1   /* Omit children but continue walking siblings */
#define WRC_Abort       2   /* Abandon the tree walk */

/*
** An instance of this structure represents a set of one or more CTEs
** (common table expressions) created by a single WITH clause.
*/
struct With {
  int nCte;                       /* Number of CTEs in the WITH clause */
  With *pOuter;                   /* Containing WITH clause, or NULL */
  struct Cte {                    /* For each CTE in the WITH clause.... */
    char *zName;                    /* Name of this CTE */
    ExprList *pCols;                /* List of explicit column names, or NULL */
    Select *pSelect;                /* The definition of this CTE */
    const char *zCteErr;            /* Error message for circular references */
  } a[1];
};

#ifdef SQLITE_DEBUG
/*
** An instance of the TreeView object is used for printing the content of
** data structures on sqlite3DebugPrintf() using a tree-like view.
*/
struct TreeView {
  int iLevel;             /* Which level of the tree we are on */
  u8  bLine[100];         /* Draw vertical in column i if bLine[i] is true */
};
#endif /* SQLITE_DEBUG */

/*
** Assuming zIn points to the first byte of a UTF-8 character,
** advance zIn to point to the first byte of the next UTF-8 character.
*/
#define SQLITE_SKIP_UTF8(zIn) {                        \
  if( (*(zIn++))>=0xc0 ){                              \
    while( (*zIn & 0xc0)==0x80 ){ zIn++; }             \
  }                                                    \
}

/*
** The SQLITE_*_BKPT macros are substitutes for the error codes with
** the same name but without the _BKPT suffix.  These macros invoke
** routines that report the line-number on which the error originated
** using sqlite3_log().  The routines also provide a convenient place
** to set a debugger breakpoint.
*/
int sqlite3CorruptError(int);
int sqlite3MisuseError(int);
int sqlite3CantopenError(int);
#define SQLITE_CORRUPT_BKPT sqlite3CorruptError(__LINE__)
#define SQLITE_MISUSE_BKPT sqlite3MisuseError(__LINE__)
#define SQLITE_CANTOPEN_BKPT sqlite3CantopenError(__LINE__)
#ifdef SQLITE_DEBUG
  int sqlite3NomemError(int);
  int sqlite3IoerrnomemError(int);
  int sqlite3CorruptPgnoError(int,Pgno);
# define SQLITE_NOMEM_BKPT sqlite3NomemError(__LINE__)
# define SQLITE_IOERR_NOMEM_BKPT sqlite3IoerrnomemError(__LINE__)
# define SQLITE_CORRUPT_PGNO(P) sqlite3CorruptPgnoError(__LINE__,(P))
#else
# define SQLITE_NOMEM_BKPT SQLITE_NOMEM
# define SQLITE_IOERR_NOMEM_BKPT SQLITE_IOERR_NOMEM
# define SQLITE_CORRUPT_PGNO(P) sqlite3CorruptError(__LINE__)
#endif

/*
** FTS3 and FTS4 both require virtual table support
*/
#if defined(SQLITE_OMIT_VIRTUALTABLE)
# undef SQLITE_ENABLE_FTS3
# undef SQLITE_ENABLE_FTS4
#endif

/*
** FTS4 is really an extension for FTS3.  It is enabled using the
** SQLITE_ENABLE_FTS3 macro.  But to avoid confusion we also call
** the SQLITE_ENABLE_FTS4 macro to serve as an alias for SQLITE_ENABLE_FTS3.
*/
#if defined(SQLITE_ENABLE_FTS4) && !defined(SQLITE_ENABLE_FTS3)
# define SQLITE_ENABLE_FTS3 1
#endif

/*
** The ctype.h header is needed for non-ASCII systems.  It is also
** needed by FTS3 when FTS3 is included in the amalgamation.
*/
