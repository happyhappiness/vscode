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
 * target    -> A token holding the quoted name of the table to insert into.
 * pExprList -> If this is an INSERT INTO ... VALUES ... statement, then
 *              this stores values to be inserted. Otherwise NULL.
 * pIdList   -> If this is an INSERT INTO ... (<column-names>) VALUES ... 
 *              statement, then this stores the column-names to be
 *              inserted into.
 *
 * (op == TK_DELETE)
 * target    -> A token holding the quoted name of the table to delete from.
 * pWhere    -> The WHERE clause of the DELETE statement if one is specified.
 *              Otherwise NULL.
 * 
 * (op == TK_UPDATE)
 * target    -> A token holding the quoted name of the table to update rows of.
 * pWhere    -> The WHERE clause of the UPDATE statement if one is specified.
 *              Otherwise NULL.
 * pExprList -> A list of the columns to update and the expressions to update
 *              them to. See sqlite3Update() documentation of "pChanges"
 *              argument.
 * 
 */
struct TriggerStep {
  int op;              /* One of TK_DELETE, TK_UPDATE, TK_INSERT, TK_SELECT */
  int orconf;          /* OE_Rollback etc. */
  Trigger *pTrig;      /* The trigger that this step is a part of */

  Select *pSelect;     /* Valid for SELECT and sometimes 
                          INSERT steps (when pExprList == 0) */
  Token target;        /* Target table for DELETE, UPDATE, INSERT.  Quoted */
  Expr *pWhere;        /* Valid for DELETE, UPDATE steps */
  ExprList *pExprList; /* Valid for UPDATE statements and sometimes 
                           INSERT steps (when pSelect == 0)         */
  IdList *pIdList;     /* Valid for INSERT statements only */
  TriggerStep *pNext;  /* Next in the link-list */
  TriggerStep *pLast;  /* Last element in link-list. Valid for 1st elem only */
};

/*
 * An instance of struct TriggerStack stores information required during code
 * generation of a single trigger program. While the trigger program is being
 * coded, its associated TriggerStack instance is pointed to by the
 * "pTriggerStack" member of the Parse structure.
 *
 * The pTab member points to the table that triggers are being coded on. The 
 * newIdx member contains the index of the vdbe cursor that points at the temp
 * table that stores the new.* references. If new.* references are not valid
 * for the trigger being coded (for example an ON DELETE trigger), then newIdx
 * is set to -1. The oldIdx member is analogous to newIdx, for old.* references.
 *
 * The ON CONFLICT policy to be used for the trigger program steps is stored 
 * as the orconf member. If this is OE_Default, then the ON CONFLICT clause 
 * specified for individual triggers steps is used.
 *
 * struct TriggerStack has a "pNext" member, to allow linked lists to be
 * constructed. When coding nested triggers (triggers fired by other triggers)
 * each nested trigger stores its parent trigger's TriggerStack as the "pNext" 
 * pointer. Once the nested trigger has been coded, the pNext value is restored
 * to the pTriggerStack member of the Parse stucture and coding of the parent
 * trigger continues.
 *
 * Before a nested trigger is coded, the linked list pointed to by the 
 * pTriggerStack is scanned to ensure that the trigger is not about to be coded
 * recursively. If this condition is detected, the nested trigger is not coded.
 */
struct TriggerStack {
  Table *pTab;         /* Table that triggers are currently being coded on */
  int newIdx;          /* Index of vdbe cursor to "new" temp table */
  int oldIdx;          /* Index of vdbe cursor to "old" temp table */
  u32 newColMask;
  u32 oldColMask;
  int orconf;          /* Current orconf policy */
  int ignoreJump;      /* where to jump to for a RAISE(IGNORE) */
  Trigger *pTrigger;   /* The trigger currently being coded */
  TriggerStack *pNext; /* Next trigger down on the trigger stack */
};

/*
** The following structure contains information used by the sqliteFix...
** routines as they walk the parse tree to make database references
** explicit.  
*/
typedef struct DbFixer DbFixer;
struct DbFixer {
  Parse *pParse;      /* The parsing context.  Error messages written here */
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
  char *zBase;         /* A base allocation.  Not from malloc. */
  char *zText;         /* The string collected so far */
  int  nChar;          /* Length of the string so far */
  int  nAlloc;         /* Amount of space allocated in zText */
  int  mxAlloc;        /* Maximum allowed string length */
  u8   mallocFailed;   /* Becomes true if any memory allocation fails */
  u8   useMalloc;      /* True if zText is enlargeable using realloc */
  u8   tooBig;         /* Becomes true if string size exceeds limits */
};

/*
** A pointer to this structure is used to communicate information
** from sqlite3Init and OP_ParseSchema into the sqlite3InitCallback.
*/
typedef struct {
  sqlite3 *db;        /* The database being initialized */
  int iDb;            /* 0 for main database.  1 for TEMP, 2.. for ATTACHed */
  char **pzErrMsg;    /* Error message stored here */
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
  int mxStrlen;                     /* Maximum string length */
  int szLookaside;                  /* Default lookaside buffer size */
  int nLookaside;                   /* Default lookaside buffer count */
  sqlite3_mem_methods m;            /* Low-level memory allocation interface */
  sqlite3_mutex_methods mutex;      /* Low-level mutex interface */
  sqlite3_pcache_methods pcache;    /* Low-level page-cache interface */
  void *pHeap;                      /* Heap storage space */
  int nHeap;                        /* Size of pHeap[] */
  int mnReq, mxReq;                 /* Min and max heap requests sizes */
  void *pScratch;                   /* Scratch memory */
  int szScratch;                    /* Size of each scratch buffer */
  int nScratch;                     /* Number of scratch buffers */
  void *pPage;                      /* Page cache memory */
  int szPage;                       /* Size of each page in pPage[] */
  int nPage;                        /* Number of pages in pPage[] */
  int mxParserStack;                /* maximum depth of the parser stack */
  int sharedCacheEnabled;           /* true if shared-cache mode enabled */
  /* The above might be initialized to non-zero.  The following need to always
  ** initially be zero, however. */
  int isInit;                       /* True after initialization has finished */
  int inProgress;                   /* True while initialization in progress */
  int isMallocInit;                 /* True after malloc is initialized */
  sqlite3_mutex *pInitMutex;        /* Mutex used by sqlite3_initialize() */
  int nRefInitMutex;                /* Number of users of pInitMutex */
};

/*
** Context pointer passed down through the tree-walk.
*/
struct Walker {
  int (*xExprCallback)(Walker*, Expr*);     /* Callback for expressions */
  int (*xSelectCallback)(Walker*,Select*);  /* Callback for SELECTs */
  Parse *pParse;                            /* Parser context.  */
  union {                                   /* Extra data for callback */
    NameContext *pNC;                          /* Naming context */
    int i;                                     /* Integer value */
  } u;
};

/* Forward declarations */
int sqlite3WalkExpr(Walker*, Expr*);
int sqlite3WalkExprList(Walker*, ExprList*);
int sqlite3WalkSelect(Walker*, Select*);
int sqlite3WalkSelectExpr(Walker*, Select*);
int sqlite3WalkSelectFrom(Walker*, Select*);

/*
** Return code from the parse-tree walking primitives and their
** callbacks.
*/
#define WRC_Continue    0   /* Continue down into children */
#define WRC_Prune       1   /* Omit children but continue walking siblings */
#define WRC_Abort       2   /* Abandon the tree walk */

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
** The SQLITE_CORRUPT_BKPT macro can be either a constant (for production
** builds) or a function call (for debugging).  If it is a function call,
** it allows the operator to set a breakpoint at the spot where database
** corruption is first detected.
*/
#ifdef SQLITE_DEBUG
  int sqlite3Corrupt(void);
# define SQLITE_CORRUPT_BKPT sqlite3Corrupt()
#else
# define SQLITE_CORRUPT_BKPT SQLITE_CORRUPT
#endif

/*
** The ctype.h header is needed for non-ASCII systems.  It is also
** needed by FTS3 when FTS3 is included in the amalgamation.
*/
