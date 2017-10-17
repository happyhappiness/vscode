 # define sqlite3Isspace(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x01)
 # define sqlite3Isalnum(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x06)
 # define sqlite3Isalpha(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x02)
 # define sqlite3Isdigit(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x04)
 # define sqlite3Isxdigit(x)  (sqlite3CtypeMap[(unsigned char)(x)]&0x08)
 # define sqlite3Tolower(x)   (sqlite3UpperToLower[(unsigned char)(x)])
-# define sqlite3Isquote(x)   (sqlite3CtypeMap[(unsigned char)(x)]&0x80)
 #else
 # define sqlite3Toupper(x)   toupper((unsigned char)(x))
 # define sqlite3Isspace(x)   isspace((unsigned char)(x))
 # define sqlite3Isalnum(x)   isalnum((unsigned char)(x))
 # define sqlite3Isalpha(x)   isalpha((unsigned char)(x))
 # define sqlite3Isdigit(x)   isdigit((unsigned char)(x))
 # define sqlite3Isxdigit(x)  isxdigit((unsigned char)(x))
 # define sqlite3Tolower(x)   tolower((unsigned char)(x))
-# define sqlite3Isquote(x)   ((x)=='"'||(x)=='\''||(x)=='['||(x)=='`')
-#endif
-#ifndef SQLITE_OMIT_COMPILEOPTION_DIAGS
-int sqlite3IsIdChar(u8);
 #endif
 
 /*
 ** Internal function prototypes
 */
-int sqlite3StrICmp(const char*,const char*);
+int sqlite3StrICmp(const char *, const char *);
+int sqlite3StrNICmp(const char *, const char *, int);
+int sqlite3IsNumber(const char*, int*, u8);
 int sqlite3Strlen30(const char*);
-char *sqlite3ColumnType(Column*,char*);
-#define sqlite3StrNICmp sqlite3_strnicmp
 
 int sqlite3MallocInit(void);
 void sqlite3MallocEnd(void);
-void *sqlite3Malloc(u64);
-void *sqlite3MallocZero(u64);
-void *sqlite3DbMallocZero(sqlite3*, u64);
-void *sqlite3DbMallocRaw(sqlite3*, u64);
-void *sqlite3DbMallocRawNN(sqlite3*, u64);
+void *sqlite3Malloc(int);
+void *sqlite3MallocZero(int);
+void *sqlite3DbMallocZero(sqlite3*, int);
+void *sqlite3DbMallocRaw(sqlite3*, int);
 char *sqlite3DbStrDup(sqlite3*,const char*);
-char *sqlite3DbStrNDup(sqlite3*,const char*, u64);
-void *sqlite3Realloc(void*, u64);
-void *sqlite3DbReallocOrFree(sqlite3 *, void *, u64);
-void *sqlite3DbRealloc(sqlite3 *, void *, u64);
+char *sqlite3DbStrNDup(sqlite3*,const char*, int);
+void *sqlite3Realloc(void*, int);
+void *sqlite3DbReallocOrFree(sqlite3 *, void *, int);
+void *sqlite3DbRealloc(sqlite3 *, void *, int);
 void sqlite3DbFree(sqlite3*, void*);
-void sqlite3DbFreeNN(sqlite3*, void*);
 int sqlite3MallocSize(void*);
 int sqlite3DbMallocSize(sqlite3*, void*);
+void *sqlite3ScratchMalloc(int);
+void sqlite3ScratchFree(void*);
 void *sqlite3PageMalloc(int);
 void sqlite3PageFree(void*);
 void sqlite3MemSetDefault(void);
-#ifndef SQLITE_UNTESTABLE
 void sqlite3BenignMallocHooks(void (*)(void), void (*)(void));
-#endif
-int sqlite3HeapNearlyFull(void);
+int sqlite3MemoryAlarm(void (*)(void*, sqlite3_int64, int), void*, sqlite3_int64);
 
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
-# define sqlite3StackFree(D,P)
+# define sqlite3StackFree(D,P)       
 #else
 # define sqlite3StackAllocRaw(D,N)   sqlite3DbMallocRaw(D,N)
 # define sqlite3StackAllocZero(D,N)  sqlite3DbMallocZero(D,N)
 # define sqlite3StackFree(D,P)       sqlite3DbFree(D,P)
 #endif
 
-/* Do not allow both MEMSYS5 and MEMSYS3 to be defined together.  If they
-** are, disable MEMSYS3
-*/
-#ifdef SQLITE_ENABLE_MEMSYS5
-const sqlite3_mem_methods *sqlite3MemGetMemsys5(void);
-#undef SQLITE_ENABLE_MEMSYS3
-#endif
 #ifdef SQLITE_ENABLE_MEMSYS3
 const sqlite3_mem_methods *sqlite3MemGetMemsys3(void);
 #endif
+#ifdef SQLITE_ENABLE_MEMSYS5
+const sqlite3_mem_methods *sqlite3MemGetMemsys5(void);
+#endif
 
 
 #ifndef SQLITE_MUTEX_OMIT
-  sqlite3_mutex_methods const *sqlite3DefaultMutex(void);
-  sqlite3_mutex_methods const *sqlite3NoopMutex(void);
+  sqlite3_mutex_methods *sqlite3DefaultMutex(void);
   sqlite3_mutex *sqlite3MutexAlloc(int);
   int sqlite3MutexInit(void);
   int sqlite3MutexEnd(void);
 #endif
-#if !defined(SQLITE_MUTEX_OMIT) && !defined(SQLITE_MUTEX_NOOP)
-  void sqlite3MemoryBarrier(void);
-#else
-# define sqlite3MemoryBarrier()
-#endif
-
-sqlite3_int64 sqlite3StatusValue(int);
-void sqlite3StatusUp(int, int);
-void sqlite3StatusDown(int, int);
-void sqlite3StatusHighwater(int, int);
-int sqlite3LookasideUsed(sqlite3*,int*);
 
-/* Access to mutexes used by sqlite3_status() */
-sqlite3_mutex *sqlite3Pcache1Mutex(void);
-sqlite3_mutex *sqlite3MallocMutex(void);
-
-#ifndef SQLITE_OMIT_FLOATING_POINT
-  int sqlite3IsNaN(double);
-#else
-# define sqlite3IsNaN(X)  0
-#endif
+int sqlite3StatusValue(int);
+void sqlite3StatusAdd(int, int);
+void sqlite3StatusSet(int, int);
 
-/*
-** An instance of the following structure holds information about SQL
-** functions arguments that are the parameters to the printf() function.
-*/
-struct PrintfArguments {
-  int nArg;                /* Total number of arguments */
-  int nUsed;               /* Number of arguments used so far */
-  sqlite3_value **apArg;   /* The argument values */
-};
+int sqlite3IsNaN(double);
 
-void sqlite3VXPrintf(StrAccum*, const char*, va_list);
-void sqlite3XPrintf(StrAccum*, const char*, ...);
+void sqlite3VXPrintf(StrAccum*, int, const char*, va_list);
 char *sqlite3MPrintf(sqlite3*,const char*, ...);
 char *sqlite3VMPrintf(sqlite3*,const char*, va_list);
-#if defined(SQLITE_DEBUG) || defined(SQLITE_HAVE_OS_TRACE)
+char *sqlite3MAppendf(sqlite3*,char*,const char*,...);
+#if defined(SQLITE_TEST) || defined(SQLITE_DEBUG)
   void sqlite3DebugPrintf(const char*, ...);
 #endif
 #if defined(SQLITE_TEST)
   void *sqlite3TestTextToPtr(const char*);
 #endif
-
-#if defined(SQLITE_DEBUG)
-  void sqlite3TreeViewExpr(TreeView*, const Expr*, u8);
-  void sqlite3TreeViewBareExprList(TreeView*, const ExprList*, const char*);
-  void sqlite3TreeViewExprList(TreeView*, const ExprList*, u8, const char*);
-  void sqlite3TreeViewSelect(TreeView*, const Select*, u8);
-  void sqlite3TreeViewWith(TreeView*, const With*, u8);
-#endif
-
-
-void sqlite3SetString(char **, sqlite3*, const char*);
+void sqlite3SetString(char **, sqlite3*, const char*, ...);
 void sqlite3ErrorMsg(Parse*, const char*, ...);
-void sqlite3Dequote(char*);
-void sqlite3TokenInit(Token*,char*);
+void sqlite3ErrorClear(Parse*);
+int sqlite3Dequote(char*);
 int sqlite3KeywordCode(const unsigned char*, int);
 int sqlite3RunParser(Parse*, const char*, char **);
 void sqlite3FinishCoding(Parse*);
 int sqlite3GetTempReg(Parse*);
 void sqlite3ReleaseTempReg(Parse*,int);
 int sqlite3GetTempRange(Parse*,int);
 void sqlite3ReleaseTempRange(Parse*,int,int);
-void sqlite3ClearTempRegCache(Parse*);
-#ifdef SQLITE_DEBUG
-int sqlite3NoTempsInRange(Parse*,int,int);
-#endif
 Expr *sqlite3ExprAlloc(sqlite3*,int,const Token*,int);
 Expr *sqlite3Expr(sqlite3*,int,const char*);
 void sqlite3ExprAttachSubtrees(sqlite3*,Expr*,Expr*,Expr*);
-Expr *sqlite3PExpr(Parse*, int, Expr*, Expr*);
-void sqlite3PExprAddSelect(Parse*, Expr*, Select*);
+Expr *sqlite3PExpr(Parse*, int, Expr*, Expr*, const Token*);
 Expr *sqlite3ExprAnd(sqlite3*,Expr*, Expr*);
 Expr *sqlite3ExprFunction(Parse*,ExprList*, Token*);
-void sqlite3ExprAssignVarNumber(Parse*, Expr*, u32);
+void sqlite3ExprAssignVarNumber(Parse*, Expr*);
+void sqlite3ExprClear(sqlite3*, Expr*);
 void sqlite3ExprDelete(sqlite3*, Expr*);
 ExprList *sqlite3ExprListAppend(Parse*,ExprList*,Expr*);
-ExprList *sqlite3ExprListAppendVector(Parse*,ExprList*,IdList*,Expr*);
-void sqlite3ExprListSetSortOrder(ExprList*,int);
 void sqlite3ExprListSetName(Parse*,ExprList*,Token*,int);
 void sqlite3ExprListSetSpan(Parse*,ExprList*,ExprSpan*);
 void sqlite3ExprListDelete(sqlite3*, ExprList*);
-u32 sqlite3ExprListFlags(const ExprList*);
 int sqlite3Init(sqlite3*, char**);
 int sqlite3InitCallback(void*, int, char**, char**);
 void sqlite3Pragma(Parse*,Token*,Token*,Token*,int);
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-Module *sqlite3PragmaVtabRegister(sqlite3*,const char *zName);
-#endif
-void sqlite3ResetAllSchemasOfConnection(sqlite3*);
-void sqlite3ResetOneSchema(sqlite3*,int);
-void sqlite3CollapseDatabaseArray(sqlite3*);
+void sqlite3ResetInternalSchema(sqlite3*, int);
+void sqlite3BeginParse(Parse*,int);
 void sqlite3CommitInternalChanges(sqlite3*);
-void sqlite3DeleteColumnNames(sqlite3*,Table*);
-int sqlite3ColumnsFromExprList(Parse*,ExprList*,i16*,Column**);
-void sqlite3SelectAddColumnTypeAndCollation(Parse*,Table*,Select*);
 Table *sqlite3ResultSetOfSelect(Parse*,Select*);
 void sqlite3OpenMasterTable(Parse *, int);
-Index *sqlite3PrimaryKeyIndex(Table*);
-i16 sqlite3ColumnOfIndex(Index*, i16);
 void sqlite3StartTable(Parse*,Token*,Token*,int,int,int,int);
-#if SQLITE_ENABLE_HIDDEN_COLUMNS
-  void sqlite3ColumnPropertiesFromName(Table*, Column*);
-#else
-# define sqlite3ColumnPropertiesFromName(T,C) /* no-op */
-#endif
-void sqlite3AddColumn(Parse*,Token*,Token*);
+void sqlite3AddColumn(Parse*,Token*);
 void sqlite3AddNotNull(Parse*, int);
 void sqlite3AddPrimaryKey(Parse*, ExprList*, int, int, int);
 void sqlite3AddCheckConstraint(Parse*, Expr*);
+void sqlite3AddColumnType(Parse*,Token*);
 void sqlite3AddDefaultValue(Parse*,ExprSpan*);
 void sqlite3AddCollateType(Parse*, Token*);
-void sqlite3EndTable(Parse*,Token*,Token*,u8,Select*);
-int sqlite3ParseUri(const char*,const char*,unsigned int*,
-                    sqlite3_vfs**,char**,char **);
-Btree *sqlite3DbNameToBtree(sqlite3*,const char*);
-
-#ifdef SQLITE_UNTESTABLE
-# define sqlite3FaultSim(X) SQLITE_OK
-#else
-  int sqlite3FaultSim(int);
-#endif
+void sqlite3EndTable(Parse*,Token*,Token*,Select*);
 
 Bitvec *sqlite3BitvecCreate(u32);
 int sqlite3BitvecTest(Bitvec*, u32);
-int sqlite3BitvecTestNotNull(Bitvec*, u32);
 int sqlite3BitvecSet(Bitvec*, u32);
 void sqlite3BitvecClear(Bitvec*, u32, void*);
 void sqlite3BitvecDestroy(Bitvec*);
 u32 sqlite3BitvecSize(Bitvec*);
-#ifndef SQLITE_UNTESTABLE
 int sqlite3BitvecBuiltinTest(int,int*);
-#endif
 
 RowSet *sqlite3RowSetInit(sqlite3*, void*, unsigned int);
 void sqlite3RowSetClear(RowSet*);
 void sqlite3RowSetInsert(RowSet*, i64);
-int sqlite3RowSetTest(RowSet*, int iBatch, i64);
+int sqlite3RowSetTest(RowSet*, u8 iBatch, i64);
 int sqlite3RowSetNext(RowSet*, i64*);
 
-void sqlite3CreateView(Parse*,Token*,Token*,Token*,ExprList*,Select*,int,int);
+void sqlite3CreateView(Parse*,Token*,Token*,Token*,Select*,int,int);
 
 #if !defined(SQLITE_OMIT_VIEW) || !defined(SQLITE_OMIT_VIRTUALTABLE)
   int sqlite3ViewGetColumnNames(Parse*,Table*);
 #else
 # define sqlite3ViewGetColumnNames(A,B) 0
 #endif
 
-#if SQLITE_MAX_ATTACHED>30
-  int sqlite3DbMaskAllZero(yDbMask);
-#endif
 void sqlite3DropTable(Parse*, SrcList*, int, int);
-void sqlite3CodeDropTable(Parse*, Table*, int, int);
-void sqlite3DeleteTable(sqlite3*, Table*);
-#ifndef SQLITE_OMIT_AUTOINCREMENT
-  void sqlite3AutoincrementBegin(Parse *pParse);
-  void sqlite3AutoincrementEnd(Parse *pParse);
-#else
-# define sqlite3AutoincrementBegin(X)
-# define sqlite3AutoincrementEnd(X)
-#endif
-void sqlite3Insert(Parse*, SrcList*, Select*, IdList*, int);
-void *sqlite3ArrayAllocate(sqlite3*,void*,int,int*,int*);
+void sqlite3DeleteTable(Table*);
+void sqlite3Insert(Parse*, SrcList*, ExprList*, Select*, IdList*, int);
+void *sqlite3ArrayAllocate(sqlite3*,void*,int,int,int*,int*,int*);
 IdList *sqlite3IdListAppend(sqlite3*, IdList*, Token*);
 int sqlite3IdListIndex(IdList*,const char*);
 SrcList *sqlite3SrcListEnlarge(sqlite3*, SrcList*, int, int);
 SrcList *sqlite3SrcListAppend(sqlite3*, SrcList*, Token*, Token*);
 SrcList *sqlite3SrcListAppendFromTerm(Parse*, SrcList*, Token*, Token*,
                                       Token*, Select*, Expr*, IdList*);
 void sqlite3SrcListIndexedBy(Parse *, SrcList *, Token *);
-void sqlite3SrcListFuncArgs(Parse*, SrcList*, ExprList*);
 int sqlite3IndexedByLookup(Parse *, struct SrcList_item *);
 void sqlite3SrcListShiftJoinType(SrcList*);
 void sqlite3SrcListAssignCursors(Parse*, SrcList*);
 void sqlite3IdListDelete(sqlite3*, IdList*);
 void sqlite3SrcListDelete(sqlite3*, SrcList*);
-Index *sqlite3AllocateIndexObject(sqlite3*,i16,int,char**);
 void sqlite3CreateIndex(Parse*,Token*,Token*,SrcList*,ExprList*,int,Token*,
-                          Expr*, int, int, u8);
+                        Token*, int, int);
 void sqlite3DropIndex(Parse*, SrcList*, int);
 int sqlite3Select(Parse*, Select*, SelectDest*);
 Select *sqlite3SelectNew(Parse*,ExprList*,SrcList*,Expr*,ExprList*,
-                         Expr*,ExprList*,u32,Expr*,Expr*);
+                         Expr*,ExprList*,int,Expr*,Expr*);
 void sqlite3SelectDelete(sqlite3*, Select*);
 Table *sqlite3SrcListLookup(Parse*, SrcList*);
 int sqlite3IsReadOnly(Parse*, Table*, int);
 void sqlite3OpenTable(Parse*, int iCur, int iDb, Table*, int);
 #if defined(SQLITE_ENABLE_UPDATE_DELETE_LIMIT) && !defined(SQLITE_OMIT_SUBQUERY)
-Expr *sqlite3LimitWhere(Parse*,SrcList*,Expr*,ExprList*,Expr*,Expr*,char*);
+Expr *sqlite3LimitWhere(Parse *, SrcList *, Expr *, ExprList *, Expr *, Expr *, char *);
 #endif
 void sqlite3DeleteFrom(Parse*, SrcList*, Expr*);
 void sqlite3Update(Parse*, SrcList*, ExprList*, Expr*, int);
-WhereInfo *sqlite3WhereBegin(Parse*,SrcList*,Expr*,ExprList*,ExprList*,u16,int);
+WhereInfo *sqlite3WhereBegin(Parse*, SrcList*, Expr*, ExprList**, u16);
 void sqlite3WhereEnd(WhereInfo*);
-LogEst sqlite3WhereOutputRowCount(WhereInfo*);
-int sqlite3WhereIsDistinct(WhereInfo*);
-int sqlite3WhereIsOrdered(WhereInfo*);
-int sqlite3WhereOrderedInnerLoop(WhereInfo*);
-int sqlite3WhereIsSorted(WhereInfo*);
-int sqlite3WhereContinueLabel(WhereInfo*);
-int sqlite3WhereBreakLabel(WhereInfo*);
-int sqlite3WhereOkOnePass(WhereInfo*, int*);
-#define ONEPASS_OFF      0        /* Use of ONEPASS not allowed */
-#define ONEPASS_SINGLE   1        /* ONEPASS valid for a single row update */
-#define ONEPASS_MULTI    2        /* ONEPASS is valid for multiple rows */
-void sqlite3ExprCodeLoadIndexColumn(Parse*, Index*, int, int, int);
-int sqlite3ExprCodeGetColumn(Parse*, Table*, int, int, int, u8);
-void sqlite3ExprCodeGetColumnToReg(Parse*, Table*, int, int, int);
-void sqlite3ExprCodeGetColumnOfTable(Vdbe*, Table*, int, int, int);
+int sqlite3ExprCodeGetColumn(Parse*, Table*, int, int, int, int);
 void sqlite3ExprCodeMove(Parse*, int, int, int);
+void sqlite3ExprCodeCopy(Parse*, int, int, int);
 void sqlite3ExprCacheStore(Parse*, int, int, int);
 void sqlite3ExprCachePush(Parse*);
-void sqlite3ExprCachePop(Parse*);
-void sqlite3ExprCacheRemove(Parse*, int, int);
+void sqlite3ExprCachePop(Parse*, int);
+void sqlite3ExprCacheRemove(Parse*, int);
 void sqlite3ExprCacheClear(Parse*);
 void sqlite3ExprCacheAffinityChange(Parse*, int, int);
-void sqlite3ExprCode(Parse*, Expr*, int);
-void sqlite3ExprCodeCopy(Parse*, Expr*, int);
-void sqlite3ExprCodeFactorable(Parse*, Expr*, int);
-int sqlite3ExprCodeAtInit(Parse*, Expr*, int);
+void sqlite3ExprHardCopy(Parse*,int,int);
+int sqlite3ExprCode(Parse*, Expr*, int);
 int sqlite3ExprCodeTemp(Parse*, Expr*, int*);
 int sqlite3ExprCodeTarget(Parse*, Expr*, int);
-void sqlite3ExprCodeAndCache(Parse*, Expr*, int);
-int sqlite3ExprCodeExprList(Parse*, ExprList*, int, int, u8);
-#define SQLITE_ECEL_DUP      0x01  /* Deep, not shallow copies */
-#define SQLITE_ECEL_FACTOR   0x02  /* Factor out constant terms */
-#define SQLITE_ECEL_REF      0x04  /* Use ExprList.u.x.iOrderByCol */
-#define SQLITE_ECEL_OMITREF  0x08  /* Omit if ExprList.u.x.iOrderByCol */
+int sqlite3ExprCodeAndCache(Parse*, Expr*, int);
+void sqlite3ExprCodeConstants(Parse*, Expr*);
+int sqlite3ExprCodeExprList(Parse*, ExprList*, int, int);
 void sqlite3ExprIfTrue(Parse*, Expr*, int, int);
 void sqlite3ExprIfFalse(Parse*, Expr*, int, int);
-void sqlite3ExprIfFalseDup(Parse*, Expr*, int, int);
 Table *sqlite3FindTable(sqlite3*,const char*, const char*);
-#define LOCATE_VIEW    0x01
-#define LOCATE_NOERR   0x02
-Table *sqlite3LocateTable(Parse*,u32 flags,const char*, const char*);
-Table *sqlite3LocateTableItem(Parse*,u32 flags,struct SrcList_item *);
+Table *sqlite3LocateTable(Parse*,int isView,const char*, const char*);
 Index *sqlite3FindIndex(sqlite3*,const char*, const char*);
 void sqlite3UnlinkAndDeleteTable(sqlite3*,int,const char*);
 void sqlite3UnlinkAndDeleteIndex(sqlite3*,int,const char*);
-void sqlite3Vacuum(Parse*,Token*);
-int sqlite3RunVacuum(char**, sqlite3*, int);
+void sqlite3Vacuum(Parse*);
+int sqlite3RunVacuum(char**, sqlite3*);
 char *sqlite3NameFromToken(sqlite3*, Token*);
-int sqlite3ExprCompare(Parse*,Expr*, Expr*, int);
-int sqlite3ExprCompareSkip(Expr*, Expr*, int);
-int sqlite3ExprListCompare(ExprList*, ExprList*, int);
-int sqlite3ExprImpliesExpr(Parse*,Expr*, Expr*, int);
+int sqlite3ExprCompare(Expr*, Expr*);
 void sqlite3ExprAnalyzeAggregates(NameContext*, Expr*);
 void sqlite3ExprAnalyzeAggList(NameContext*,ExprList*);
-int sqlite3ExprCoveredByIndex(Expr*, int iCur, Index *pIdx);
-int sqlite3FunctionUsesThisSrc(Expr*, SrcList*);
 Vdbe *sqlite3GetVdbe(Parse*);
-#ifndef SQLITE_UNTESTABLE
+Expr *sqlite3CreateIdExpr(Parse *, const char*);
 void sqlite3PrngSaveState(void);
 void sqlite3PrngRestoreState(void);
-#endif
-void sqlite3RollbackAll(sqlite3*,int);
+void sqlite3PrngResetState(void);
+void sqlite3RollbackAll(sqlite3*);
 void sqlite3CodeVerifySchema(Parse*, int);
-void sqlite3CodeVerifyNamedSchema(Parse*, const char *zDb);
 void sqlite3BeginTransaction(Parse*, int);
-void sqlite3EndTransaction(Parse*,int);
+void sqlite3CommitTransaction(Parse*);
+void sqlite3RollbackTransaction(Parse*);
 void sqlite3Savepoint(Parse*, int, Token*);
 void sqlite3CloseSavepoints(sqlite3 *);
-void sqlite3LeaveMutexAndCloseZombie(sqlite3*);
 int sqlite3ExprIsConstant(Expr*);
 int sqlite3ExprIsConstantNotJoin(Expr*);
-int sqlite3ExprIsConstantOrFunction(Expr*, u8);
-int sqlite3ExprIsConstantOrGroupBy(Parse*, Expr*, ExprList*);
-int sqlite3ExprIsTableConstant(Expr*,int);
-#ifdef SQLITE_ENABLE_CURSOR_HINTS
-int sqlite3ExprContainsSubquery(Expr*);
-#endif
+int sqlite3ExprIsConstantOrFunction(Expr*);
 int sqlite3ExprIsInteger(Expr*, int*);
-int sqlite3ExprCanBeNull(const Expr*);
-int sqlite3ExprNeedsNoAffinityChange(const Expr*, char);
 int sqlite3IsRowid(const char*);
-void sqlite3GenerateRowDelete(
-    Parse*,Table*,Trigger*,int,int,int,i16,u8,u8,u8,int);
-void sqlite3GenerateRowIndexDelete(Parse*, Table*, int, int, int*, int);
-int sqlite3GenerateIndexKey(Parse*, Index*, int, int, int, int*,Index*,int);
-void sqlite3ResolvePartIdxLabel(Parse*,int);
-void sqlite3GenerateConstraintChecks(Parse*,Table*,int*,int,int,int,int,
-                                     u8,u8,int,int*,int*);
-#ifdef SQLITE_ENABLE_NULL_TRIM
-  void sqlite3SetMakeRecordP5(Vdbe*,Table*);
-#else
-# define sqlite3SetMakeRecordP5(A,B)
-#endif
-void sqlite3CompleteInsertion(Parse*,Table*,int,int,int,int*,int,int,int);
-int sqlite3OpenTableAndIndices(Parse*, Table*, int, u8, int, u8*, int*, int*);
+void sqlite3GenerateRowDelete(Parse*, Table*, int, int, int);
+void sqlite3GenerateRowIndexDelete(Parse*, Table*, int, int*);
+int sqlite3GenerateIndexKey(Parse*, Index*, int, int, int);
+void sqlite3GenerateConstraintChecks(Parse*,Table*,int,int,
+                                     int*,int,int,int,int,int*);
+void sqlite3CompleteInsertion(Parse*, Table*, int, int, int*, int, int,int,int);
+int sqlite3OpenTableAndIndices(Parse*, Table*, int, int);
 void sqlite3BeginWriteOperation(Parse*, int, int);
-void sqlite3MultiWrite(Parse*);
-void sqlite3MayAbort(Parse*);
-void sqlite3HaltConstraint(Parse*, int, int, char*, i8, u8);
-void sqlite3UniqueConstraint(Parse*, int, Index*);
-void sqlite3RowidConstraint(Parse*, int, Table*);
 Expr *sqlite3ExprDup(sqlite3*,Expr*,int);
 ExprList *sqlite3ExprListDup(sqlite3*,ExprList*,int);
 SrcList *sqlite3SrcListDup(sqlite3*,SrcList*,int);
 IdList *sqlite3IdListDup(sqlite3*,IdList*);
 Select *sqlite3SelectDup(sqlite3*,Select*,int);
-#if SELECTTRACE_ENABLED
-void sqlite3SelectSetName(Select*,const char*);
+void sqlite3FuncDefInsert(FuncDefHash*, FuncDef*);
+FuncDef *sqlite3FindFunction(sqlite3*,const char*,int,int,u8,int);
+void sqlite3RegisterBuiltinFunctions(sqlite3*);
+void sqlite3RegisterDateTimeFunctions(void);
+void sqlite3RegisterGlobalFunctions(void);
+#ifdef SQLITE_DEBUG
+  int sqlite3SafetyOn(sqlite3*);
+  int sqlite3SafetyOff(sqlite3*);
 #else
-# define sqlite3SelectSetName(A,B)
+# define sqlite3SafetyOn(A) 0
+# define sqlite3SafetyOff(A) 0
 #endif
-void sqlite3InsertBuiltinFuncs(FuncDef*,int);
-FuncDef *sqlite3FindFunction(sqlite3*,const char*,int,u8,u8);
-void sqlite3RegisterBuiltinFunctions(void);
-void sqlite3RegisterDateTimeFunctions(void);
-void sqlite3RegisterPerConnectionBuiltinFunctions(sqlite3*);
 int sqlite3SafetyCheckOk(sqlite3*);
 int sqlite3SafetyCheckSickOrOk(sqlite3*);
 void sqlite3ChangeCookie(Parse*, int);
 
 #if !defined(SQLITE_OMIT_VIEW) && !defined(SQLITE_OMIT_TRIGGER)
 void sqlite3MaterializeView(Parse*, Table*, Expr*, int);
