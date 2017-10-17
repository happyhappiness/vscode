                           Expr*,int, int);
  void sqlite3FinishTrigger(Parse*, TriggerStep*, Token*);
  void sqlite3DropTrigger(Parse*, SrcList*, int);
  void sqlite3DropTriggerPtr(Parse*, Trigger*);
  Trigger *sqlite3TriggersExist(Parse *, Table*, int, ExprList*, int *pMask);
  Trigger *sqlite3TriggerList(Parse *, Table *);
  void sqlite3CodeRowTrigger(Parse*, Trigger *, int, ExprList*, int, Table *,
                            int, int, int);
  void sqlite3CodeRowTriggerDirect(Parse *, Trigger *, Table *, int, int, int);
  void sqliteViewTriggers(Parse*, Table*, Expr*, int, ExprList*);
  void sqlite3DeleteTriggerStep(sqlite3*, TriggerStep*);
  TriggerStep *sqlite3TriggerSelectStep(sqlite3*,Select*);
  TriggerStep *sqlite3TriggerInsertStep(sqlite3*,Token*, IdList*,
                                        Select*,u8);
  TriggerStep *sqlite3TriggerUpdateStep(sqlite3*,Token*,ExprList*, Expr*, u8);
  TriggerStep *sqlite3TriggerDeleteStep(sqlite3*,Token*, Expr*);
  void sqlite3DeleteTrigger(sqlite3*, Trigger*);
  void sqlite3UnlinkAndDeleteTrigger(sqlite3*,int,const char*);
  u32 sqlite3TriggerColmask(Parse*,Trigger*,ExprList*,int,int,Table*,int);
# define sqlite3ParseToplevel(p) ((p)->pToplevel ? (p)->pToplevel : (p))
# define sqlite3IsToplevel(p) ((p)->pToplevel==0)
#else
# define sqlite3TriggersExist(B,C,D,E,F) 0
# define sqlite3DeleteTrigger(A,B)
# define sqlite3DropTriggerPtr(A,B)
# define sqlite3UnlinkAndDeleteTrigger(A,B,C)
# define sqlite3CodeRowTrigger(A,B,C,D,E,F,G,H,I)
# define sqlite3CodeRowTriggerDirect(A,B,C,D,E,F)
# define sqlite3TriggerList(X, Y) 0
# define sqlite3ParseToplevel(p) p
# define sqlite3IsToplevel(p) 1
# define sqlite3TriggerColmask(A,B,C,D,E,F,G) 0
#endif

int sqlite3JoinType(Parse*, Token*, Token*, Token*);
void sqlite3CreateForeignKey(Parse*, ExprList*, Token*, ExprList*, int);
void sqlite3DeferForeignKey(Parse*, int);
#ifndef SQLITE_OMIT_AUTHORIZATION
  void sqlite3AuthRead(Parse*,Expr*,Schema*,SrcList*);
  int sqlite3AuthCheck(Parse*,int, const char*, const char*, const char*);
  void sqlite3AuthContextPush(Parse*, AuthContext*, const char*);
  void sqlite3AuthContextPop(AuthContext*);
  int sqlite3AuthReadCol(Parse*, const char *, const char *, int);
#else
# define sqlite3AuthRead(a,b,c,d)
# define sqlite3AuthCheck(a,b,c,d,e)    SQLITE_OK
# define sqlite3AuthContextPush(a,b,c)
# define sqlite3AuthContextPop(a)  ((void)(a))
#endif
void sqlite3Attach(Parse*, Expr*, Expr*, Expr*);
void sqlite3Detach(Parse*, Expr*);
void sqlite3FixInit(DbFixer*, Parse*, int, const char*, const Token*);
int sqlite3FixSrcList(DbFixer*, SrcList*);
int sqlite3FixSelect(DbFixer*, Select*);
int sqlite3FixExpr(DbFixer*, Expr*);
int sqlite3FixExprList(DbFixer*, ExprList*);
int sqlite3FixTriggerStep(DbFixer*, TriggerStep*);
int sqlite3AtoF(const char *z, double*, int, u8);
int sqlite3GetInt32(const char *, int*);
int sqlite3Atoi(const char*);
#ifndef SQLITE_OMIT_UTF16
int sqlite3Utf16ByteLen(const void *pData, int nChar);
#endif
int sqlite3Utf8CharLen(const char *pData, int nByte);
u32 sqlite3Utf8Read(const u8**);
LogEst sqlite3LogEst(u64);
LogEst sqlite3LogEstAdd(LogEst,LogEst);
#ifndef SQLITE_OMIT_VIRTUALTABLE
LogEst sqlite3LogEstFromDouble(double);
#endif
#if defined(SQLITE_ENABLE_STMT_SCANSTATUS) || \
    defined(SQLITE_ENABLE_STAT3_OR_STAT4) || \
    defined(SQLITE_EXPLAIN_ESTIMATED_ROWS)
u64 sqlite3LogEstToInt(LogEst);
#endif
VList *sqlite3VListAdd(sqlite3*,VList*,const char*,int,int);
const char *sqlite3VListNumToName(VList*,int);
int sqlite3VListNameToNum(VList*,const char*,int);

/*
** Routines to read and write variable-length integers.  These used to
** be defined locally, but now we use the varint routines in the util.c
** file.
*/
int sqlite3PutVarint(unsigned char*, u64);
u8 sqlite3GetVarint(const unsigned char *, u64 *);
u8 sqlite3GetVarint32(const unsigned char *, u32 *);
int sqlite3VarintLen(u64 v);

/*
** The common case is for a varint to be a single byte.  They following
** macros handle the common case without a procedure call, but then call
** the procedure for larger varints.
*/
#define getVarint32(A,B)  \
  (u8)((*(A)<(u8)0x80)?((B)=(u32)*(A)),1:sqlite3GetVarint32((A),(u32 *)&(B)))
#define putVarint32(A,B)  \
  (u8)(((u32)(B)<(u32)0x80)?(*(A)=(unsigned char)(B)),1:\
  sqlite3PutVarint((A),(B)))
#define getVarint    sqlite3GetVarint
#define putVarint    sqlite3PutVarint


const char *sqlite3IndexAffinityStr(sqlite3*, Index*);
void sqlite3TableAffinity(Vdbe*, Table*, int);
char sqlite3CompareAffinity(Expr *pExpr, char aff2);
int sqlite3IndexAffinityOk(Expr *pExpr, char idx_affinity);
char sqlite3TableColumnAffinity(Table*,int);
char sqlite3ExprAffinity(Expr *pExpr);
int sqlite3Atoi64(const char*, i64*, int, u8);
int sqlite3DecOrHexToI64(const char*, i64*);
void sqlite3ErrorWithMsg(sqlite3*, int, const char*,...);
void sqlite3Error(sqlite3*,int);
void sqlite3SystemError(sqlite3*,int);
void *sqlite3HexToBlob(sqlite3*, const char *z, int n);
u8 sqlite3HexToInt(int h);
int sqlite3TwoPartName(Parse *, Token *, Token *, Token **);

#if defined(SQLITE_NEED_ERR_NAME)
const char *sqlite3ErrName(int);
#endif

const char *sqlite3ErrStr(int);
int sqlite3ReadSchema(Parse *pParse);
CollSeq *sqlite3FindCollSeq(sqlite3*,u8 enc, const char*,int);
CollSeq *sqlite3LocateCollSeq(Parse *pParse, const char*zName);
CollSeq *sqlite3ExprCollSeq(Parse *pParse, Expr *pExpr);
CollSeq *sqlite3ExprNNCollSeq(Parse *pParse, Expr *pExpr);
int sqlite3ExprCollSeqMatch(Parse*,Expr*,Expr*);
Expr *sqlite3ExprAddCollateToken(Parse *pParse, Expr*, const Token*, int);
Expr *sqlite3ExprAddCollateString(Parse*,Expr*,const char*);
Expr *sqlite3ExprSkipCollate(Expr*);
int sqlite3CheckCollSeq(Parse *, CollSeq *);
int sqlite3CheckObjectName(Parse *, const char *);
void sqlite3VdbeSetChanges(sqlite3 *, int);
int sqlite3AddInt64(i64*,i64);
int sqlite3SubInt64(i64*,i64);
int sqlite3MulInt64(i64*,i64);
int sqlite3AbsInt32(int);
#ifdef SQLITE_ENABLE_8_3_NAMES
void sqlite3FileSuffix3(const char*, char*);
#else
# define sqlite3FileSuffix3(X,Y)
#endif
u8 sqlite3GetBoolean(const char *z,u8);

const void *sqlite3ValueText(sqlite3_value*, u8);
int sqlite3ValueBytes(sqlite3_value*, u8);
void sqlite3ValueSetStr(sqlite3_value*, int, const void *,u8,
                        void(*)(void*));
void sqlite3ValueSetNull(sqlite3_value*);
void sqlite3ValueFree(sqlite3_value*);
sqlite3_value *sqlite3ValueNew(sqlite3 *);
#ifndef SQLITE_OMIT_UTF16
char *sqlite3Utf16to8(sqlite3 *, const void*, int, u8);
#endif
int sqlite3ValueFromExpr(sqlite3 *, Expr *, u8, u8, sqlite3_value **);
void sqlite3ValueApplyAffinity(sqlite3_value *, u8, u8);
#ifndef SQLITE_AMALGAMATION
extern const unsigned char sqlite3OpcodeProperty[];
extern const char sqlite3StrBINARY[];
extern const unsigned char sqlite3UpperToLower[];
extern const unsigned char sqlite3CtypeMap[];
extern const Token sqlite3IntTokens[];
extern SQLITE_WSD struct Sqlite3Config sqlite3Config;
extern FuncDefHash sqlite3BuiltinFunctions;
#ifndef SQLITE_OMIT_WSD
extern int sqlite3PendingByte;
#endif
#endif
void sqlite3RootPageMoved(sqlite3*, int, int, int);
void sqlite3Reindex(Parse*, Token*, Token*);
void sqlite3AlterFunctions(void);
void sqlite3AlterRenameTable(Parse*, SrcList*, Token*);
int sqlite3GetToken(const unsigned char *, int *);
void sqlite3NestedParse(Parse*, const char*, ...);
void sqlite3ExpirePreparedStatements(sqlite3*);
int sqlite3CodeSubselect(Parse*, Expr *, int, int);
void sqlite3SelectPrep(Parse*, Select*, NameContext*);
void sqlite3SelectWrongNumTermsError(Parse *pParse, Select *p);
int sqlite3MatchSpanName(const char*, const char*, const char*, const char*);
int sqlite3ResolveExprNames(NameContext*, Expr*);
int sqlite3ResolveExprListNames(NameContext*, ExprList*);
void sqlite3ResolveSelectNames(Parse*, Select*, NameContext*);
void sqlite3ResolveSelfReference(Parse*,Table*,int,Expr*,ExprList*);
int sqlite3ResolveOrderGroupBy(Parse*, Select*, ExprList*, const char*);
void sqlite3ColumnDefault(Vdbe *, Table *, int, int);
void sqlite3AlterFinishAddColumn(Parse *, Token *);
void sqlite3AlterBeginAddColumn(Parse *, SrcList *);
CollSeq *sqlite3GetCollSeq(Parse*, u8, CollSeq *, const char*);
char sqlite3AffinityType(const char*, u8*);
void sqlite3Analyze(Parse*, Token*, Token*);
int sqlite3InvokeBusyHandler(BusyHandler*);
int sqlite3FindDb(sqlite3*, Token*);
int sqlite3FindDbName(sqlite3 *, const char *);
int sqlite3AnalysisLoad(sqlite3*,int iDB);
void sqlite3DeleteIndexSamples(sqlite3*,Index*);
void sqlite3DefaultRowEst(Index*);
void sqlite3RegisterLikeFunctions(sqlite3*, int);
int sqlite3IsLikeFunction(sqlite3*,Expr*,int*,char*);
void sqlite3SchemaClear(void *);
Schema *sqlite3SchemaGet(sqlite3 *, Btree *);
int sqlite3SchemaToIndex(sqlite3 *db, Schema *);
KeyInfo *sqlite3KeyInfoAlloc(sqlite3*,int,int);
void sqlite3KeyInfoUnref(KeyInfo*);
KeyInfo *sqlite3KeyInfoRef(KeyInfo*);
KeyInfo *sqlite3KeyInfoOfIndex(Parse*, Index*);
#ifdef SQLITE_DEBUG
int sqlite3KeyInfoIsWriteable(KeyInfo*);
#endif
int sqlite3CreateFunc(sqlite3 *, const char *, int, int, void *,
  void (*)(sqlite3_context*,int,sqlite3_value **),
  void (*)(sqlite3_context*,int,sqlite3_value **), void (*)(sqlite3_context*),
  FuncDestructor *pDestructor
);
void sqlite3OomFault(sqlite3*);
void sqlite3OomClear(sqlite3*);
int sqlite3ApiExit(sqlite3 *db, int);
int sqlite3OpenTempDatabase(Parse *);

void sqlite3StrAccumInit(StrAccum*, sqlite3*, char*, int, int);
void sqlite3StrAccumAppend(StrAccum*,const char*,int);
void sqlite3StrAccumAppendAll(StrAccum*,const char*);
void sqlite3AppendChar(StrAccum*,int,char);
char *sqlite3StrAccumFinish(StrAccum*);
void sqlite3StrAccumReset(StrAccum*);
void sqlite3SelectDestInit(SelectDest*,int,int);
Expr *sqlite3CreateColumnExpr(sqlite3 *, SrcList *, int, int);

void sqlite3BackupRestart(sqlite3_backup *);
void sqlite3BackupUpdate(sqlite3_backup *, Pgno, const u8 *);

#ifndef SQLITE_OMIT_SUBQUERY
int sqlite3ExprCheckIN(Parse*, Expr*);
#else
# define sqlite3ExprCheckIN(x,y) SQLITE_OK
#endif

#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
void sqlite3AnalyzeFunctions(void);
int sqlite3Stat4ProbeSetValue(
    Parse*,Index*,UnpackedRecord**,Expr*,int,int,int*);
int sqlite3Stat4ValueFromExpr(Parse*, Expr*, u8, sqlite3_value**);
void sqlite3Stat4ProbeFree(UnpackedRecord*);
int sqlite3Stat4Column(sqlite3*, const void*, int, int, sqlite3_value**);
char sqlite3IndexColumnAffinity(sqlite3*, Index*, int);
#endif

/*
** The interface to the LEMON-generated parser
*/
#ifndef SQLITE_AMALGAMATION
  void *sqlite3ParserAlloc(void*(*)(u64));
  void sqlite3ParserFree(void*, void(*)(void*));
#endif
void sqlite3Parser(void*, int, Token, Parse*);
#ifdef YYTRACKMAXSTACKDEPTH
  int sqlite3ParserStackPeak(void*);
#endif

void sqlite3AutoLoadExtensions(sqlite3*);
