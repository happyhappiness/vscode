                           Expr*,int, int);
  void sqlite3FinishTrigger(Parse*, TriggerStep*, Token*);
  void sqlite3DropTrigger(Parse*, SrcList*, int);
  void sqlite3DropTriggerPtr(Parse*, Trigger*);
  Trigger *sqlite3TriggersExist(Parse *, Table*, int, ExprList*, int *pMask);
  Trigger *sqlite3TriggerList(Parse *, Table *);
  int sqlite3CodeRowTrigger(Parse*, Trigger *, int, ExprList*, int, Table *,
                            int, int, int, int, u32*, u32*);
  void sqliteViewTriggers(Parse*, Table*, Expr*, int, ExprList*);
  void sqlite3DeleteTriggerStep(sqlite3*, TriggerStep*);
  TriggerStep *sqlite3TriggerSelectStep(sqlite3*,Select*);
  TriggerStep *sqlite3TriggerInsertStep(sqlite3*,Token*, IdList*,
                                        ExprList*,Select*,int);
  TriggerStep *sqlite3TriggerUpdateStep(sqlite3*,Token*,ExprList*, Expr*, int);
  TriggerStep *sqlite3TriggerDeleteStep(sqlite3*,Token*, Expr*);
  void sqlite3DeleteTrigger(sqlite3*, Trigger*);
  void sqlite3UnlinkAndDeleteTrigger(sqlite3*,int,const char*);
#else
# define sqlite3TriggersExist(B,C,D,E,F) 0
# define sqlite3DeleteTrigger(A,B)
# define sqlite3DropTriggerPtr(A,B)
# define sqlite3UnlinkAndDeleteTrigger(A,B,C)
# define sqlite3CodeRowTrigger(A,B,C,D,E,F,G,H,I,J,K,L) 0
# define sqlite3TriggerList(X, Y) 0
#endif

int sqlite3JoinType(Parse*, Token*, Token*, Token*);
void sqlite3CreateForeignKey(Parse*, ExprList*, Token*, ExprList*, int);
void sqlite3DeferForeignKey(Parse*, int);
#ifndef SQLITE_OMIT_AUTHORIZATION
  void sqlite3AuthRead(Parse*,Expr*,Schema*,SrcList*);
  int sqlite3AuthCheck(Parse*,int, const char*, const char*, const char*);
  void sqlite3AuthContextPush(Parse*, AuthContext*, const char*);
  void sqlite3AuthContextPop(AuthContext*);
#else
# define sqlite3AuthRead(a,b,c,d)
# define sqlite3AuthCheck(a,b,c,d,e)    SQLITE_OK
# define sqlite3AuthContextPush(a,b,c)
# define sqlite3AuthContextPop(a)  ((void)(a))
#endif
void sqlite3Attach(Parse*, Expr*, Expr*, Expr*);
void sqlite3Detach(Parse*, Expr*);
int sqlite3BtreeFactory(const sqlite3 *db, const char *zFilename,
                       int omitJournal, int nCache, int flags, Btree **ppBtree);
int sqlite3FixInit(DbFixer*, Parse*, int, const char*, const Token*);
int sqlite3FixSrcList(DbFixer*, SrcList*);
int sqlite3FixSelect(DbFixer*, Select*);
int sqlite3FixExpr(DbFixer*, Expr*);
int sqlite3FixExprList(DbFixer*, ExprList*);
int sqlite3FixTriggerStep(DbFixer*, TriggerStep*);
int sqlite3AtoF(const char *z, double*);
int sqlite3GetInt32(const char *, int*);
int sqlite3FitsIn64Bits(const char *, int);
int sqlite3Utf16ByteLen(const void *pData, int nChar);
int sqlite3Utf8CharLen(const char *pData, int nByte);
int sqlite3Utf8Read(const u8*, const u8**);

/*
** Routines to read and write variable-length integers.  These used to
** be defined locally, but now we use the varint routines in the util.c
** file.  Code should use the MACRO forms below, as the Varint32 versions
** are coded to assume the single byte case is already handled (which 
** the MACRO form does).
*/
int sqlite3PutVarint(unsigned char*, u64);
int sqlite3PutVarint32(unsigned char*, u32);
u8 sqlite3GetVarint(const unsigned char *, u64 *);
u8 sqlite3GetVarint32(const unsigned char *, u32 *);
int sqlite3VarintLen(u64 v);

/*
** The header of a record consists of a sequence variable-length integers.
** These integers are almost always small and are encoded as a single byte.
** The following macros take advantage this fact to provide a fast encode
** and decode of the integers in a record header.  It is faster for the common
** case where the integer is a single byte.  It is a little slower when the
** integer is two or more bytes.  But overall it is faster.
**
** The following expressions are equivalent:
**
**     x = sqlite3GetVarint32( A, &B );
**     x = sqlite3PutVarint32( A, B );
**
**     x = getVarint32( A, B );
**     x = putVarint32( A, B );
**
*/
#define getVarint32(A,B)  (u8)((*(A)<(u8)0x80) ? ((B) = (u32)*(A)),1 : sqlite3GetVarint32((A), (u32 *)&(B)))
#define putVarint32(A,B)  (u8)(((u32)(B)<(u32)0x80) ? (*(A) = (unsigned char)(B)),1 : sqlite3PutVarint32((A), (B)))
#define getVarint    sqlite3GetVarint
#define putVarint    sqlite3PutVarint


void sqlite3IndexAffinityStr(Vdbe *, Index *);
void sqlite3TableAffinityStr(Vdbe *, Table *);
char sqlite3CompareAffinity(Expr *pExpr, char aff2);
int sqlite3IndexAffinityOk(Expr *pExpr, char idx_affinity);
char sqlite3ExprAffinity(Expr *pExpr);
int sqlite3Atoi64(const char*, i64*);
void sqlite3Error(sqlite3*, int, const char*,...);
void *sqlite3HexToBlob(sqlite3*, const char *z, int n);
int sqlite3TwoPartName(Parse *, Token *, Token *, Token **);
const char *sqlite3ErrStr(int);
int sqlite3ReadSchema(Parse *pParse);
CollSeq *sqlite3FindCollSeq(sqlite3*,u8 enc, const char*,int);
CollSeq *sqlite3LocateCollSeq(Parse *pParse, const char*zName);
CollSeq *sqlite3ExprCollSeq(Parse *pParse, Expr *pExpr);
Expr *sqlite3ExprSetColl(Parse *pParse, Expr *, Token *);
int sqlite3CheckCollSeq(Parse *, CollSeq *);
int sqlite3CheckObjectName(Parse *, const char *);
void sqlite3VdbeSetChanges(sqlite3 *, int);

const void *sqlite3ValueText(sqlite3_value*, u8);
int sqlite3ValueBytes(sqlite3_value*, u8);
void sqlite3ValueSetStr(sqlite3_value*, int, const void *,u8, 
                        void(*)(void*));
void sqlite3ValueFree(sqlite3_value*);
sqlite3_value *sqlite3ValueNew(sqlite3 *);
char *sqlite3Utf16to8(sqlite3 *, const void*, int);
int sqlite3ValueFromExpr(sqlite3 *, Expr *, u8, u8, sqlite3_value **);
void sqlite3ValueApplyAffinity(sqlite3_value *, u8, u8);
#ifndef SQLITE_AMALGAMATION
extern const unsigned char sqlite3UpperToLower[];
extern const unsigned char sqlite3CtypeMap[];
extern SQLITE_WSD struct Sqlite3Config sqlite3Config;
extern SQLITE_WSD FuncDefHash sqlite3GlobalFunctions;
extern int sqlite3PendingByte;
#endif
void sqlite3RootPageMoved(Db*, int, int);
void sqlite3Reindex(Parse*, Token*, Token*);
void sqlite3AlterFunctions(sqlite3*);
void sqlite3AlterRenameTable(Parse*, SrcList*, Token*);
int sqlite3GetToken(const unsigned char *, int *);
void sqlite3NestedParse(Parse*, const char*, ...);
void sqlite3ExpirePreparedStatements(sqlite3*);
void sqlite3CodeSubselect(Parse *, Expr *, int, int);
void sqlite3SelectPrep(Parse*, Select*, NameContext*);
int sqlite3ResolveExprNames(NameContext*, Expr*);
void sqlite3ResolveSelectNames(Parse*, Select*, NameContext*);
int sqlite3ResolveOrderGroupBy(Parse*, Select*, ExprList*, const char*);
void sqlite3ColumnDefault(Vdbe *, Table *, int);
void sqlite3AlterFinishAddColumn(Parse *, Token *);
void sqlite3AlterBeginAddColumn(Parse *, SrcList *);
CollSeq *sqlite3GetCollSeq(sqlite3*, CollSeq *, const char*);
char sqlite3AffinityType(const char*);
void sqlite3Analyze(Parse*, Token*, Token*);
int sqlite3InvokeBusyHandler(BusyHandler*);
int sqlite3FindDb(sqlite3*, Token*);
int sqlite3FindDbName(sqlite3 *, const char *);
int sqlite3AnalysisLoad(sqlite3*,int iDB);
void sqlite3DefaultRowEst(Index*);
void sqlite3RegisterLikeFunctions(sqlite3*, int);
int sqlite3IsLikeFunction(sqlite3*,Expr*,int*,char*);
void sqlite3MinimumFileFormat(Parse*, int, int);
void sqlite3SchemaFree(void *);
Schema *sqlite3SchemaGet(sqlite3 *, Btree *);
int sqlite3SchemaToIndex(sqlite3 *db, Schema *);
KeyInfo *sqlite3IndexKeyinfo(Parse *, Index *);
int sqlite3CreateFunc(sqlite3 *, const char *, int, int, void *, 
  void (*)(sqlite3_context*,int,sqlite3_value **),
  void (*)(sqlite3_context*,int,sqlite3_value **), void (*)(sqlite3_context*));
int sqlite3ApiExit(sqlite3 *db, int);
int sqlite3OpenTempDatabase(Parse *);

void sqlite3StrAccumInit(StrAccum*, char*, int, int);
void sqlite3StrAccumAppend(StrAccum*,const char*,int);
char *sqlite3StrAccumFinish(StrAccum*);
void sqlite3StrAccumReset(StrAccum*);
void sqlite3SelectDestInit(SelectDest*,int,int);

void sqlite3BackupRestart(sqlite3_backup *);
void sqlite3BackupUpdate(sqlite3_backup *, Pgno, const u8 *);

/*
** The interface to the LEMON-generated parser
*/
void *sqlite3ParserAlloc(void*(*)(size_t));
void sqlite3ParserFree(void*, void(*)(void*));
void sqlite3Parser(void*, int, Token, Parse*);
#ifdef YYTRACKMAXSTACKDEPTH
  int sqlite3ParserStackPeak(void*);
#endif

void sqlite3AutoLoadExtensions(sqlite3*);
