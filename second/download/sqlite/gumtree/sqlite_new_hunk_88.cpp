# define sqlite3Isspace(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x01)
# define sqlite3Isalnum(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x06)
# define sqlite3Isalpha(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x02)
# define sqlite3Isdigit(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x04)
# define sqlite3Isxdigit(x)  (sqlite3CtypeMap[(unsigned char)(x)]&0x08)
# define sqlite3Tolower(x)   (sqlite3UpperToLower[(unsigned char)(x)])
#else
# define sqlite3Toupper(x)   toupper((unsigned char)(x))
# define sqlite3Isspace(x)   isspace((unsigned char)(x))
# define sqlite3Isalnum(x)   isalnum((unsigned char)(x))
# define sqlite3Isalpha(x)   isalpha((unsigned char)(x))
# define sqlite3Isdigit(x)   isdigit((unsigned char)(x))
# define sqlite3Isxdigit(x)  isxdigit((unsigned char)(x))
# define sqlite3Tolower(x)   tolower((unsigned char)(x))
#endif

/*
** Internal function prototypes
*/
int sqlite3StrICmp(const char *, const char *);
int sqlite3StrNICmp(const char *, const char *, int);
int sqlite3IsNumber(const char*, int*, u8);
int sqlite3Strlen30(const char*);

int sqlite3MallocInit(void);
void sqlite3MallocEnd(void);
void *sqlite3Malloc(int);
void *sqlite3MallocZero(int);
void *sqlite3DbMallocZero(sqlite3*, int);
void *sqlite3DbMallocRaw(sqlite3*, int);
char *sqlite3DbStrDup(sqlite3*,const char*);
char *sqlite3DbStrNDup(sqlite3*,const char*, int);
void *sqlite3Realloc(void*, int);
void *sqlite3DbReallocOrFree(sqlite3 *, void *, int);
void *sqlite3DbRealloc(sqlite3 *, void *, int);
void sqlite3DbFree(sqlite3*, void*);
int sqlite3MallocSize(void*);
int sqlite3DbMallocSize(sqlite3*, void*);
void *sqlite3ScratchMalloc(int);
void sqlite3ScratchFree(void*);
void *sqlite3PageMalloc(int);
void sqlite3PageFree(void*);
void sqlite3MemSetDefault(void);
void sqlite3BenignMallocHooks(void (*)(void), void (*)(void));
int sqlite3MemoryAlarm(void (*)(void*, sqlite3_int64, int), void*, sqlite3_int64);

/*
** On systems with ample stack space and that support alloca(), make
** use of alloca() to obtain space for large automatic objects.  By default,
** obtain space from malloc().
**
** The alloca() routine never returns NULL.  This will cause code paths
** that deal with sqlite3StackAlloc() failures to be unreachable.
*/
#ifdef SQLITE_USE_ALLOCA
# define sqlite3StackAllocRaw(D,N)   alloca(N)
# define sqlite3StackAllocZero(D,N)  memset(alloca(N), 0, N)
# define sqlite3StackFree(D,P)       
#else
# define sqlite3StackAllocRaw(D,N)   sqlite3DbMallocRaw(D,N)
# define sqlite3StackAllocZero(D,N)  sqlite3DbMallocZero(D,N)
# define sqlite3StackFree(D,P)       sqlite3DbFree(D,P)
#endif

#ifdef SQLITE_ENABLE_MEMSYS3
const sqlite3_mem_methods *sqlite3MemGetMemsys3(void);
#endif
#ifdef SQLITE_ENABLE_MEMSYS5
const sqlite3_mem_methods *sqlite3MemGetMemsys5(void);
#endif


#ifndef SQLITE_MUTEX_OMIT
  sqlite3_mutex_methods *sqlite3DefaultMutex(void);
  sqlite3_mutex *sqlite3MutexAlloc(int);
  int sqlite3MutexInit(void);
  int sqlite3MutexEnd(void);
#endif

int sqlite3StatusValue(int);
void sqlite3StatusAdd(int, int);
void sqlite3StatusSet(int, int);

int sqlite3IsNaN(double);

void sqlite3VXPrintf(StrAccum*, int, const char*, va_list);
char *sqlite3MPrintf(sqlite3*,const char*, ...);
char *sqlite3VMPrintf(sqlite3*,const char*, va_list);
char *sqlite3MAppendf(sqlite3*,char*,const char*,...);
#if defined(SQLITE_TEST) || defined(SQLITE_DEBUG)
  void sqlite3DebugPrintf(const char*, ...);
#endif
#if defined(SQLITE_TEST)
  void *sqlite3TestTextToPtr(const char*);
#endif
void sqlite3SetString(char **, sqlite3*, const char*, ...);
void sqlite3ErrorMsg(Parse*, const char*, ...);
void sqlite3ErrorClear(Parse*);
int sqlite3Dequote(char*);
int sqlite3KeywordCode(const unsigned char*, int);
int sqlite3RunParser(Parse*, const char*, char **);
void sqlite3FinishCoding(Parse*);
int sqlite3GetTempReg(Parse*);
void sqlite3ReleaseTempReg(Parse*,int);
int sqlite3GetTempRange(Parse*,int);
void sqlite3ReleaseTempRange(Parse*,int,int);
Expr *sqlite3ExprAlloc(sqlite3*,int,const Token*,int);
Expr *sqlite3Expr(sqlite3*,int,const char*);
void sqlite3ExprAttachSubtrees(sqlite3*,Expr*,Expr*,Expr*);
Expr *sqlite3PExpr(Parse*, int, Expr*, Expr*, const Token*);
Expr *sqlite3ExprAnd(sqlite3*,Expr*, Expr*);
Expr *sqlite3ExprFunction(Parse*,ExprList*, Token*);
void sqlite3ExprAssignVarNumber(Parse*, Expr*);
void sqlite3ExprClear(sqlite3*, Expr*);
void sqlite3ExprDelete(sqlite3*, Expr*);
ExprList *sqlite3ExprListAppend(Parse*,ExprList*,Expr*);
void sqlite3ExprListSetName(Parse*,ExprList*,Token*,int);
void sqlite3ExprListSetSpan(Parse*,ExprList*,ExprSpan*);
void sqlite3ExprListDelete(sqlite3*, ExprList*);
int sqlite3Init(sqlite3*, char**);
int sqlite3InitCallback(void*, int, char**, char**);
void sqlite3Pragma(Parse*,Token*,Token*,Token*,int);
void sqlite3ResetInternalSchema(sqlite3*, int);
void sqlite3BeginParse(Parse*,int);
void sqlite3CommitInternalChanges(sqlite3*);
Table *sqlite3ResultSetOfSelect(Parse*,Select*);
void sqlite3OpenMasterTable(Parse *, int);
void sqlite3StartTable(Parse*,Token*,Token*,int,int,int,int);
void sqlite3AddColumn(Parse*,Token*);
void sqlite3AddNotNull(Parse*, int);
void sqlite3AddPrimaryKey(Parse*, ExprList*, int, int, int);
void sqlite3AddCheckConstraint(Parse*, Expr*);
void sqlite3AddColumnType(Parse*,Token*);
void sqlite3AddDefaultValue(Parse*,ExprSpan*);
void sqlite3AddCollateType(Parse*, Token*);
void sqlite3EndTable(Parse*,Token*,Token*,Select*);

Bitvec *sqlite3BitvecCreate(u32);
int sqlite3BitvecTest(Bitvec*, u32);
int sqlite3BitvecSet(Bitvec*, u32);
void sqlite3BitvecClear(Bitvec*, u32, void*);
void sqlite3BitvecDestroy(Bitvec*);
u32 sqlite3BitvecSize(Bitvec*);
int sqlite3BitvecBuiltinTest(int,int*);

RowSet *sqlite3RowSetInit(sqlite3*, void*, unsigned int);
void sqlite3RowSetClear(RowSet*);
void sqlite3RowSetInsert(RowSet*, i64);
int sqlite3RowSetTest(RowSet*, u8 iBatch, i64);
int sqlite3RowSetNext(RowSet*, i64*);

void sqlite3CreateView(Parse*,Token*,Token*,Token*,Select*,int,int);

#if !defined(SQLITE_OMIT_VIEW) || !defined(SQLITE_OMIT_VIRTUALTABLE)
  int sqlite3ViewGetColumnNames(Parse*,Table*);
#else
# define sqlite3ViewGetColumnNames(A,B) 0
#endif

void sqlite3DropTable(Parse*, SrcList*, int, int);
void sqlite3DeleteTable(Table*);
void sqlite3Insert(Parse*, SrcList*, ExprList*, Select*, IdList*, int);
void *sqlite3ArrayAllocate(sqlite3*,void*,int,int,int*,int*,int*);
IdList *sqlite3IdListAppend(sqlite3*, IdList*, Token*);
int sqlite3IdListIndex(IdList*,const char*);
SrcList *sqlite3SrcListEnlarge(sqlite3*, SrcList*, int, int);
SrcList *sqlite3SrcListAppend(sqlite3*, SrcList*, Token*, Token*);
SrcList *sqlite3SrcListAppendFromTerm(Parse*, SrcList*, Token*, Token*,
                                      Token*, Select*, Expr*, IdList*);
void sqlite3SrcListIndexedBy(Parse *, SrcList *, Token *);
int sqlite3IndexedByLookup(Parse *, struct SrcList_item *);
void sqlite3SrcListShiftJoinType(SrcList*);
void sqlite3SrcListAssignCursors(Parse*, SrcList*);
void sqlite3IdListDelete(sqlite3*, IdList*);
void sqlite3SrcListDelete(sqlite3*, SrcList*);
void sqlite3CreateIndex(Parse*,Token*,Token*,SrcList*,ExprList*,int,Token*,
                        Token*, int, int);
void sqlite3DropIndex(Parse*, SrcList*, int);
int sqlite3Select(Parse*, Select*, SelectDest*);
Select *sqlite3SelectNew(Parse*,ExprList*,SrcList*,Expr*,ExprList*,
                         Expr*,ExprList*,int,Expr*,Expr*);
void sqlite3SelectDelete(sqlite3*, Select*);
Table *sqlite3SrcListLookup(Parse*, SrcList*);
int sqlite3IsReadOnly(Parse*, Table*, int);
void sqlite3OpenTable(Parse*, int iCur, int iDb, Table*, int);
#if defined(SQLITE_ENABLE_UPDATE_DELETE_LIMIT) && !defined(SQLITE_OMIT_SUBQUERY)
Expr *sqlite3LimitWhere(Parse *, SrcList *, Expr *, ExprList *, Expr *, Expr *, char *);
#endif
void sqlite3DeleteFrom(Parse*, SrcList*, Expr*);
void sqlite3Update(Parse*, SrcList*, ExprList*, Expr*, int);
WhereInfo *sqlite3WhereBegin(Parse*, SrcList*, Expr*, ExprList**, u16);
void sqlite3WhereEnd(WhereInfo*);
int sqlite3ExprCodeGetColumn(Parse*, Table*, int, int, int, int);
void sqlite3ExprCodeMove(Parse*, int, int, int);
void sqlite3ExprCodeCopy(Parse*, int, int, int);
void sqlite3ExprCacheStore(Parse*, int, int, int);
void sqlite3ExprCachePush(Parse*);
void sqlite3ExprCachePop(Parse*, int);
void sqlite3ExprCacheRemove(Parse*, int);
void sqlite3ExprCacheClear(Parse*);
void sqlite3ExprCacheAffinityChange(Parse*, int, int);
void sqlite3ExprHardCopy(Parse*,int,int);
int sqlite3ExprCode(Parse*, Expr*, int);
int sqlite3ExprCodeTemp(Parse*, Expr*, int*);
int sqlite3ExprCodeTarget(Parse*, Expr*, int);
int sqlite3ExprCodeAndCache(Parse*, Expr*, int);
void sqlite3ExprCodeConstants(Parse*, Expr*);
int sqlite3ExprCodeExprList(Parse*, ExprList*, int, int);
void sqlite3ExprIfTrue(Parse*, Expr*, int, int);
void sqlite3ExprIfFalse(Parse*, Expr*, int, int);
Table *sqlite3FindTable(sqlite3*,const char*, const char*);
Table *sqlite3LocateTable(Parse*,int isView,const char*, const char*);
Index *sqlite3FindIndex(sqlite3*,const char*, const char*);
void sqlite3UnlinkAndDeleteTable(sqlite3*,int,const char*);
void sqlite3UnlinkAndDeleteIndex(sqlite3*,int,const char*);
void sqlite3Vacuum(Parse*);
int sqlite3RunVacuum(char**, sqlite3*);
char *sqlite3NameFromToken(sqlite3*, Token*);
int sqlite3ExprCompare(Expr*, Expr*);
void sqlite3ExprAnalyzeAggregates(NameContext*, Expr*);
void sqlite3ExprAnalyzeAggList(NameContext*,ExprList*);
Vdbe *sqlite3GetVdbe(Parse*);
Expr *sqlite3CreateIdExpr(Parse *, const char*);
void sqlite3PrngSaveState(void);
void sqlite3PrngRestoreState(void);
void sqlite3PrngResetState(void);
void sqlite3RollbackAll(sqlite3*);
void sqlite3CodeVerifySchema(Parse*, int);
void sqlite3BeginTransaction(Parse*, int);
void sqlite3CommitTransaction(Parse*);
void sqlite3RollbackTransaction(Parse*);
void sqlite3Savepoint(Parse*, int, Token*);
void sqlite3CloseSavepoints(sqlite3 *);
int sqlite3ExprIsConstant(Expr*);
int sqlite3ExprIsConstantNotJoin(Expr*);
int sqlite3ExprIsConstantOrFunction(Expr*);
int sqlite3ExprIsInteger(Expr*, int*);
int sqlite3IsRowid(const char*);
void sqlite3GenerateRowDelete(Parse*, Table*, int, int, int);
void sqlite3GenerateRowIndexDelete(Parse*, Table*, int, int*);
int sqlite3GenerateIndexKey(Parse*, Index*, int, int, int);
void sqlite3GenerateConstraintChecks(Parse*,Table*,int,int,
                                     int*,int,int,int,int,int*);
void sqlite3CompleteInsertion(Parse*, Table*, int, int, int*, int, int,int,int);
int sqlite3OpenTableAndIndices(Parse*, Table*, int, int);
void sqlite3BeginWriteOperation(Parse*, int, int);
Expr *sqlite3ExprDup(sqlite3*,Expr*,int);
ExprList *sqlite3ExprListDup(sqlite3*,ExprList*,int);
SrcList *sqlite3SrcListDup(sqlite3*,SrcList*,int);
IdList *sqlite3IdListDup(sqlite3*,IdList*);
Select *sqlite3SelectDup(sqlite3*,Select*,int);
void sqlite3FuncDefInsert(FuncDefHash*, FuncDef*);
FuncDef *sqlite3FindFunction(sqlite3*,const char*,int,int,u8,int);
void sqlite3RegisterBuiltinFunctions(sqlite3*);
void sqlite3RegisterDateTimeFunctions(void);
void sqlite3RegisterGlobalFunctions(void);
#ifdef SQLITE_DEBUG
  int sqlite3SafetyOn(sqlite3*);
  int sqlite3SafetyOff(sqlite3*);
#else
# define sqlite3SafetyOn(A) 0
# define sqlite3SafetyOff(A) 0
#endif
int sqlite3SafetyCheckOk(sqlite3*);
int sqlite3SafetyCheckSickOrOk(sqlite3*);
void sqlite3ChangeCookie(Parse*, int);

#if !defined(SQLITE_OMIT_VIEW) && !defined(SQLITE_OMIT_TRIGGER)
void sqlite3MaterializeView(Parse*, Table*, Expr*, int);
