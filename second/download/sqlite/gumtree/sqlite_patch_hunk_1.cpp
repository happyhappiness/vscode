 ** write an empty doclist (varint(docid) varint(POS_END)), for updates
 ** we simply write the new doclist.  Segment merges overwrite older
 ** data for a particular docid with newer data, so deletes or updates
 ** will eventually overtake the earlier data and knock it out.  The
 ** query logic likewise merges doclists so that newer data knocks out
 ** older data.
+**
+** TODO(shess) Provide a VACUUM type operation to clear out all
+** deletions and duplications.  This would basically be a forced merge
+** into a single segment.
 */
 
-#include "fts3Int.h"
 #if !defined(SQLITE_CORE) || defined(SQLITE_ENABLE_FTS3)
 
 #if defined(SQLITE_ENABLE_FTS3) && !defined(SQLITE_CORE)
 # define SQLITE_CORE 1
 #endif
 
 #include <assert.h>
 #include <stdlib.h>
-#include <stddef.h>
 #include <stdio.h>
 #include <string.h>
-#include <stdarg.h>
+#include <ctype.h>
 
 #include "fts3.h"
+#include "fts3_expr.h"
+#include "fts3_hash.h"
+#include "fts3_tokenizer.h"
 #ifndef SQLITE_CORE 
 # include "sqlite3ext.h"
   SQLITE_EXTENSION_INIT1
 #endif
 
-static int fts3EvalNext(Fts3Cursor *pCsr);
-static int fts3EvalStart(Fts3Cursor *pCsr);
-static int fts3TermSegReaderCursor(
-    Fts3Cursor *, const char *, int, int, Fts3MultiSegReader **);
-
-#ifndef SQLITE_AMALGAMATION
-# if defined(SQLITE_DEBUG)
-int sqlite3Fts3Always(int b) { assert( b ); return b; }
-int sqlite3Fts3Never(int b)  { assert( !b ); return b; }
-# endif
+
+/* TODO(shess) MAN, this thing needs some refactoring.  At minimum, it
+** would be nice to order the file better, perhaps something along the
+** lines of:
+**
+**  - utility functions
+**  - table setup functions
+**  - table update functions
+**  - table query functions
+**
+** Put the query functions last because they're likely to reference
+** typedefs or functions from the table update section.
+*/
+
+#if 0
+# define FTSTRACE(A)  printf A; fflush(stdout)
+#else
+# define FTSTRACE(A)
 #endif
 
-/* 
-** Write a 64-bit variable-length integer to memory starting at p[0].
-** The length of data written will be between 1 and FTS3_VARINT_MAX bytes.
-** The number of bytes written is returned.
+/* It is not safe to call isspace(), tolower(), or isalnum() on
+** hi-bit-set characters.  This is the same solution used in the
+** tokenizer.
+*/
+/* TODO(shess) The snippet-generation code should be using the
+** tokenizer-generated tokens rather than doing its own local
+** tokenization.
+*/
+/* TODO(shess) Is __isascii() a portable version of (c&0x80)==0? */
+static int safe_isspace(char c){
+  return (c&0x80)==0 ? isspace(c) : 0;
+}
+static int safe_tolower(char c){
+  return (c&0x80)==0 ? tolower(c) : c;
+}
+static int safe_isalnum(char c){
+  return (c&0x80)==0 ? isalnum(c) : 0;
+}
+
+typedef enum DocListType {
+  DL_DOCIDS,              /* docids only */
+  DL_POSITIONS,           /* docids + positions */
+  DL_POSITIONS_OFFSETS    /* docids + positions + offsets */
+} DocListType;
+
+/*
+** By default, only positions and not offsets are stored in the doclists.
+** To change this so that offsets are stored too, compile with
+**
+**          -DDL_DEFAULT=DL_POSITIONS_OFFSETS
+**
+** If DL_DEFAULT is set to DL_DOCIDS, your table can only be inserted
+** into (no deletes or updates).
+*/
+#ifndef DL_DEFAULT
+# define DL_DEFAULT DL_POSITIONS
+#endif
+
+enum {
+  POS_END = 0,        /* end of this position list */
+  POS_COLUMN,         /* followed by new column number */
+  POS_BASE
+};
+
+/* MERGE_COUNT controls how often we merge segments (see comment at
+** top of file).
+*/
+#define MERGE_COUNT 16
+
+/* utility functions */
+
+/* CLEAR() and SCRAMBLE() abstract memset() on a pointer to a single
+** record to prevent errors of the form:
+**
+** my_function(SomeType *b){
+**   memset(b, '\0', sizeof(b));  // sizeof(b)!=sizeof(*b)
+** }
 */
-int sqlite3Fts3PutVarint(char *p, sqlite_int64 v){
+/* TODO(shess) Obvious candidates for a header file. */
+#define CLEAR(b) memset(b, '\0', sizeof(*(b)))
+
+#ifndef NDEBUG
+#  define SCRAMBLE(b) memset(b, 0x55, sizeof(*(b)))
+#else
+#  define SCRAMBLE(b)
+#endif
+
+/* We may need up to VARINT_MAX bytes to store an encoded 64-bit integer. */
+#define VARINT_MAX 10
+
+/* Write a 64-bit variable-length integer to memory starting at p[0].
+ * The length of data written will be between 1 and VARINT_MAX bytes.
+ * The number of bytes written is returned. */
+static int fts3PutVarint(char *p, sqlite_int64 v){
   unsigned char *q = (unsigned char *) p;
   sqlite_uint64 vu = v;
   do{
     *q++ = (unsigned char) ((vu & 0x7f) | 0x80);
     vu >>= 7;
   }while( vu!=0 );
   q[-1] &= 0x7f;  /* turn off high bit in final byte */
-  assert( q - (unsigned char *)p <= FTS3_VARINT_MAX );
+  assert( q - (unsigned char *)p <= VARINT_MAX );
   return (int) (q - (unsigned char *)p);
 }
 
-#define GETVARINT_STEP(v, ptr, shift, mask1, mask2, var, ret) \
-  v = (v & mask1) | ( (*ptr++) << shift );                    \
-  if( (v & mask2)==0 ){ var = v; return ret; }
-#define GETVARINT_INIT(v, ptr, shift, mask1, mask2, var, ret) \
-  v = (*ptr++);                                               \
-  if( (v & mask2)==0 ){ var = v; return ret; }
+/* Read a 64-bit variable-length integer from memory starting at p[0].
+ * Return the number of bytes read, or 0 on error.
+ * The value is stored in *v. */
+static int fts3GetVarint(const char *p, sqlite_int64 *v){
+  const unsigned char *q = (const unsigned char *) p;
+  sqlite_uint64 x = 0, y = 1;
+  while( (*q & 0x80) == 0x80 ){
+    x += y * (*q++ & 0x7f);
+    y <<= 7;
+    if( q - (unsigned char *)p >= VARINT_MAX ){  /* bad data */
+      assert( 0 );
+      return 0;
+    }
+  }
+  x += y * (*q++);
+  *v = (sqlite_int64) x;
+  return (int) (q - (unsigned char *)p);
+}
 
-/* 
-** Read a 64-bit variable-length integer from memory starting at p[0].
-** Return the number of bytes read, or 0 on error.
-** The value is stored in *v.
-*/
-int sqlite3Fts3GetVarint(const char *pBuf, sqlite_int64 *v){
-  const unsigned char *p = (const unsigned char*)pBuf;
-  const unsigned char *pStart = p;
-  u32 a;
-  u64 b;
-  int shift;
-
-  GETVARINT_INIT(a, p, 0,  0x00,     0x80, *v, 1);
-  GETVARINT_STEP(a, p, 7,  0x7F,     0x4000, *v, 2);
-  GETVARINT_STEP(a, p, 14, 0x3FFF,   0x200000, *v, 3);
-  GETVARINT_STEP(a, p, 21, 0x1FFFFF, 0x10000000, *v, 4);
-  b = (a & 0x0FFFFFFF );
-
-  for(shift=28; shift<=63; shift+=7){
-    u64 c = *p++;
-    b += (c&0x7F) << shift;
-    if( (c & 0x80)==0 ) break;
+static int fts3GetVarint32(const char *p, int *pi){
+ sqlite_int64 i;
+ int ret = fts3GetVarint(p, &i);
+ *pi = (int) i;
+ assert( *pi==i );
+ return ret;
+}
+
+/*******************************************************************/
+/* DataBuffer is used to collect data into a buffer in piecemeal
+** fashion.  It implements the usual distinction between amount of
+** data currently stored (nData) and buffer capacity (nCapacity).
+**
+** dataBufferInit - create a buffer with given initial capacity.
+** dataBufferReset - forget buffer's data, retaining capacity.
+** dataBufferDestroy - free buffer's data.
+** dataBufferSwap - swap contents of two buffers.
+** dataBufferExpand - expand capacity without adding data.
+** dataBufferAppend - append data.
+** dataBufferAppend2 - append two pieces of data at once.
+** dataBufferReplace - replace buffer's data.
+*/
+typedef struct DataBuffer {
+  char *pData;          /* Pointer to malloc'ed buffer. */
+  int nCapacity;        /* Size of pData buffer. */
+  int nData;            /* End of data loaded into pData. */
+} DataBuffer;
+
+static void dataBufferInit(DataBuffer *pBuffer, int nCapacity){
+  assert( nCapacity>=0 );
+  pBuffer->nData = 0;
+  pBuffer->nCapacity = nCapacity;
+  pBuffer->pData = nCapacity==0 ? NULL : sqlite3_malloc(nCapacity);
+}
+static void dataBufferReset(DataBuffer *pBuffer){
+  pBuffer->nData = 0;
+}
+static void dataBufferDestroy(DataBuffer *pBuffer){
+  if( pBuffer->pData!=NULL ) sqlite3_free(pBuffer->pData);
+  SCRAMBLE(pBuffer);
+}
+static void dataBufferSwap(DataBuffer *pBuffer1, DataBuffer *pBuffer2){
+  DataBuffer tmp = *pBuffer1;
+  *pBuffer1 = *pBuffer2;
+  *pBuffer2 = tmp;
+}
+static void dataBufferExpand(DataBuffer *pBuffer, int nAddCapacity){
+  assert( nAddCapacity>0 );
+  /* TODO(shess) Consider expanding more aggressively.  Note that the
+  ** underlying malloc implementation may take care of such things for
+  ** us already.
+  */
+  if( pBuffer->nData+nAddCapacity>pBuffer->nCapacity ){
+    pBuffer->nCapacity = pBuffer->nData+nAddCapacity;
+    pBuffer->pData = sqlite3_realloc(pBuffer->pData, pBuffer->nCapacity);
   }
-  *v = b;
-  return (int)(p - pStart);
+}
+static void dataBufferAppend(DataBuffer *pBuffer,
+                             const char *pSource, int nSource){
+  assert( nSource>0 && pSource!=NULL );
+  dataBufferExpand(pBuffer, nSource);
+  memcpy(pBuffer->pData+pBuffer->nData, pSource, nSource);
+  pBuffer->nData += nSource;
+}
+static void dataBufferAppend2(DataBuffer *pBuffer,
+                              const char *pSource1, int nSource1,
+                              const char *pSource2, int nSource2){
+  assert( nSource1>0 && pSource1!=NULL );
+  assert( nSource2>0 && pSource2!=NULL );
+  dataBufferExpand(pBuffer, nSource1+nSource2);
+  memcpy(pBuffer->pData+pBuffer->nData, pSource1, nSource1);
+  memcpy(pBuffer->pData+pBuffer->nData+nSource1, pSource2, nSource2);
+  pBuffer->nData += nSource1+nSource2;
+}
+static void dataBufferReplace(DataBuffer *pBuffer,
+                              const char *pSource, int nSource){
+  dataBufferReset(pBuffer);
+  dataBufferAppend(pBuffer, pSource, nSource);
 }
 
-/*
-** Similar to sqlite3Fts3GetVarint(), except that the output is truncated to 
-** a non-negative 32-bit integer before it is returned.
-*/
-int sqlite3Fts3GetVarint32(const char *p, int *pi){
-  u32 a;
+/* StringBuffer is a null-terminated version of DataBuffer. */
+typedef struct StringBuffer {
+  DataBuffer b;            /* Includes null terminator. */
+} StringBuffer;
 
-#ifndef fts3GetVarint32
-  GETVARINT_INIT(a, p, 0,  0x00,     0x80, *pi, 1);
-#else
-  a = (*p++);
-  assert( a & 0x80 );
-#endif
+static void initStringBuffer(StringBuffer *sb){
+  dataBufferInit(&sb->b, 100);
+  dataBufferReplace(&sb->b, "", 1);
+}
+static int stringBufferLength(StringBuffer *sb){
+  return sb->b.nData-1;
+}
+static char *stringBufferData(StringBuffer *sb){
+  return sb->b.pData;
+}
+static void stringBufferDestroy(StringBuffer *sb){
+  dataBufferDestroy(&sb->b);
+}
 
-  GETVARINT_STEP(a, p, 7,  0x7F,     0x4000, *pi, 2);
-  GETVARINT_STEP(a, p, 14, 0x3FFF,   0x200000, *pi, 3);
-  GETVARINT_STEP(a, p, 21, 0x1FFFFF, 0x10000000, *pi, 4);
-  a = (a & 0x0FFFFFFF );
-  *pi = (int)(a | ((u32)(*p & 0x07) << 28));
-  assert( 0==(a & 0x80000000) );
-  assert( *pi>=0 );
-  return 5;
+static void nappend(StringBuffer *sb, const char *zFrom, int nFrom){
+  assert( sb->b.nData>0 );
+  if( nFrom>0 ){
+    sb->b.nData--;
+    dataBufferAppend2(&sb->b, zFrom, nFrom, "", 1);
+  }
+}
+static void append(StringBuffer *sb, const char *zFrom){
+  nappend(sb, zFrom, strlen(zFrom));
 }
 
-/*
-** Return the number of bytes required to encode v as a varint
+/* Append a list of strings separated by commas. */
+static void appendList(StringBuffer *sb, int nString, char **azString){
+  int i;
+  for(i=0; i<nString; ++i){
+    if( i>0 ) append(sb, ", ");
+    append(sb, azString[i]);
+  }
+}
+
+static int endsInWhiteSpace(StringBuffer *p){
+  return stringBufferLength(p)>0 &&
+    safe_isspace(stringBufferData(p)[stringBufferLength(p)-1]);
+}
+
+/* If the StringBuffer ends in something other than white space, add a
+** single space character to the end.
 */
-int sqlite3Fts3VarintLen(sqlite3_uint64 v){
-  int i = 0;
-  do{
-    i++;
-    v >>= 7;
-  }while( v!=0 );
-  return i;
+static void appendWhiteSpace(StringBuffer *p){
+  if( stringBufferLength(p)==0 ) return;
+  if( !endsInWhiteSpace(p) ) append(p, " ");
 }
 
-/*
-** Convert an SQL-style quoted string into a normal string by removing
-** the quote characters.  The conversion is done in-place.  If the
-** input does not begin with a quote character, then this routine
-** is a no-op.
+/* Remove white space from the end of the StringBuffer */
+static void trimWhiteSpace(StringBuffer *p){
+  while( endsInWhiteSpace(p) ){
+    p->b.pData[--p->b.nData-1] = '\0';
+  }
+}
+
+/*******************************************************************/
+/* DLReader is used to read document elements from a doclist.  The
+** current docid is cached, so dlrDocid() is fast.  DLReader does not
+** own the doclist buffer.
 **
-** Examples:
+** dlrAtEnd - true if there's no more data to read.
+** dlrDocid - docid of current document.
+** dlrDocData - doclist data for current document (including docid).
+** dlrDocDataBytes - length of same.
+** dlrAllDataBytes - length of all remaining data.
+** dlrPosData - position data for current document.
+** dlrPosDataLen - length of pos data for current document (incl POS_END).
+** dlrStep - step to current document.
+** dlrInit - initial for doclist of given type against given data.
+** dlrDestroy - clean up.
 **
-**     "abc"   becomes   abc
-**     'xyz'   becomes   xyz
-**     [pqr]   becomes   pqr
-**     `mno`   becomes   mno
+** Expected usage is something like:
 **
+**   DLReader reader;
+**   dlrInit(&reader, pData, nData);
+**   while( !dlrAtEnd(&reader) ){
+**     // calls to dlrDocid() and kin.
+**     dlrStep(&reader);
+**   }
+**   dlrDestroy(&reader);
 */
-void sqlite3Fts3Dequote(char *z){
-  char quote;                     /* Quote character (if any ) */
-
-  quote = z[0];
-  if( quote=='[' || quote=='\'' || quote=='"' || quote=='`' ){
-    int iIn = 1;                  /* Index of next byte to read from input */
-    int iOut = 0;                 /* Index of next byte to write to output */
-
-    /* If the first byte was a '[', then the close-quote character is a ']' */
-    if( quote=='[' ) quote = ']';  
-
-    while( z[iIn] ){
-      if( z[iIn]==quote ){
-        if( z[iIn+1]!=quote ) break;
-        z[iOut++] = quote;
-        iIn += 2;
-      }else{
-        z[iOut++] = z[iIn++];
+typedef struct DLReader {
+  DocListType iType;
+  const char *pData;
+  int nData;
+
+  sqlite_int64 iDocid;
+  int nElement;
+} DLReader;
+
+static int dlrAtEnd(DLReader *pReader){
+  assert( pReader->nData>=0 );
+  return pReader->nData==0;
+}
+static sqlite_int64 dlrDocid(DLReader *pReader){
+  assert( !dlrAtEnd(pReader) );
+  return pReader->iDocid;
+}
+static const char *dlrDocData(DLReader *pReader){
+  assert( !dlrAtEnd(pReader) );
+  return pReader->pData;
+}
+static int dlrDocDataBytes(DLReader *pReader){
+  assert( !dlrAtEnd(pReader) );
+  return pReader->nElement;
+}
+static int dlrAllDataBytes(DLReader *pReader){
+  assert( !dlrAtEnd(pReader) );
+  return pReader->nData;
+}
+/* TODO(shess) Consider adding a field to track iDocid varint length
+** to make these two functions faster.  This might matter (a tiny bit)
+** for queries.
+*/
+static const char *dlrPosData(DLReader *pReader){
+  sqlite_int64 iDummy;
+  int n = fts3GetVarint(pReader->pData, &iDummy);
+  assert( !dlrAtEnd(pReader) );
+  return pReader->pData+n;
+}
+static int dlrPosDataLen(DLReader *pReader){
+  sqlite_int64 iDummy;
+  int n = fts3GetVarint(pReader->pData, &iDummy);
+  assert( !dlrAtEnd(pReader) );
+  return pReader->nElement-n;
+}
+static void dlrStep(DLReader *pReader){
+  assert( !dlrAtEnd(pReader) );
+
+  /* Skip past current doclist element. */
+  assert( pReader->nElement<=pReader->nData );
+  pReader->pData += pReader->nElement;
+  pReader->nData -= pReader->nElement;
+
+  /* If there is more data, read the next doclist element. */
+  if( pReader->nData!=0 ){
+    sqlite_int64 iDocidDelta;
+    int iDummy, n = fts3GetVarint(pReader->pData, &iDocidDelta);
+    pReader->iDocid += iDocidDelta;
+    if( pReader->iType>=DL_POSITIONS ){
+      assert( n<pReader->nData );
+      while( 1 ){
+        n += fts3GetVarint32(pReader->pData+n, &iDummy);
+        assert( n<=pReader->nData );
+        if( iDummy==POS_END ) break;
+        if( iDummy==POS_COLUMN ){
+          n += fts3GetVarint32(pReader->pData+n, &iDummy);
+          assert( n<pReader->nData );
+        }else if( pReader->iType==DL_POSITIONS_OFFSETS ){
+          n += fts3GetVarint32(pReader->pData+n, &iDummy);
+          n += fts3GetVarint32(pReader->pData+n, &iDummy);
+          assert( n<pReader->nData );
+        }
+      }
+    }
+    pReader->nElement = n;
+    assert( pReader->nElement<=pReader->nData );
+  }
+}
+static void dlrInit(DLReader *pReader, DocListType iType,
+                    const char *pData, int nData){
+  assert( pData!=NULL && nData!=0 );
+  pReader->iType = iType;
+  pReader->pData = pData;
+  pReader->nData = nData;
+  pReader->nElement = 0;
+  pReader->iDocid = 0;
+
+  /* Load the first element's data.  There must be a first element. */
+  dlrStep(pReader);
+}
+static void dlrDestroy(DLReader *pReader){
+  SCRAMBLE(pReader);
+}
+
+#ifndef NDEBUG
+/* Verify that the doclist can be validly decoded.  Also returns the
+** last docid found because it is convenient in other assertions for
+** DLWriter.
+*/
+static void docListValidate(DocListType iType, const char *pData, int nData,
+                            sqlite_int64 *pLastDocid){
+  sqlite_int64 iPrevDocid = 0;
+  assert( nData>0 );
+  assert( pData!=0 );
+  assert( pData+nData>pData );
+  while( nData!=0 ){
+    sqlite_int64 iDocidDelta;
+    int n = fts3GetVarint(pData, &iDocidDelta);
+    iPrevDocid += iDocidDelta;
+    if( iType>DL_DOCIDS ){
+      int iDummy;
+      while( 1 ){
+        n += fts3GetVarint32(pData+n, &iDummy);
+        if( iDummy==POS_END ) break;
+        if( iDummy==POS_COLUMN ){
+          n += fts3GetVarint32(pData+n, &iDummy);
+        }else if( iType>DL_POSITIONS ){
+          n += fts3GetVarint32(pData+n, &iDummy);
+          n += fts3GetVarint32(pData+n, &iDummy);
+        }
+        assert( n<=nData );
       }
     }
-    z[iOut] = '\0';
+    assert( n<=nData );
+    pData += n;
+    nData -= n;
   }
+  if( pLastDocid ) *pLastDocid = iPrevDocid;
 }
+#define ASSERT_VALID_DOCLIST(i, p, n, o) docListValidate(i, p, n, o)
+#else
+#define ASSERT_VALID_DOCLIST(i, p, n, o) assert( 1 )
+#endif
 
-/*
-** Read a single varint from the doclist at *pp and advance *pp to point
-** to the first byte past the end of the varint.  Add the value of the varint
-** to *pVal.
-*/
-static void fts3GetDeltaVarint(char **pp, sqlite3_int64 *pVal){
-  sqlite3_int64 iVal;
-  *pp += sqlite3Fts3GetVarint(*pp, &iVal);
-  *pVal += iVal;
+/*******************************************************************/
+/* DLWriter is used to write doclist data to a DataBuffer.  DLWriter
+** always appends to the buffer and does not own it.
+**
+** dlwInit - initialize to write a given type doclistto a buffer.
+** dlwDestroy - clear the writer's memory.  Does not free buffer.
+** dlwAppend - append raw doclist data to buffer.
+** dlwCopy - copy next doclist from reader to writer.
+** dlwAdd - construct doclist element and append to buffer.
+**    Only apply dlwAdd() to DL_DOCIDS doclists (else use PLWriter).
+*/
+typedef struct DLWriter {
+  DocListType iType;
+  DataBuffer *b;
+  sqlite_int64 iPrevDocid;
+#ifndef NDEBUG
+  int has_iPrevDocid;
+#endif
+} DLWriter;
+
+static void dlwInit(DLWriter *pWriter, DocListType iType, DataBuffer *b){
+  pWriter->b = b;
+  pWriter->iType = iType;
+  pWriter->iPrevDocid = 0;
+#ifndef NDEBUG
+  pWriter->has_iPrevDocid = 0;
+#endif
 }
+static void dlwDestroy(DLWriter *pWriter){
+  SCRAMBLE(pWriter);
+}
+/* iFirstDocid is the first docid in the doclist in pData.  It is
+** needed because pData may point within a larger doclist, in which
+** case the first item would be delta-encoded.
+**
+** iLastDocid is the final docid in the doclist in pData.  It is
+** needed to create the new iPrevDocid for future delta-encoding.  The
+** code could decode the passed doclist to recreate iLastDocid, but
+** the only current user (docListMerge) already has decoded this
+** information.
+*/
+/* TODO(shess) This has become just a helper for docListMerge.
+** Consider a refactor to make this cleaner.
+*/
+static void dlwAppend(DLWriter *pWriter,
+                      const char *pData, int nData,
+                      sqlite_int64 iFirstDocid, sqlite_int64 iLastDocid){
+  sqlite_int64 iDocid = 0;
+  char c[VARINT_MAX];
+  int nFirstOld, nFirstNew;     /* Old and new varint len of first docid. */
+#ifndef NDEBUG
+  sqlite_int64 iLastDocidDelta;
+#endif
 
-/*
-** When this function is called, *pp points to the first byte following a
-** varint that is part of a doclist (or position-list, or any other list
-** of varints). This function moves *pp to point to the start of that varint,
-** and sets *pVal by the varint value.
-**
-** Argument pStart points to the first byte of the doclist that the
-** varint is part of.
-*/
-static void fts3GetReverseVarint(
-  char **pp, 
-  char *pStart, 
-  sqlite3_int64 *pVal
-){
-  sqlite3_int64 iVal;
-  char *p;
+  /* Recode the initial docid as delta from iPrevDocid. */
+  nFirstOld = fts3GetVarint(pData, &iDocid);
+  assert( nFirstOld<nData || (nFirstOld==nData && pWriter->iType==DL_DOCIDS) );
+  nFirstNew = fts3PutVarint(c, iFirstDocid-pWriter->iPrevDocid);
+
+  /* Verify that the incoming doclist is valid AND that it ends with
+  ** the expected docid.  This is essential because we'll trust this
+  ** docid in future delta-encoding.
+  */
+  ASSERT_VALID_DOCLIST(pWriter->iType, pData, nData, &iLastDocidDelta);
+  assert( iLastDocid==iFirstDocid-iDocid+iLastDocidDelta );
+
+  /* Append recoded initial docid and everything else.  Rest of docids
+  ** should have been delta-encoded from previous initial docid.
+  */
+  if( nFirstOld<nData ){
+    dataBufferAppend2(pWriter->b, c, nFirstNew,
+                      pData+nFirstOld, nData-nFirstOld);
+  }else{
+    dataBufferAppend(pWriter->b, c, nFirstNew);
+  }
+  pWriter->iPrevDocid = iLastDocid;
+}
+static void dlwCopy(DLWriter *pWriter, DLReader *pReader){
+  dlwAppend(pWriter, dlrDocData(pReader), dlrDocDataBytes(pReader),
+            dlrDocid(pReader), dlrDocid(pReader));
+}
+static void dlwAdd(DLWriter *pWriter, sqlite_int64 iDocid){
+  char c[VARINT_MAX];
+  int n = fts3PutVarint(c, iDocid-pWriter->iPrevDocid);
+
+  /* Docids must ascend. */
+  assert( !pWriter->has_iPrevDocid || iDocid>pWriter->iPrevDocid );
+  assert( pWriter->iType==DL_DOCIDS );
+
+  dataBufferAppend(pWriter->b, c, n);
+  pWriter->iPrevDocid = iDocid;
+#ifndef NDEBUG
+  pWriter->has_iPrevDocid = 1;
+#endif
+}
 
-  /* Pointer p now points at the first byte past the varint we are 
-  ** interested in. So, unless the doclist is corrupt, the 0x80 bit is
-  ** clear on character p[-1]. */
-  for(p = (*pp)-2; p>=pStart && *p&0x80; p--);
-  p++;
-  *pp = p;
+/*******************************************************************/
+/* PLReader is used to read data from a document's position list.  As
+** the caller steps through the list, data is cached so that varints
+** only need to be decoded once.
+**
+** plrInit, plrDestroy - create/destroy a reader.
+** plrColumn, plrPosition, plrStartOffset, plrEndOffset - accessors
+** plrAtEnd - at end of stream, only call plrDestroy once true.
+** plrStep - step to the next element.
+*/
+typedef struct PLReader {
+  /* These refer to the next position's data.  nData will reach 0 when
+  ** reading the last position, so plrStep() signals EOF by setting
+  ** pData to NULL.
+  */
+  const char *pData;
+  int nData;
 
-  sqlite3Fts3GetVarint(p, &iVal);
-  *pVal = iVal;
+  DocListType iType;
+  int iColumn;         /* the last column read */
+  int iPosition;       /* the last position read */
+  int iStartOffset;    /* the last start offset read */
+  int iEndOffset;      /* the last end offset read */
+} PLReader;
+
+static int plrAtEnd(PLReader *pReader){
+  return pReader->pData==NULL;
+}
+static int plrColumn(PLReader *pReader){
+  assert( !plrAtEnd(pReader) );
+  return pReader->iColumn;
+}
+static int plrPosition(PLReader *pReader){
+  assert( !plrAtEnd(pReader) );
+  return pReader->iPosition;
+}
+static int plrStartOffset(PLReader *pReader){
+  assert( !plrAtEnd(pReader) );
+  return pReader->iStartOffset;
+}
+static int plrEndOffset(PLReader *pReader){
+  assert( !plrAtEnd(pReader) );
+  return pReader->iEndOffset;
 }
+static void plrStep(PLReader *pReader){
+  int i, n;
 
-/*
-** The xDisconnect() virtual table method.
-*/
-static int fts3DisconnectMethod(sqlite3_vtab *pVtab){
-  Fts3Table *p = (Fts3Table *)pVtab;
-  int i;
+  assert( !plrAtEnd(pReader) );
 
-  assert( p->nPendingData==0 );
-  assert( p->pSegments==0 );
+  if( pReader->nData==0 ){
+    pReader->pData = NULL;
+    return;
+  }
 
-  /* Free any prepared statements held */
-  sqlite3_finalize(p->pSeekStmt);
-  for(i=0; i<SizeofArray(p->aStmt); i++){
-    sqlite3_finalize(p->aStmt[i]);
-  }
-  sqlite3_free(p->zSegmentsTbl);
-  sqlite3_free(p->zReadExprlist);
-  sqlite3_free(p->zWriteExprlist);
-  sqlite3_free(p->zContentTbl);
-  sqlite3_free(p->zLanguageid);
+  n = fts3GetVarint32(pReader->pData, &i);
+  if( i==POS_COLUMN ){
+    n += fts3GetVarint32(pReader->pData+n, &pReader->iColumn);
+    pReader->iPosition = 0;
+    pReader->iStartOffset = 0;
+    n += fts3GetVarint32(pReader->pData+n, &i);
+  }
+  /* Should never see adjacent column changes. */
+  assert( i!=POS_COLUMN );
+
+  if( i==POS_END ){
+    pReader->nData = 0;
+    pReader->pData = NULL;
+    return;
+  }
 
-  /* Invoke the tokenizer destructor to free the tokenizer. */
-  p->pTokenizer->pModule->xDestroy(p->pTokenizer);
+  pReader->iPosition += i-POS_BASE;
+  if( pReader->iType==DL_POSITIONS_OFFSETS ){
+    n += fts3GetVarint32(pReader->pData+n, &i);
+    pReader->iStartOffset += i;
+    n += fts3GetVarint32(pReader->pData+n, &i);
+    pReader->iEndOffset = pReader->iStartOffset+i;
+  }
+  assert( n<=pReader->nData );
+  pReader->pData += n;
+  pReader->nData -= n;
+}
+
+static void plrInit(PLReader *pReader, DLReader *pDLReader){
+  pReader->pData = dlrPosData(pDLReader);
+  pReader->nData = dlrPosDataLen(pDLReader);
+  pReader->iType = pDLReader->iType;
+  pReader->iColumn = 0;
+  pReader->iPosition = 0;
+  pReader->iStartOffset = 0;
+  pReader->iEndOffset = 0;
+  plrStep(pReader);
+}
+static void plrDestroy(PLReader *pReader){
+  SCRAMBLE(pReader);
+}
+
+/*******************************************************************/
+/* PLWriter is used in constructing a document's position list.  As a
+** convenience, if iType is DL_DOCIDS, PLWriter becomes a no-op.
+** PLWriter writes to the associated DLWriter's buffer.
+**
+** plwInit - init for writing a document's poslist.
+** plwDestroy - clear a writer.
+** plwAdd - append position and offset information.
+** plwCopy - copy next position's data from reader to writer.
+** plwTerminate - add any necessary doclist terminator.
+**
+** Calling plwAdd() after plwTerminate() may result in a corrupt
+** doclist.
+*/
+/* TODO(shess) Until we've written the second item, we can cache the
+** first item's information.  Then we'd have three states:
+**
+** - initialized with docid, no positions.
+** - docid and one position.
+** - docid and multiple positions.
+**
+** Only the last state needs to actually write to dlw->b, which would
+** be an improvement in the DLCollector case.
+*/
+typedef struct PLWriter {
+  DLWriter *dlw;
+
+  int iColumn;    /* the last column written */
+  int iPos;       /* the last position written */
+  int iOffset;    /* the last start offset written */
+} PLWriter;
+
+/* TODO(shess) In the case where the parent is reading these values
+** from a PLReader, we could optimize to a copy if that PLReader has
+** the same type as pWriter.
+*/
+static void plwAdd(PLWriter *pWriter, int iColumn, int iPos,
+                   int iStartOffset, int iEndOffset){
+  /* Worst-case space for POS_COLUMN, iColumn, iPosDelta,
+  ** iStartOffsetDelta, and iEndOffsetDelta.
+  */
+  char c[5*VARINT_MAX];
+  int n = 0;
 
-  sqlite3_free(p);
-  return SQLITE_OK;
-}
+  /* Ban plwAdd() after plwTerminate(). */
+  assert( pWriter->iPos!=-1 );
 
-/*
-** Write an error message into *pzErr
-*/
-void sqlite3Fts3ErrMsg(char **pzErr, const char *zFormat, ...){
-  va_list ap;
-  sqlite3_free(*pzErr);
-  va_start(ap, zFormat);
-  *pzErr = sqlite3_vmprintf(zFormat, ap);
-  va_end(ap);
+  if( pWriter->dlw->iType==DL_DOCIDS ) return;
+
+  if( iColumn!=pWriter->iColumn ){
+    n += fts3PutVarint(c+n, POS_COLUMN);
+    n += fts3PutVarint(c+n, iColumn);
+    pWriter->iColumn = iColumn;
+    pWriter->iPos = 0;
+    pWriter->iOffset = 0;
+  }
+  assert( iPos>=pWriter->iPos );
+  n += fts3PutVarint(c+n, POS_BASE+(iPos-pWriter->iPos));
+  pWriter->iPos = iPos;
+  if( pWriter->dlw->iType==DL_POSITIONS_OFFSETS ){
+    assert( iStartOffset>=pWriter->iOffset );
+    n += fts3PutVarint(c+n, iStartOffset-pWriter->iOffset);
+    pWriter->iOffset = iStartOffset;
+    assert( iEndOffset>=iStartOffset );
+    n += fts3PutVarint(c+n, iEndOffset-iStartOffset);
+  }
+  dataBufferAppend(pWriter->dlw->b, c, n);
+}
+static void plwCopy(PLWriter *pWriter, PLReader *pReader){
+  plwAdd(pWriter, plrColumn(pReader), plrPosition(pReader),
+         plrStartOffset(pReader), plrEndOffset(pReader));
+}
+static void plwInit(PLWriter *pWriter, DLWriter *dlw, sqlite_int64 iDocid){
+  char c[VARINT_MAX];
+  int n;
+
+  pWriter->dlw = dlw;
+
+  /* Docids must ascend. */
+  assert( !pWriter->dlw->has_iPrevDocid || iDocid>pWriter->dlw->iPrevDocid );
+  n = fts3PutVarint(c, iDocid-pWriter->dlw->iPrevDocid);
+  dataBufferAppend(pWriter->dlw->b, c, n);
+  pWriter->dlw->iPrevDocid = iDocid;
+#ifndef NDEBUG
+  pWriter->dlw->has_iPrevDocid = 1;
+#endif
+
+  pWriter->iColumn = 0;
+  pWriter->iPos = 0;
+  pWriter->iOffset = 0;
+}
+/* TODO(shess) Should plwDestroy() also terminate the doclist?  But
+** then plwDestroy() would no longer be just a destructor, it would
+** also be doing work, which isn't consistent with the overall idiom.
+** Another option would be for plwAdd() to always append any necessary
+** terminator, so that the output is always correct.  But that would
+** add incremental work to the common case with the only benefit being
+** API elegance.  Punt for now.
+*/
+static void plwTerminate(PLWriter *pWriter){
+  if( pWriter->dlw->iType>DL_DOCIDS ){
+    char c[VARINT_MAX];
+    int n = fts3PutVarint(c, POS_END);
+    dataBufferAppend(pWriter->dlw->b, c, n);
+  }
+#ifndef NDEBUG
+  /* Mark as terminated for assert in plwAdd(). */
+  pWriter->iPos = -1;
+#endif
+}
+static void plwDestroy(PLWriter *pWriter){
+  SCRAMBLE(pWriter);
 }
 
-/*
-** Construct one or more SQL statements from the format string given
-** and then evaluate those statements. The success code is written
-** into *pRc.
-**
-** If *pRc is initially non-zero then this routine is a no-op.
-*/
-static void fts3DbExec(
-  int *pRc,              /* Success code */
-  sqlite3 *db,           /* Database in which to run SQL */
-  const char *zFormat,   /* Format string for SQL */
-  ...                    /* Arguments to the format string */
-){
-  va_list ap;
-  char *zSql;
-  if( *pRc ) return;
-  va_start(ap, zFormat);
-  zSql = sqlite3_vmprintf(zFormat, ap);
-  va_end(ap);
-  if( zSql==0 ){
-    *pRc = SQLITE_NOMEM;
+/*******************************************************************/
+/* DLCollector wraps PLWriter and DLWriter to provide a
+** dynamically-allocated doclist area to use during tokenization.
+**
+** dlcNew - malloc up and initialize a collector.
+** dlcDelete - destroy a collector and all contained items.
+** dlcAddPos - append position and offset information.
+** dlcAddDoclist - add the collected doclist to the given buffer.
+** dlcNext - terminate the current document and open another.
+*/
+typedef struct DLCollector {
+  DataBuffer b;
+  DLWriter dlw;
+  PLWriter plw;
+} DLCollector;
+
+/* TODO(shess) This could also be done by calling plwTerminate() and
+** dataBufferAppend().  I tried that, expecting nominal performance
+** differences, but it seemed to pretty reliably be worth 1% to code
+** it this way.  I suspect it is the incremental malloc overhead (some
+** percentage of the plwTerminate() calls will cause a realloc), so
+** this might be worth revisiting if the DataBuffer implementation
+** changes.
+*/
+static void dlcAddDoclist(DLCollector *pCollector, DataBuffer *b){
+  if( pCollector->dlw.iType>DL_DOCIDS ){
+    char c[VARINT_MAX];
+    int n = fts3PutVarint(c, POS_END);
+    dataBufferAppend2(b, pCollector->b.pData, pCollector->b.nData, c, n);
   }else{
-    *pRc = sqlite3_exec(db, zSql, 0, 0, 0);
-    sqlite3_free(zSql);
+    dataBufferAppend(b, pCollector->b.pData, pCollector->b.nData);
   }
 }
+static void dlcNext(DLCollector *pCollector, sqlite_int64 iDocid){
+  plwTerminate(&pCollector->plw);
+  plwDestroy(&pCollector->plw);
+  plwInit(&pCollector->plw, &pCollector->dlw, iDocid);
+}
+static void dlcAddPos(DLCollector *pCollector, int iColumn, int iPos,
+                      int iStartOffset, int iEndOffset){
+  plwAdd(&pCollector->plw, iColumn, iPos, iStartOffset, iEndOffset);
+}
 
-/*
-** The xDestroy() virtual table method.
-*/
-static int fts3DestroyMethod(sqlite3_vtab *pVtab){
-  Fts3Table *p = (Fts3Table *)pVtab;
-  int rc = SQLITE_OK;              /* Return code */
-  const char *zDb = p->zDb;        /* Name of database (e.g. "main", "temp") */
-  sqlite3 *db = p->db;             /* Database handle */
-
-  /* Drop the shadow tables */
-  if( p->zContentTbl==0 ){
-    fts3DbExec(&rc, db, "DROP TABLE IF EXISTS %Q.'%q_content'", zDb, p->zName);
-  }
-  fts3DbExec(&rc, db, "DROP TABLE IF EXISTS %Q.'%q_segments'", zDb,p->zName);
-  fts3DbExec(&rc, db, "DROP TABLE IF EXISTS %Q.'%q_segdir'", zDb, p->zName);
-  fts3DbExec(&rc, db, "DROP TABLE IF EXISTS %Q.'%q_docsize'", zDb, p->zName);
-  fts3DbExec(&rc, db, "DROP TABLE IF EXISTS %Q.'%q_stat'", zDb, p->zName);
-
-  /* If everything has worked, invoke fts3DisconnectMethod() to free the
-  ** memory associated with the Fts3Table structure and return SQLITE_OK.
-  ** Otherwise, return an SQLite error code.
-  */
-  return (rc==SQLITE_OK ? fts3DisconnectMethod(pVtab) : rc);
+static DLCollector *dlcNew(sqlite_int64 iDocid, DocListType iType){
+  DLCollector *pCollector = sqlite3_malloc(sizeof(DLCollector));
+  dataBufferInit(&pCollector->b, 0);
+  dlwInit(&pCollector->dlw, iType, &pCollector->b);
+  plwInit(&pCollector->plw, &pCollector->dlw, iDocid);
+  return pCollector;
+}
+static void dlcDelete(DLCollector *pCollector){
+  plwDestroy(&pCollector->plw);
+  dlwDestroy(&pCollector->dlw);
+  dataBufferDestroy(&pCollector->b);
+  SCRAMBLE(pCollector);
+  sqlite3_free(pCollector);
 }
 
 
-/*
-** Invoke sqlite3_declare_vtab() to declare the schema for the FTS3 table
-** passed as the first argument. This is done as part of the xConnect()
-** and xCreate() methods.
-**
-** If *pRc is non-zero when this function is called, it is a no-op. 
-** Otherwise, if an error occurs, an SQLite error code is stored in *pRc
-** before returning.
-*/
-static void fts3DeclareVtab(int *pRc, Fts3Table *p){
-  if( *pRc==SQLITE_OK ){
-    int i;                        /* Iterator variable */
-    int rc;                       /* Return code */
-    char *zSql;                   /* SQL statement passed to declare_vtab() */
-    char *zCols;                  /* List of user defined columns */
-    const char *zLanguageid;
-
-    zLanguageid = (p->zLanguageid ? p->zLanguageid : "__langid");
-    sqlite3_vtab_config(p->db, SQLITE_VTAB_CONSTRAINT_SUPPORT, 1);
-
-    /* Create a list of user columns for the virtual table */
-    zCols = sqlite3_mprintf("%Q, ", p->azColumn[0]);
-    for(i=1; zCols && i<p->nColumn; i++){
-      zCols = sqlite3_mprintf("%z%Q, ", zCols, p->azColumn[i]);
-    }
-
-    /* Create the whole "CREATE TABLE" statement to pass to SQLite */
-    zSql = sqlite3_mprintf(
-        "CREATE TABLE x(%s %Q HIDDEN, docid HIDDEN, %Q HIDDEN)", 
-        zCols, p->zName, zLanguageid
-    );
-    if( !zCols || !zSql ){
-      rc = SQLITE_NOMEM;
-    }else{
-      rc = sqlite3_declare_vtab(p->db, zSql);
+/* Copy the doclist data of iType in pData/nData into *out, trimming
+** unnecessary data as we go.  Only columns matching iColumn are
+** copied, all columns copied if iColumn is -1.  Elements with no
+** matching columns are dropped.  The output is an iOutType doclist.
+*/
+/* NOTE(shess) This code is only valid after all doclists are merged.
+** If this is run before merges, then doclist items which represent
+** deletion will be trimmed, and will thus not effect a deletion
+** during the merge.
+*/
+static void docListTrim(DocListType iType, const char *pData, int nData,
+                        int iColumn, DocListType iOutType, DataBuffer *out){
+  DLReader dlReader;
+  DLWriter dlWriter;
+
+  assert( iOutType<=iType );
+
+  dlrInit(&dlReader, iType, pData, nData);
+  dlwInit(&dlWriter, iOutType, out);
+
+  while( !dlrAtEnd(&dlReader) ){
+    PLReader plReader;
+    PLWriter plWriter;
+    int match = 0;
+
+    plrInit(&plReader, &dlReader);
+
+    while( !plrAtEnd(&plReader) ){
+      if( iColumn==-1 || plrColumn(&plReader)==iColumn ){
+        if( !match ){
+          plwInit(&plWriter, &dlWriter, dlrDocid(&dlReader));
+          match = 1;
+        }
+        plwAdd(&plWriter, plrColumn(&plReader), plrPosition(&plReader),
+               plrStartOffset(&plReader), plrEndOffset(&plReader));
+      }
+      plrStep(&plReader);
+    }
+    if( match ){
+      plwTerminate(&plWriter);
+      plwDestroy(&plWriter);
     }
 
-    sqlite3_free(zSql);
-    sqlite3_free(zCols);
-    *pRc = rc;
+    plrDestroy(&plReader);
+    dlrStep(&dlReader);
   }
+  dlwDestroy(&dlWriter);
+  dlrDestroy(&dlReader);
 }
 
-/*
-** Create the %_stat table if it does not already exist.
+/* Used by docListMerge() to keep doclists in the ascending order by
+** docid, then ascending order by age (so the newest comes first).
 */
-void sqlite3Fts3CreateStatTable(int *pRc, Fts3Table *p){
-  fts3DbExec(pRc, p->db, 
-      "CREATE TABLE IF NOT EXISTS %Q.'%q_stat'"
-          "(id INTEGER PRIMARY KEY, value BLOB);",
-      p->zDb, p->zName
-  );
-  if( (*pRc)==SQLITE_OK ) p->bHasStat = 1;
+typedef struct OrderedDLReader {
+  DLReader *pReader;
+
+  /* TODO(shess) If we assume that docListMerge pReaders is ordered by
+  ** age (which we do), then we could use pReader comparisons to break
+  ** ties.
+  */
+  int idx;
+} OrderedDLReader;
+
+/* Order eof to end, then by docid asc, idx desc. */
+static int orderedDLReaderCmp(OrderedDLReader *r1, OrderedDLReader *r2){
+  if( dlrAtEnd(r1->pReader) ){
+    if( dlrAtEnd(r2->pReader) ) return 0;  /* Both atEnd(). */
+    return 1;                              /* Only r1 atEnd(). */
+  }
+  if( dlrAtEnd(r2->pReader) ) return -1;   /* Only r2 atEnd(). */
+
+  if( dlrDocid(r1->pReader)<dlrDocid(r2->pReader) ) return -1;
+  if( dlrDocid(r1->pReader)>dlrDocid(r2->pReader) ) return 1;
+
+  /* Descending on idx. */
+  return r2->idx-r1->idx;
+}
+
+/* Bubble p[0] to appropriate place in p[1..n-1].  Assumes that
+** p[1..n-1] is already sorted.
+*/
+/* TODO(shess) Is this frequent enough to warrant a binary search?
+** Before implementing that, instrument the code to check.  In most
+** current usage, I expect that p[0] will be less than p[1] a very
+** high proportion of the time.
+*/
+static void orderedDLReaderReorder(OrderedDLReader *p, int n){
+  while( n>1 && orderedDLReaderCmp(p, p+1)>0 ){
+    OrderedDLReader tmp = p[0];
+    p[0] = p[1];
+    p[1] = tmp;
+    n--;
+    p++;
+  }
 }
 
-/*
-** Create the backing store tables (%_content, %_segments and %_segdir)
-** required by the FTS3 table passed as the only argument. This is done
-** as part of the vtab xCreate() method.
-**
-** If the p->bHasDocsize boolean is true (indicating that this is an
-** FTS4 table, not an FTS3 table) then also create the %_docsize and
-** %_stat tables required by FTS4.
-*/
-static int fts3CreateTables(Fts3Table *p){
-  int rc = SQLITE_OK;             /* Return code */
-  int i;                          /* Iterator variable */
-  sqlite3 *db = p->db;            /* The database connection */
-
-  if( p->zContentTbl==0 ){
-    const char *zLanguageid = p->zLanguageid;
-    char *zContentCols;           /* Columns of %_content table */
-
-    /* Create a list of user columns for the content table */
-    zContentCols = sqlite3_mprintf("docid INTEGER PRIMARY KEY");
-    for(i=0; zContentCols && i<p->nColumn; i++){
-      char *z = p->azColumn[i];
-      zContentCols = sqlite3_mprintf("%z, 'c%d%q'", zContentCols, i, z);
-    }
-    if( zLanguageid && zContentCols ){
-      zContentCols = sqlite3_mprintf("%z, langid", zContentCols, zLanguageid);
-    }
-    if( zContentCols==0 ) rc = SQLITE_NOMEM;
-  
-    /* Create the content table */
-    fts3DbExec(&rc, db, 
-       "CREATE TABLE %Q.'%q_content'(%s)",
-       p->zDb, p->zName, zContentCols
-    );
-    sqlite3_free(zContentCols);
+/* Given an array of doclist readers, merge their doclist elements
+** into out in sorted order (by docid), dropping elements from older
+** readers when there is a duplicate docid.  pReaders is assumed to be
+** ordered by age, oldest first.
+*/
+/* TODO(shess) nReaders must be <= MERGE_COUNT.  This should probably
+** be fixed.
+*/
+static void docListMerge(DataBuffer *out,
+                         DLReader *pReaders, int nReaders){
+  OrderedDLReader readers[MERGE_COUNT];
+  DLWriter writer;
+  int i, n;
+  const char *pStart = 0;
+  int nStart = 0;
+  sqlite_int64 iFirstDocid = 0, iLastDocid = 0;
+
+  assert( nReaders>0 );
+  if( nReaders==1 ){
+    dataBufferAppend(out, dlrDocData(pReaders), dlrAllDataBytes(pReaders));
+    return;
   }
 
-  /* Create other tables */
-  fts3DbExec(&rc, db, 
-      "CREATE TABLE %Q.'%q_segments'(blockid INTEGER PRIMARY KEY, block BLOB);",
-      p->zDb, p->zName
-  );
-  fts3DbExec(&rc, db, 
-      "CREATE TABLE %Q.'%q_segdir'("
-        "level INTEGER,"
-        "idx INTEGER,"
-        "start_block INTEGER,"
-        "leaves_end_block INTEGER,"
-        "end_block INTEGER,"
-        "root BLOB,"
-        "PRIMARY KEY(level, idx)"
-      ");",
-      p->zDb, p->zName
-  );
-  if( p->bHasDocsize ){
-    fts3DbExec(&rc, db, 
-        "CREATE TABLE %Q.'%q_docsize'(docid INTEGER PRIMARY KEY, size BLOB);",
-        p->zDb, p->zName
-    );
+  assert( nReaders<=MERGE_COUNT );
+  n = 0;
+  for(i=0; i<nReaders; i++){
+    assert( pReaders[i].iType==pReaders[0].iType );
+    readers[i].pReader = pReaders+i;
+    readers[i].idx = i;
+    n += dlrAllDataBytes(&pReaders[i]);
   }
-  assert( p->bHasStat==p->bFts4 );
-  if( p->bHasStat ){
-    sqlite3Fts3CreateStatTable(&rc, p);
+  /* Conservatively size output to sum of inputs.  Output should end
+  ** up strictly smaller than input.
+  */
+  dataBufferExpand(out, n);
+
+  /* Get the readers into sorted order. */
+  while( i-->0 ){
+    orderedDLReaderReorder(readers+i, nReaders-i);
   }
-  return rc;
-}
 
-/*
-** Store the current database page-size in bytes in p->nPgsz.
-**
-** If *pRc is non-zero when this function is called, it is a no-op. 
-** Otherwise, if an error occurs, an SQLite error code is stored in *pRc
-** before returning.
-*/
-static void fts3DatabasePageSize(int *pRc, Fts3Table *p){
-  if( *pRc==SQLITE_OK ){
-    int rc;                       /* Return code */
-    char *zSql;                   /* SQL text "PRAGMA %Q.page_size" */
-    sqlite3_stmt *pStmt;          /* Compiled "PRAGMA %Q.page_size" statement */
-  
-    zSql = sqlite3_mprintf("PRAGMA %Q.page_size", p->zDb);
-    if( !zSql ){
-      rc = SQLITE_NOMEM;
+  dlwInit(&writer, pReaders[0].iType, out);
+  while( !dlrAtEnd(readers[0].pReader) ){
+    sqlite_int64 iDocid = dlrDocid(readers[0].pReader);
+
+    /* If this is a continuation of the current buffer to copy, extend
+    ** that buffer.  memcpy() seems to be more efficient if it has a
+    ** lots of data to copy.
+    */
+    if( dlrDocData(readers[0].pReader)==pStart+nStart ){
+      nStart += dlrDocDataBytes(readers[0].pReader);
     }else{
-      rc = sqlite3_prepare(p->db, zSql, -1, &pStmt, 0);
-      if( rc==SQLITE_OK ){
-        sqlite3_step(pStmt);
-        p->nPgsz = sqlite3_column_int(pStmt, 0);
-        rc = sqlite3_finalize(pStmt);
-      }else if( rc==SQLITE_AUTH ){
-        p->nPgsz = 1024;
-        rc = SQLITE_OK;
+      if( pStart!=0 ){
+        dlwAppend(&writer, pStart, nStart, iFirstDocid, iLastDocid);
       }
+      pStart = dlrDocData(readers[0].pReader);
+      nStart = dlrDocDataBytes(readers[0].pReader);
+      iFirstDocid = iDocid;
+    }
+    iLastDocid = iDocid;
+    dlrStep(readers[0].pReader);
+
+    /* Drop all of the older elements with the same docid. */
+    for(i=1; i<nReaders &&
+             !dlrAtEnd(readers[i].pReader) &&
+             dlrDocid(readers[i].pReader)==iDocid; i++){
+      dlrStep(readers[i].pReader);
+    }
+
+    /* Get the readers back into order. */
+    while( i-->0 ){
+      orderedDLReaderReorder(readers+i, nReaders-i);
     }
-    assert( p->nPgsz>0 || rc!=SQLITE_OK );
-    sqlite3_free(zSql);
-    *pRc = rc;
   }
+
+  /* Copy over any remaining elements. */
+  if( nStart>0 ) dlwAppend(&writer, pStart, nStart, iFirstDocid, iLastDocid);
+  dlwDestroy(&writer);
 }
 
-/*
-** "Special" FTS4 arguments are column specifications of the following form:
-**
-**   <key> = <value>
-**
-** There may not be whitespace surrounding the "=" character. The <value> 
-** term may be quoted, but the <key> may not.
+/* Helper function for posListUnion().  Compares the current position
+** between left and right, returning as standard C idiom of <0 if
+** left<right, >0 if left>right, and 0 if left==right.  "End" always
+** compares greater.
 */
-static int fts3IsSpecialColumn(
-  const char *z, 
-  int *pnKey,
-  char **pzValue
-){
-  char *zValue;
-  const char *zCsr = z;
+static int posListCmp(PLReader *pLeft, PLReader *pRight){
+  assert( pLeft->iType==pRight->iType );
+  if( pLeft->iType==DL_DOCIDS ) return 0;
 
-  while( *zCsr!='=' ){
-    if( *zCsr=='\0' ) return 0;
-    zCsr++;
-  }
+  if( plrAtEnd(pLeft) ) return plrAtEnd(pRight) ? 0 : 1;
+  if( plrAtEnd(pRight) ) return -1;
+
+  if( plrColumn(pLeft)<plrColumn(pRight) ) return -1;
+  if( plrColumn(pLeft)>plrColumn(pRight) ) return 1;
+
+  if( plrPosition(pLeft)<plrPosition(pRight) ) return -1;
+  if( plrPosition(pLeft)>plrPosition(pRight) ) return 1;
+  if( pLeft->iType==DL_POSITIONS ) return 0;
 
-  *pnKey = (int)(zCsr-z);
-  zValue = sqlite3_mprintf("%s", &zCsr[1]);
-  if( zValue ){
-    sqlite3Fts3Dequote(zValue);
+  if( plrStartOffset(pLeft)<plrStartOffset(pRight) ) return -1;
+  if( plrStartOffset(pLeft)>plrStartOffset(pRight) ) return 1;
+
+  if( plrEndOffset(pLeft)<plrEndOffset(pRight) ) return -1;
+  if( plrEndOffset(pLeft)>plrEndOffset(pRight) ) return 1;
+
+  return 0;
+}
+
+/* Write the union of position lists in pLeft and pRight to pOut.
+** "Union" in this case meaning "All unique position tuples".  Should
+** work with any doclist type, though both inputs and the output
+** should be the same type.
+*/
+static void posListUnion(DLReader *pLeft, DLReader *pRight, DLWriter *pOut){
+  PLReader left, right;
+  PLWriter writer;
+
+  assert( dlrDocid(pLeft)==dlrDocid(pRight) );
+  assert( pLeft->iType==pRight->iType );
+  assert( pLeft->iType==pOut->iType );
+
+  plrInit(&left, pLeft);
+  plrInit(&right, pRight);
+  plwInit(&writer, pOut, dlrDocid(pLeft));
+
+  while( !plrAtEnd(&left) || !plrAtEnd(&right) ){
+    int c = posListCmp(&left, &right);
+    if( c<0 ){
+      plwCopy(&writer, &left);
+      plrStep(&left);
+    }else if( c>0 ){
+      plwCopy(&writer, &right);
+      plrStep(&right);
+    }else{
+      plwCopy(&writer, &left);
+      plrStep(&left);
+      plrStep(&right);
+    }
   }
-  *pzValue = zValue;
-  return 1;
+
+  plwTerminate(&writer);
+  plwDestroy(&writer);
+  plrDestroy(&left);
+  plrDestroy(&right);
 }
 
-/*
-** Append the output of a printf() style formatting to an existing string.
+/* Write the union of doclists in pLeft and pRight to pOut.  For
+** docids in common between the inputs, the union of the position
+** lists is written.  Inputs and outputs are always type DL_DEFAULT.
 */
-static void fts3Appendf(
-  int *pRc,                       /* IN/OUT: Error code */
-  char **pz,                      /* IN/OUT: Pointer to string buffer */
-  const char *zFormat,            /* Printf format string to append */
-  ...                             /* Arguments for printf format string */
+static void docListUnion(
+  const char *pLeft, int nLeft,
+  const char *pRight, int nRight,
+  DataBuffer *pOut      /* Write the combined doclist here */
 ){
-  if( *pRc==SQLITE_OK ){
-    va_list ap;
-    char *z;
-    va_start(ap, zFormat);
-    z = sqlite3_vmprintf(zFormat, ap);
-    va_end(ap);
-    if( z && *pz ){
-      char *z2 = sqlite3_mprintf("%s%s", *pz, z);
-      sqlite3_free(z);
-      z = z2;
-    }
-    if( z==0 ) *pRc = SQLITE_NOMEM;
-    sqlite3_free(*pz);
-    *pz = z;
+  DLReader left, right;
+  DLWriter writer;
+
+  if( nLeft==0 ){
+    if( nRight!=0) dataBufferAppend(pOut, pRight, nRight);
+    return;
+  }
+  if( nRight==0 ){
+    dataBufferAppend(pOut, pLeft, nLeft);
+    return;
   }
-}
 
-/*
-** Return a copy of input string zInput enclosed in double-quotes (") and
-** with all double quote characters escaped. For example:
-**
-**     fts3QuoteId("un \"zip\"")   ->    "un \"\"zip\"\""
-**
-** The pointer returned points to memory obtained from sqlite3_malloc(). It
-** is the callers responsibility to call sqlite3_free() to release this
-** memory.
-*/
-static char *fts3QuoteId(char const *zInput){
-  int nRet;
-  char *zRet;
-  nRet = 2 + (int)strlen(zInput)*2 + 1;
-  zRet = sqlite3_malloc(nRet);
-  if( zRet ){
-    int i;
-    char *z = zRet;
-    *(z++) = '"';
-    for(i=0; zInput[i]; i++){
-      if( zInput[i]=='"' ) *(z++) = '"';
-      *(z++) = zInput[i];
+  dlrInit(&left, DL_DEFAULT, pLeft, nLeft);
+  dlrInit(&right, DL_DEFAULT, pRight, nRight);
+  dlwInit(&writer, DL_DEFAULT, pOut);
+
+  while( !dlrAtEnd(&left) || !dlrAtEnd(&right) ){
+    if( dlrAtEnd(&right) ){
+      dlwCopy(&writer, &left);
+      dlrStep(&left);
+    }else if( dlrAtEnd(&left) ){
+      dlwCopy(&writer, &right);
+      dlrStep(&right);
+    }else if( dlrDocid(&left)<dlrDocid(&right) ){
+      dlwCopy(&writer, &left);
+      dlrStep(&left);
+    }else if( dlrDocid(&left)>dlrDocid(&right) ){
+      dlwCopy(&writer, &right);
+      dlrStep(&right);
+    }else{
+      posListUnion(&left, &right, &writer);
+      dlrStep(&left);
+      dlrStep(&right);
     }
-    *(z++) = '"';
-    *(z++) = '\0';
   }
-  return zRet;
+
+  dlrDestroy(&left);
+  dlrDestroy(&right);
+  dlwDestroy(&writer);
 }
 
-/*
-** Return a list of comma separated SQL expressions and a FROM clause that 
-** could be used in a SELECT statement such as the following:
-**
-**     SELECT <list of expressions> FROM %_content AS x ...
+/* 
+** This function is used as part of the implementation of phrase and
+** NEAR matching.
 **
-** to return the docid, followed by each column of text data in order
-** from left to write. If parameter zFunc is not NULL, then instead of
-** being returned directly each column of text data is passed to an SQL
-** function named zFunc first. For example, if zFunc is "unzip" and the
-** table has the three user-defined columns "a", "b", and "c", the following
-** string is returned:
-**
-**     "docid, unzip(x.'a'), unzip(x.'b'), unzip(x.'c') FROM %_content AS x"
-**
-** The pointer returned points to a buffer allocated by sqlite3_malloc(). It
-** is the responsibility of the caller to eventually free it.
-**
-** If *pRc is not SQLITE_OK when this function is called, it is a no-op (and
-** a NULL pointer is returned). Otherwise, if an OOM error is encountered
-** by this function, NULL is returned and *pRc is set to SQLITE_NOMEM. If
-** no error occurs, *pRc is left unmodified.
-*/
-static char *fts3ReadExprList(Fts3Table *p, const char *zFunc, int *pRc){
-  char *zRet = 0;
-  char *zFree = 0;
-  char *zFunction;
-  int i;
-
-  if( p->zContentTbl==0 ){
-    if( !zFunc ){
-      zFunction = "";
+** pLeft and pRight are DLReaders positioned to the same docid in
+** lists of type DL_POSITION. This function writes an entry to the
+** DLWriter pOut for each position in pRight that is less than
+** (nNear+1) greater (but not equal to or smaller) than a position 
+** in pLeft. For example, if nNear is 0, and the positions contained
+** by pLeft and pRight are:
+**
+**    pLeft:  5 10 15 20
+**    pRight: 6  9 17 21
+**
+** then the docid is added to pOut. If pOut is of type DL_POSITIONS,
+** then a positionids "6" and "21" are also added to pOut.
+**
+** If boolean argument isSaveLeft is true, then positionids are copied
+** from pLeft instead of pRight. In the example above, the positions "5"
+** and "20" would be added instead of "6" and "21".
+*/
+static void posListPhraseMerge(
+  DLReader *pLeft, 
+  DLReader *pRight,
+  int nNear,
+  int isSaveLeft,
+  DLWriter *pOut
+){
+  PLReader left, right;
+  PLWriter writer;
+  int match = 0;
+
+  assert( dlrDocid(pLeft)==dlrDocid(pRight) );
+  assert( pOut->iType!=DL_POSITIONS_OFFSETS );
+
+  plrInit(&left, pLeft);
+  plrInit(&right, pRight);
+
+  while( !plrAtEnd(&left) && !plrAtEnd(&right) ){
+    if( plrColumn(&left)<plrColumn(&right) ){
+      plrStep(&left);
+    }else if( plrColumn(&left)>plrColumn(&right) ){
+      plrStep(&right);
+    }else if( plrPosition(&left)>=plrPosition(&right) ){
+      plrStep(&right);
     }else{
-      zFree = zFunction = fts3QuoteId(zFunc);
-    }
-    fts3Appendf(pRc, &zRet, "docid");
-    for(i=0; i<p->nColumn; i++){
-      fts3Appendf(pRc, &zRet, ",%s(x.'c%d%q')", zFunction, i, p->azColumn[i]);
-    }
-    if( p->zLanguageid ){
-      fts3Appendf(pRc, &zRet, ", x.%Q", "langid");
-    }
-    sqlite3_free(zFree);
-  }else{
-    fts3Appendf(pRc, &zRet, "rowid");
-    for(i=0; i<p->nColumn; i++){
-      fts3Appendf(pRc, &zRet, ", x.'%q'", p->azColumn[i]);
-    }
-    if( p->zLanguageid ){
-      fts3Appendf(pRc, &zRet, ", x.%Q", p->zLanguageid);
+      if( (plrPosition(&right)-plrPosition(&left))<=(nNear+1) ){
+        if( !match ){
+          plwInit(&writer, pOut, dlrDocid(pLeft));
+          match = 1;
+        }
+        if( !isSaveLeft ){
+          plwAdd(&writer, plrColumn(&right), plrPosition(&right), 0, 0);
+        }else{
+          plwAdd(&writer, plrColumn(&left), plrPosition(&left), 0, 0);
+        }
+        plrStep(&right);
+      }else{
+        plrStep(&left);
+      }
     }
   }
-  fts3Appendf(pRc, &zRet, " FROM '%q'.'%q%s' AS x", 
-      p->zDb,
-      (p->zContentTbl ? p->zContentTbl : p->zName),
-      (p->zContentTbl ? "" : "_content")
-  );
-  return zRet;
+
+  if( match ){
+    plwTerminate(&writer);
+    plwDestroy(&writer);
+  }
+
+  plrDestroy(&left);
+  plrDestroy(&right);
 }
 
 /*
-** Return a list of N comma separated question marks, where N is the number
-** of columns in the %_content table (one for the docid plus one for each
-** user-defined text column).
-**
-** If argument zFunc is not NULL, then all but the first question mark
-** is preceded by zFunc and an open bracket, and followed by a closed
-** bracket. For example, if zFunc is "zip" and the FTS3 table has three 
-** user-defined text columns, the following string is returned:
-**
-**     "?, zip(?), zip(?), zip(?)"
-**
-** The pointer returned points to a buffer allocated by sqlite3_malloc(). It
-** is the responsibility of the caller to eventually free it.
-**
-** If *pRc is not SQLITE_OK when this function is called, it is a no-op (and
-** a NULL pointer is returned). Otherwise, if an OOM error is encountered
-** by this function, NULL is returned and *pRc is set to SQLITE_NOMEM. If
-** no error occurs, *pRc is left unmodified.
-*/
-static char *fts3WriteExprList(Fts3Table *p, const char *zFunc, int *pRc){
-  char *zRet = 0;
-  char *zFree = 0;
-  char *zFunction;
-  int i;
+** Compare the values pointed to by the PLReaders passed as arguments. 
+** Return -1 if the value pointed to by pLeft is considered less than
+** the value pointed to by pRight, +1 if it is considered greater
+** than it, or 0 if it is equal. i.e.
+**
+**     (*pLeft - *pRight)
+**
+** A PLReader that is in the EOF condition is considered greater than
+** any other. If neither argument is in EOF state, the return value of
+** plrColumn() is used. If the plrColumn() values are equal, the
+** comparison is on the basis of plrPosition().
+*/
+static int plrCompare(PLReader *pLeft, PLReader *pRight){
+  assert(!plrAtEnd(pLeft) || !plrAtEnd(pRight));
 
-  if( !zFunc ){
-    zFunction = "";
-  }else{
-    zFree = zFunction = fts3QuoteId(zFunc);
+  if( plrAtEnd(pRight) || plrAtEnd(pLeft) ){
+    return (plrAtEnd(pRight) ? -1 : 1);
   }
-  fts3Appendf(pRc, &zRet, "?");
-  for(i=0; i<p->nColumn; i++){
-    fts3Appendf(pRc, &zRet, ",%s(?)", zFunction);
+  if( plrColumn(pLeft)!=plrColumn(pRight) ){
+    return ((plrColumn(pLeft)<plrColumn(pRight)) ? -1 : 1);
   }
-  if( p->zLanguageid ){
-    fts3Appendf(pRc, &zRet, ", ?");
+  if( plrPosition(pLeft)!=plrPosition(pRight) ){
+    return ((plrPosition(pLeft)<plrPosition(pRight)) ? -1 : 1);
   }
-  sqlite3_free(zFree);
-  return zRet;
+  return 0;
 }
 
-/*
-** This function interprets the string at (*pp) as a non-negative integer
-** value. It reads the integer and sets *pnOut to the value read, then 
-** sets *pp to point to the byte immediately following the last byte of
-** the integer value.
-**
-** Only decimal digits ('0'..'9') may be part of an integer value. 
-**
-** If *pp does not being with a decimal digit SQLITE_ERROR is returned and
-** the output value undefined. Otherwise SQLITE_OK is returned.
-**
-** This function is used when parsing the "prefix=" FTS4 parameter.
-*/
-static int fts3GobbleInt(const char **pp, int *pnOut){
-  const int MAX_NPREFIX = 10000000;
-  const char *p;                  /* Iterator pointer */
-  int nInt = 0;                   /* Output value */
-
-  for(p=*pp; p[0]>='0' && p[0]<='9'; p++){
-    nInt = nInt * 10 + (p[0] - '0');
-    if( nInt>MAX_NPREFIX ){
-      nInt = 0;
-      break;
+/* We have two doclists with positions:  pLeft and pRight. Depending
+** on the value of the nNear parameter, perform either a phrase
+** intersection (if nNear==0) or a NEAR intersection (if nNear>0)
+** and write the results into pOut.
+**
+** A phrase intersection means that two documents only match
+** if pLeft.iPos+1==pRight.iPos.
+**
+** A NEAR intersection means that two documents only match if 
+** (abs(pLeft.iPos-pRight.iPos)<nNear).
+**
+** If a NEAR intersection is requested, then the nPhrase argument should
+** be passed the number of tokens in the two operands to the NEAR operator
+** combined. For example:
+**
+**       Query syntax               nPhrase
+**      ------------------------------------
+**       "A B C" NEAR "D E"         5
+**       A NEAR B                   2
+**
+** iType controls the type of data written to pOut.  If iType is
+** DL_POSITIONS, the positions are those from pRight.
+*/
+static void docListPhraseMerge(
+  const char *pLeft, int nLeft,
+  const char *pRight, int nRight,
+  int nNear,            /* 0 for a phrase merge, non-zero for a NEAR merge */
+  int nPhrase,          /* Number of tokens in left+right operands to NEAR */
+  DocListType iType,    /* Type of doclist to write to pOut */
+  DataBuffer *pOut      /* Write the combined doclist here */
+){
+  DLReader left, right;
+  DLWriter writer;
+
+  if( nLeft==0 || nRight==0 ) return;
+
+  assert( iType!=DL_POSITIONS_OFFSETS );
+
+  dlrInit(&left, DL_POSITIONS, pLeft, nLeft);
+  dlrInit(&right, DL_POSITIONS, pRight, nRight);
+  dlwInit(&writer, iType, pOut);
+
+  while( !dlrAtEnd(&left) && !dlrAtEnd(&right) ){
+    if( dlrDocid(&left)<dlrDocid(&right) ){
+      dlrStep(&left);
+    }else if( dlrDocid(&right)<dlrDocid(&left) ){
+      dlrStep(&right);
+    }else{
+      if( nNear==0 ){
+        posListPhraseMerge(&left, &right, 0, 0, &writer);
+      }else{
+        /* This case occurs when two terms (simple terms or phrases) are
+         * connected by a NEAR operator, span (nNear+1). i.e.
+         *
+         *     '"terrible company" NEAR widget'
+         */
+        DataBuffer one = {0, 0, 0};
+        DataBuffer two = {0, 0, 0};
+
+        DLWriter dlwriter2;
+        DLReader dr1 = {0, 0, 0, 0, 0}; 
+        DLReader dr2 = {0, 0, 0, 0, 0};
+
+        dlwInit(&dlwriter2, iType, &one);
+        posListPhraseMerge(&right, &left, nNear-3+nPhrase, 1, &dlwriter2);
+        dlwInit(&dlwriter2, iType, &two);
+        posListPhraseMerge(&left, &right, nNear-1, 0, &dlwriter2);
+
+        if( one.nData) dlrInit(&dr1, iType, one.pData, one.nData);
+        if( two.nData) dlrInit(&dr2, iType, two.pData, two.nData);
+
+        if( !dlrAtEnd(&dr1) || !dlrAtEnd(&dr2) ){
+          PLReader pr1 = {0};
+          PLReader pr2 = {0};
+
+          PLWriter plwriter;
+          plwInit(&plwriter, &writer, dlrDocid(dlrAtEnd(&dr1)?&dr2:&dr1));
+
+          if( one.nData ) plrInit(&pr1, &dr1);
+          if( two.nData ) plrInit(&pr2, &dr2);
+          while( !plrAtEnd(&pr1) || !plrAtEnd(&pr2) ){
+            int iCompare = plrCompare(&pr1, &pr2);
+            switch( iCompare ){
+              case -1:
+                plwCopy(&plwriter, &pr1);
+                plrStep(&pr1);
+                break;
+              case 1:
+                plwCopy(&plwriter, &pr2);
+                plrStep(&pr2);
+                break;
+              case 0:
+                plwCopy(&plwriter, &pr1);
+                plrStep(&pr1);
+                plrStep(&pr2);
+                break;
+            }
+          }
+          plwTerminate(&plwriter);
+        }
+        dataBufferDestroy(&one);
+        dataBufferDestroy(&two);
+      }
+      dlrStep(&left);
+      dlrStep(&right);
     }
   }
-  if( p==*pp ) return SQLITE_ERROR;
-  *pnOut = nInt;
-  *pp = p;
-  return SQLITE_OK;
+
+  dlrDestroy(&left);
+  dlrDestroy(&right);
+  dlwDestroy(&writer);
 }
 
-/*
-** This function is called to allocate an array of Fts3Index structures
-** representing the indexes maintained by the current FTS table. FTS tables
-** always maintain the main "terms" index, but may also maintain one or
-** more "prefix" indexes, depending on the value of the "prefix=" parameter
-** (if any) specified as part of the CREATE VIRTUAL TABLE statement.
-**
-** Argument zParam is passed the value of the "prefix=" option if one was
-** specified, or NULL otherwise.
-**
-** If no error occurs, SQLITE_OK is returned and *apIndex set to point to
-** the allocated array. *pnIndex is set to the number of elements in the
-** array. If an error does occur, an SQLite error code is returned.
-**
-** Regardless of whether or not an error is returned, it is the responsibility
-** of the caller to call sqlite3_free() on the output array to free it.
-*/
-static int fts3PrefixParameter(
-  const char *zParam,             /* ABC in prefix=ABC parameter to parse */
-  int *pnIndex,                   /* OUT: size of *apIndex[] array */
-  struct Fts3Index **apIndex      /* OUT: Array of indexes for this table */
+/* We have two DL_DOCIDS doclists:  pLeft and pRight.
+** Write the intersection of these two doclists into pOut as a
+** DL_DOCIDS doclist.
+*/
+static void docListAndMerge(
+  const char *pLeft, int nLeft,
+  const char *pRight, int nRight,
+  DataBuffer *pOut      /* Write the combined doclist here */
 ){
-  struct Fts3Index *aIndex;       /* Allocated array */
-  int nIndex = 1;                 /* Number of entries in array */
+  DLReader left, right;
+  DLWriter writer;
+
+  if( nLeft==0 || nRight==0 ) return;
+
+  dlrInit(&left, DL_DOCIDS, pLeft, nLeft);
+  dlrInit(&right, DL_DOCIDS, pRight, nRight);
+  dlwInit(&writer, DL_DOCIDS, pOut);
 
-  if( zParam && zParam[0] ){
-    const char *p;
-    nIndex++;
-    for(p=zParam; *p; p++){
-      if( *p==',' ) nIndex++;
+  while( !dlrAtEnd(&left) && !dlrAtEnd(&right) ){
+    if( dlrDocid(&left)<dlrDocid(&right) ){
+      dlrStep(&left);
+    }else if( dlrDocid(&right)<dlrDocid(&left) ){
+      dlrStep(&right);
+    }else{
+      dlwAdd(&writer, dlrDocid(&left));
+      dlrStep(&left);
+      dlrStep(&right);
     }
   }
 
-  aIndex = sqlite3_malloc(sizeof(struct Fts3Index) * nIndex);
-  *apIndex = aIndex;
-  if( !aIndex ){
-    return SQLITE_NOMEM;
-  }
+  dlrDestroy(&left);
+  dlrDestroy(&right);
+  dlwDestroy(&writer);
+}
 
-  memset(aIndex, 0, sizeof(struct Fts3Index) * nIndex);
-  if( zParam ){
-    const char *p = zParam;
-    int i;
-    for(i=1; i<nIndex; i++){
-      int nPrefix = 0;
-      if( fts3GobbleInt(&p, &nPrefix) ) return SQLITE_ERROR;
-      assert( nPrefix>=0 );
-      if( nPrefix==0 ){
-        nIndex--;
-        i--;
-      }else{
-        aIndex[i].nPrefix = nPrefix;
-      }
-      p++;
-    }
-  }
-
-  *pnIndex = nIndex;
-  return SQLITE_OK;
-}
-
-/*
-** This function is called when initializing an FTS4 table that uses the
-** content=xxx option. It determines the number of and names of the columns
-** of the new FTS4 table.
-**
-** The third argument passed to this function is the value passed to the
-** config=xxx option (i.e. "xxx"). This function queries the database for
-** a table of that name. If found, the output variables are populated
-** as follows:
-**
-**   *pnCol:   Set to the number of columns table xxx has,
-**
-**   *pnStr:   Set to the total amount of space required to store a copy
-**             of each columns name, including the nul-terminator.
-**
-**   *pazCol:  Set to point to an array of *pnCol strings. Each string is
-**             the name of the corresponding column in table xxx. The array
-**             and its contents are allocated using a single allocation. It
-**             is the responsibility of the caller to free this allocation
-**             by eventually passing the *pazCol value to sqlite3_free().
-**
-** If the table cannot be found, an error code is returned and the output
-** variables are undefined. Or, if an OOM is encountered, SQLITE_NOMEM is
-** returned (and the output variables are undefined).
-*/
-static int fts3ContentColumns(
-  sqlite3 *db,                    /* Database handle */
-  const char *zDb,                /* Name of db (i.e. "main", "temp" etc.) */
-  const char *zTbl,               /* Name of content table */
-  const char ***pazCol,           /* OUT: Malloc'd array of column names */
-  int *pnCol,                     /* OUT: Size of array *pazCol */
-  int *pnStr,                     /* OUT: Bytes of string content */
-  char **pzErr                    /* OUT: error message */
+/* We have two DL_DOCIDS doclists:  pLeft and pRight.
+** Write the union of these two doclists into pOut as a
+** DL_DOCIDS doclist.
+*/
+static void docListOrMerge(
+  const char *pLeft, int nLeft,
+  const char *pRight, int nRight,
+  DataBuffer *pOut      /* Write the combined doclist here */
 ){
-  int rc = SQLITE_OK;             /* Return code */
-  char *zSql;                     /* "SELECT *" statement on zTbl */  
-  sqlite3_stmt *pStmt = 0;        /* Compiled version of zSql */
+  DLReader left, right;
+  DLWriter writer;
 
-  zSql = sqlite3_mprintf("SELECT * FROM %Q.%Q", zDb, zTbl);
-  if( !zSql ){
-    rc = SQLITE_NOMEM;
-  }else{
-    rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
-    if( rc!=SQLITE_OK ){
-      sqlite3Fts3ErrMsg(pzErr, "%s", sqlite3_errmsg(db));
-    }
+  if( nLeft==0 ){
+    if( nRight!=0 ) dataBufferAppend(pOut, pRight, nRight);
+    return;
+  }
+  if( nRight==0 ){
+    dataBufferAppend(pOut, pLeft, nLeft);
+    return;
   }
-  sqlite3_free(zSql);
 
-  if( rc==SQLITE_OK ){
-    const char **azCol;           /* Output array */
-    int nStr = 0;                 /* Size of all column names (incl. 0x00) */
-    int nCol;                     /* Number of table columns */
-    int i;                        /* Used to iterate through columns */
-
-    /* Loop through the returned columns. Set nStr to the number of bytes of
-    ** space required to store a copy of each column name, including the
-    ** nul-terminator byte.  */
-    nCol = sqlite3_column_count(pStmt);
-    for(i=0; i<nCol; i++){
-      const char *zCol = sqlite3_column_name(pStmt, i);
-      nStr += (int)strlen(zCol) + 1;
-    }
-
-    /* Allocate and populate the array to return. */
-    azCol = (const char **)sqlite3_malloc(sizeof(char *) * nCol + nStr);
-    if( azCol==0 ){
-      rc = SQLITE_NOMEM;
+  dlrInit(&left, DL_DOCIDS, pLeft, nLeft);
+  dlrInit(&right, DL_DOCIDS, pRight, nRight);
+  dlwInit(&writer, DL_DOCIDS, pOut);
+
+  while( !dlrAtEnd(&left) || !dlrAtEnd(&right) ){
+    if( dlrAtEnd(&right) ){
+      dlwAdd(&writer, dlrDocid(&left));
+      dlrStep(&left);
+    }else if( dlrAtEnd(&left) ){
+      dlwAdd(&writer, dlrDocid(&right));
+      dlrStep(&right);
+    }else if( dlrDocid(&left)<dlrDocid(&right) ){
+      dlwAdd(&writer, dlrDocid(&left));
+      dlrStep(&left);
+    }else if( dlrDocid(&right)<dlrDocid(&left) ){
+      dlwAdd(&writer, dlrDocid(&right));
+      dlrStep(&right);
     }else{
-      char *p = (char *)&azCol[nCol];
-      for(i=0; i<nCol; i++){
-        const char *zCol = sqlite3_column_name(pStmt, i);
-        int n = (int)strlen(zCol)+1;
-        memcpy(p, zCol, n);
-        azCol[i] = p;
-        p += n;
-      }
+      dlwAdd(&writer, dlrDocid(&left));
+      dlrStep(&left);
+      dlrStep(&right);
     }
-    sqlite3_finalize(pStmt);
-
-    /* Set the output variables. */
-    *pnCol = nCol;
-    *pnStr = nStr;
-    *pazCol = azCol;
   }
 
-  return rc;
+  dlrDestroy(&left);
+  dlrDestroy(&right);
+  dlwDestroy(&writer);
 }
 
-/*
-** This function is the implementation of both the xConnect and xCreate
-** methods of the FTS3 virtual table.
-**
-** The argv[] array contains the following:
-**
-**   argv[0]   -> module name  ("fts3" or "fts4")
-**   argv[1]   -> database name
-**   argv[2]   -> table name
-**   argv[...] -> "column name" and other module argument fields.
-*/
-static int fts3InitVtab(
-  int isCreate,                   /* True for xCreate, false for xConnect */
-  sqlite3 *db,                    /* The SQLite database connection */
-  void *pAux,                     /* Hash table containing tokenizers */
-  int argc,                       /* Number of elements in argv array */
-  const char * const *argv,       /* xCreate/xConnect argument array */
-  sqlite3_vtab **ppVTab,          /* Write the resulting vtab structure here */
-  char **pzErr                    /* Write any error message here */
+/* We have two DL_DOCIDS doclists:  pLeft and pRight.
+** Write into pOut as DL_DOCIDS doclist containing all documents that
+** occur in pLeft but not in pRight.
+*/
+static void docListExceptMerge(
+  const char *pLeft, int nLeft,
+  const char *pRight, int nRight,
+  DataBuffer *pOut      /* Write the combined doclist here */
 ){
-  Fts3Hash *pHash = (Fts3Hash *)pAux;
-  Fts3Table *p = 0;               /* Pointer to allocated vtab */
-  int rc = SQLITE_OK;             /* Return code */
-  int i;                          /* Iterator variable */
-  int nByte;                      /* Size of allocation used for *p */
-  int iCol;                       /* Column index */
-  int nString = 0;                /* Bytes required to hold all column names */
-  int nCol = 0;                   /* Number of columns in the FTS table */
-  char *zCsr;                     /* Space for holding column names */
-  int nDb;                        /* Bytes required to hold database name */
-  int nName;                      /* Bytes required to hold table name */
-  int isFts4 = (argv[0][3]=='4'); /* True for FTS4, false for FTS3 */
-  const char **aCol;              /* Array of column names */
-  sqlite3_tokenizer *pTokenizer = 0;        /* Tokenizer for this table */
-
-  int nIndex = 0;                 /* Size of aIndex[] array */
-  struct Fts3Index *aIndex = 0;   /* Array of indexes for this table */
-
-  /* The results of parsing supported FTS4 key=value options: */
-  int bNoDocsize = 0;             /* True to omit %_docsize table */
-  int bDescIdx = 0;               /* True to store descending indexes */
-  char *zPrefix = 0;              /* Prefix parameter value (or NULL) */
-  char *zCompress = 0;            /* compress=? parameter (or NULL) */
-  char *zUncompress = 0;          /* uncompress=? parameter (or NULL) */
-  char *zContent = 0;             /* content=? parameter (or NULL) */
-  char *zLanguageid = 0;          /* languageid=? parameter (or NULL) */
-  char **azNotindexed = 0;        /* The set of notindexed= columns */
-  int nNotindexed = 0;            /* Size of azNotindexed[] array */
-
-  assert( strlen(argv[0])==4 );
-  assert( (sqlite3_strnicmp(argv[0], "fts4", 4)==0 && isFts4)
-       || (sqlite3_strnicmp(argv[0], "fts3", 4)==0 && !isFts4)
-  );
-
-  nDb = (int)strlen(argv[1]) + 1;
-  nName = (int)strlen(argv[2]) + 1;
+  DLReader left, right;
+  DLWriter writer;
 
-  nByte = sizeof(const char *) * (argc-2);
-  aCol = (const char **)sqlite3_malloc(nByte);
-  if( aCol ){
-    memset((void*)aCol, 0, nByte);
-    azNotindexed = (char **)sqlite3_malloc(nByte);
-  }
-  if( azNotindexed ){
-    memset(azNotindexed, 0, nByte);
-  }
-  if( !aCol || !azNotindexed ){
-    rc = SQLITE_NOMEM;
-    goto fts3_init_out;
+  if( nLeft==0 ) return;
+  if( nRight==0 ){
+    dataBufferAppend(pOut, pLeft, nLeft);
+    return;
   }
 
-  /* Loop through all of the arguments passed by the user to the FTS3/4
-  ** module (i.e. all the column names and special arguments). This loop
-  ** does the following:
-  **
-  **   + Figures out the number of columns the FTSX table will have, and
-  **     the number of bytes of space that must be allocated to store copies
-  **     of the column names.
-  **
-  **   + If there is a tokenizer specification included in the arguments,
-  **     initializes the tokenizer pTokenizer.
-  */
-  for(i=3; rc==SQLITE_OK && i<argc; i++){
-    char const *z = argv[i];
-    int nKey;
-    char *zVal;
-
-    /* Check if this is a tokenizer specification */
-    if( !pTokenizer 
-     && strlen(z)>8
-     && 0==sqlite3_strnicmp(z, "tokenize", 8) 
-     && 0==sqlite3Fts3IsIdChar(z[8])
-    ){
-      rc = sqlite3Fts3InitTokenizer(pHash, &z[9], &pTokenizer, pzErr);
-    }
-
-    /* Check if it is an FTS4 special argument. */
-    else if( isFts4 && fts3IsSpecialColumn(z, &nKey, &zVal) ){
-      struct Fts4Option {
-        const char *zOpt;
-        int nOpt;
-      } aFts4Opt[] = {
-        { "matchinfo",   9 },     /* 0 -> MATCHINFO */
-        { "prefix",      6 },     /* 1 -> PREFIX */
-        { "compress",    8 },     /* 2 -> COMPRESS */
-        { "uncompress", 10 },     /* 3 -> UNCOMPRESS */
-        { "order",       5 },     /* 4 -> ORDER */
-        { "content",     7 },     /* 5 -> CONTENT */
-        { "languageid", 10 },     /* 6 -> LANGUAGEID */
-        { "notindexed", 10 }      /* 7 -> NOTINDEXED */
-      };
-
-      int iOpt;
-      if( !zVal ){
-        rc = SQLITE_NOMEM;
-      }else{
-        for(iOpt=0; iOpt<SizeofArray(aFts4Opt); iOpt++){
-          struct Fts4Option *pOp = &aFts4Opt[iOpt];
-          if( nKey==pOp->nOpt && !sqlite3_strnicmp(z, pOp->zOpt, pOp->nOpt) ){
-            break;
-          }
-        }
-        switch( iOpt ){
-          case 0:               /* MATCHINFO */
-            if( strlen(zVal)!=4 || sqlite3_strnicmp(zVal, "fts3", 4) ){
-              sqlite3Fts3ErrMsg(pzErr, "unrecognized matchinfo: %s", zVal);
-              rc = SQLITE_ERROR;
-            }
-            bNoDocsize = 1;
-            break;
+  dlrInit(&left, DL_DOCIDS, pLeft, nLeft);
+  dlrInit(&right, DL_DOCIDS, pRight, nRight);
+  dlwInit(&writer, DL_DOCIDS, pOut);
+
+  while( !dlrAtEnd(&left) ){
+    while( !dlrAtEnd(&right) && dlrDocid(&right)<dlrDocid(&left) ){
+      dlrStep(&right);
+    }
+    if( dlrAtEnd(&right) || dlrDocid(&left)<dlrDocid(&right) ){
+      dlwAdd(&writer, dlrDocid(&left));
+    }
+    dlrStep(&left);
+  }
+
+  dlrDestroy(&left);
+  dlrDestroy(&right);
+  dlwDestroy(&writer);
+}
+
+static char *string_dup_n(const char *s, int n){
+  char *str = sqlite3_malloc(n + 1);
+  memcpy(str, s, n);
+  str[n] = '\0';
+  return str;
+}
+
+/* Duplicate a string; the caller must free() the returned string.
+ * (We don't use strdup() since it is not part of the standard C library and
+ * may not be available everywhere.) */
+static char *string_dup(const char *s){
+  return string_dup_n(s, strlen(s));
+}
+
+/* Format a string, replacing each occurrence of the % character with
+ * zDb.zName.  This may be more convenient than sqlite_mprintf()
+ * when one string is used repeatedly in a format string.
+ * The caller must free() the returned string. */
+static char *string_format(const char *zFormat,
+                           const char *zDb, const char *zName){
+  const char *p;
+  size_t len = 0;
+  size_t nDb = strlen(zDb);
+  size_t nName = strlen(zName);
+  size_t nFullTableName = nDb+1+nName;
+  char *result;
+  char *r;
+
+  /* first compute length needed */
+  for(p = zFormat ; *p ; ++p){
+    len += (*p=='%' ? nFullTableName : 1);
+  }
+  len += 1;  /* for null terminator */
+
+  r = result = sqlite3_malloc(len);
+  for(p = zFormat; *p; ++p){
+    if( *p=='%' ){
+      memcpy(r, zDb, nDb);
+      r += nDb;
+      *r++ = '.';
+      memcpy(r, zName, nName);
+      r += nName;
+    } else {
+      *r++ = *p;
+    }
+  }
+  *r++ = '\0';
+  assert( r == result + len );
+  return result;
+}
+
+static int sql_exec(sqlite3 *db, const char *zDb, const char *zName,
+                    const char *zFormat){
+  char *zCommand = string_format(zFormat, zDb, zName);
+  int rc;
+  FTSTRACE(("FTS3 sql: %s\n", zCommand));
+  rc = sqlite3_exec(db, zCommand, NULL, 0, NULL);
+  sqlite3_free(zCommand);
+  return rc;
+}
 
-          case 1:               /* PREFIX */
-            sqlite3_free(zPrefix);
-            zPrefix = zVal;
-            zVal = 0;
-            break;
+static int sql_prepare(sqlite3 *db, const char *zDb, const char *zName,
+                       sqlite3_stmt **ppStmt, const char *zFormat){
+  char *zCommand = string_format(zFormat, zDb, zName);
+  int rc;
+  FTSTRACE(("FTS3 prepare: %s\n", zCommand));
+  rc = sqlite3_prepare_v2(db, zCommand, -1, ppStmt, NULL);
+  sqlite3_free(zCommand);
+  return rc;
+}
 
-          case 2:               /* COMPRESS */
-            sqlite3_free(zCompress);
-            zCompress = zVal;
-            zVal = 0;
-            break;
+/* end utility functions */
 
-          case 3:               /* UNCOMPRESS */
-            sqlite3_free(zUncompress);
-            zUncompress = zVal;
-            zVal = 0;
-            break;
+/* Forward reference */
+typedef struct fulltext_vtab fulltext_vtab;
 
-          case 4:               /* ORDER */
-            if( (strlen(zVal)!=3 || sqlite3_strnicmp(zVal, "asc", 3)) 
-             && (strlen(zVal)!=4 || sqlite3_strnicmp(zVal, "desc", 4)) 
-            ){
-              sqlite3Fts3ErrMsg(pzErr, "unrecognized order: %s", zVal);
-              rc = SQLITE_ERROR;
-            }
-            bDescIdx = (zVal[0]=='d' || zVal[0]=='D');
-            break;
+/*
+** An instance of the following structure keeps track of generated
+** matching-word offset information and snippets.
+*/
+typedef struct Snippet {
+  int nMatch;     /* Total number of matches */
+  int nAlloc;     /* Space allocated for aMatch[] */
+  struct snippetMatch { /* One entry for each matching term */
+    char snStatus;       /* Status flag for use while constructing snippets */
+    short int iCol;      /* The column that contains the match */
+    short int iTerm;     /* The index in Query.pTerms[] of the matching term */
+    int iToken;          /* The index of the matching document token */
+    short int nByte;     /* Number of bytes in the term */
+    int iStart;          /* The offset to the first character of the term */
+  } *aMatch;      /* Points to space obtained from malloc */
+  char *zOffset;  /* Text rendering of aMatch[] */
+  int nOffset;    /* strlen(zOffset) */
+  char *zSnippet; /* Snippet text */
+  int nSnippet;   /* strlen(zSnippet) */
+} Snippet;
+
+
+typedef enum QueryType {
+  QUERY_GENERIC,   /* table scan */
+  QUERY_DOCID,     /* lookup by docid */
+  QUERY_FULLTEXT   /* QUERY_FULLTEXT + [i] is a full-text search for column i*/
+} QueryType;
+
+typedef enum fulltext_statement {
+  CONTENT_INSERT_STMT,
+  CONTENT_SELECT_STMT,
+  CONTENT_UPDATE_STMT,
+  CONTENT_DELETE_STMT,
+  CONTENT_EXISTS_STMT,
+
+  BLOCK_INSERT_STMT,
+  BLOCK_SELECT_STMT,
+  BLOCK_DELETE_STMT,
+  BLOCK_DELETE_ALL_STMT,
+
+  SEGDIR_MAX_INDEX_STMT,
+  SEGDIR_SET_STMT,
+  SEGDIR_SELECT_LEVEL_STMT,
+  SEGDIR_SPAN_STMT,
+  SEGDIR_DELETE_STMT,
+  SEGDIR_SELECT_SEGMENT_STMT,
+  SEGDIR_SELECT_ALL_STMT,
+  SEGDIR_DELETE_ALL_STMT,
+  SEGDIR_COUNT_STMT,
+
+  MAX_STMT                     /* Always at end! */
+} fulltext_statement;
+
+/* These must exactly match the enum above. */
+/* TODO(shess): Is there some risk that a statement will be used in two
+** cursors at once, e.g.  if a query joins a virtual table to itself?
+** If so perhaps we should move some of these to the cursor object.
+*/
+static const char *const fulltext_zStatement[MAX_STMT] = {
+  /* CONTENT_INSERT */ NULL,  /* generated in contentInsertStatement() */
+  /* CONTENT_SELECT */ NULL,  /* generated in contentSelectStatement() */
+  /* CONTENT_UPDATE */ NULL,  /* generated in contentUpdateStatement() */
+  /* CONTENT_DELETE */ "delete from %_content where docid = ?",
+  /* CONTENT_EXISTS */ "select docid from %_content limit 1",
+
+  /* BLOCK_INSERT */
+  "insert into %_segments (blockid, block) values (null, ?)",
+  /* BLOCK_SELECT */ "select block from %_segments where blockid = ?",
+  /* BLOCK_DELETE */ "delete from %_segments where blockid between ? and ?",
+  /* BLOCK_DELETE_ALL */ "delete from %_segments",
+
+  /* SEGDIR_MAX_INDEX */ "select max(idx) from %_segdir where level = ?",
+  /* SEGDIR_SET */ "insert into %_segdir values (?, ?, ?, ?, ?, ?)",
+  /* SEGDIR_SELECT_LEVEL */
+  "select start_block, leaves_end_block, root from %_segdir "
+  " where level = ? order by idx",
+  /* SEGDIR_SPAN */
+  "select min(start_block), max(end_block) from %_segdir "
+  " where level = ? and start_block <> 0",
+  /* SEGDIR_DELETE */ "delete from %_segdir where level = ?",
 
-          case 5:              /* CONTENT */
-            sqlite3_free(zContent);
-            zContent = zVal;
-            zVal = 0;
-            break;
+  /* NOTE(shess): The first three results of the following two
+  ** statements must match.
+  */
+  /* SEGDIR_SELECT_SEGMENT */
+  "select start_block, leaves_end_block, root from %_segdir "
+  " where level = ? and idx = ?",
+  /* SEGDIR_SELECT_ALL */
+  "select start_block, leaves_end_block, root from %_segdir "
+  " order by level desc, idx asc",
+  /* SEGDIR_DELETE_ALL */ "delete from %_segdir",
+  /* SEGDIR_COUNT */ "select count(*), ifnull(max(level),0) from %_segdir",
+};
 
-          case 6:              /* LANGUAGEID */
-            assert( iOpt==6 );
-            sqlite3_free(zLanguageid);
-            zLanguageid = zVal;
-            zVal = 0;
-            break;
+/*
+** A connection to a fulltext index is an instance of the following
+** structure.  The xCreate and xConnect methods create an instance
+** of this structure and xDestroy and xDisconnect free that instance.
+** All other methods receive a pointer to the structure as one of their
+** arguments.
+*/
+struct fulltext_vtab {
+  sqlite3_vtab base;               /* Base class used by SQLite core */
+  sqlite3 *db;                     /* The database connection */
+  const char *zDb;                 /* logical database name */
+  const char *zName;               /* virtual table name */
+  int nColumn;                     /* number of columns in virtual table */
+  char **azColumn;                 /* column names.  malloced */
+  char **azContentColumn;          /* column names in content table; malloced */
+  sqlite3_tokenizer *pTokenizer;   /* tokenizer for inserts and queries */
 
-          case 7:              /* NOTINDEXED */
-            azNotindexed[nNotindexed++] = zVal;
-            zVal = 0;
-            break;
+  /* Precompiled statements which we keep as long as the table is
+  ** open.
+  */
+  sqlite3_stmt *pFulltextStatements[MAX_STMT];
 
-          default:
-            assert( iOpt==SizeofArray(aFts4Opt) );
-            sqlite3Fts3ErrMsg(pzErr, "unrecognized parameter: %s", z);
-            rc = SQLITE_ERROR;
-            break;
-        }
-        sqlite3_free(zVal);
-      }
-    }
+  /* Precompiled statements used for segment merges.  We run a
+  ** separate select across the leaf level of each tree being merged.
+  */
+  sqlite3_stmt *pLeafSelectStmts[MERGE_COUNT];
+  /* The statement used to prepare pLeafSelectStmts. */
+#define LEAF_SELECT \
+  "select block from %_segments where blockid between ? and ? order by blockid"
+
+  /* These buffer pending index updates during transactions.
+  ** nPendingData estimates the memory size of the pending data.  It
+  ** doesn't include the hash-bucket overhead, nor any malloc
+  ** overhead.  When nPendingData exceeds kPendingThreshold, the
+  ** buffer is flushed even before the transaction closes.
+  ** pendingTerms stores the data, and is only valid when nPendingData
+  ** is >=0 (nPendingData<0 means pendingTerms has not been
+  ** initialized).  iPrevDocid is the last docid written, used to make
+  ** certain we're inserting in sorted order.
+  */
+  int nPendingData;
+#define kPendingThreshold (1*1024*1024)
+  sqlite_int64 iPrevDocid;
+  fts3Hash pendingTerms;
+};
 
-    /* Otherwise, the argument is a column name. */
-    else {
-      nString += (int)(strlen(z) + 1);
-      aCol[nCol++] = z;
-    }
-  }
+/*
+** When the core wants to do a query, it create a cursor using a
+** call to xOpen.  This structure is an instance of a cursor.  It
+** is destroyed by xClose.
+*/
+typedef struct fulltext_cursor {
+  sqlite3_vtab_cursor base;        /* Base class used by SQLite core */
+  QueryType iCursorType;           /* Copy of sqlite3_index_info.idxNum */
+  sqlite3_stmt *pStmt;             /* Prepared statement in use by the cursor */
+  int eof;                         /* True if at End Of Results */
+  Fts3Expr *pExpr;                 /* Parsed MATCH query string */
+  Snippet snippet;                 /* Cached snippet for the current row */
+  int iColumn;                     /* Column being searched */
+  DataBuffer result;               /* Doclist results from fulltextQuery */
+  DLReader reader;                 /* Result reader if result not empty */
+} fulltext_cursor;
+
+static fulltext_vtab *cursor_vtab(fulltext_cursor *c){
+  return (fulltext_vtab *) c->base.pVtab;
+}
+
+static const sqlite3_module fts3Module;   /* forward declaration */
+
+/* Return a dynamically generated statement of the form
+ *   insert into %_content (docid, ...) values (?, ...)
+ */
+static const char *contentInsertStatement(fulltext_vtab *v){
+  StringBuffer sb;
+  int i;
 
-  /* If a content=xxx option was specified, the following:
-  **
-  **   1. Ignore any compress= and uncompress= options.
-  **
-  **   2. If no column names were specified as part of the CREATE VIRTUAL
-  **      TABLE statement, use all columns from the content table.
-  */
-  if( rc==SQLITE_OK && zContent ){
-    sqlite3_free(zCompress); 
-    sqlite3_free(zUncompress); 
-    zCompress = 0;
-    zUncompress = 0;
-    if( nCol==0 ){
-      sqlite3_free((void*)aCol); 
-      aCol = 0;
-      rc = fts3ContentColumns(db, argv[1], zContent,&aCol,&nCol,&nString,pzErr);
-
-      /* If a languageid= option was specified, remove the language id
-      ** column from the aCol[] array. */ 
-      if( rc==SQLITE_OK && zLanguageid ){
-        int j;
-        for(j=0; j<nCol; j++){
-          if( sqlite3_stricmp(zLanguageid, aCol[j])==0 ){
-            int k;
-            for(k=j; k<nCol; k++) aCol[k] = aCol[k+1];
-            nCol--;
-            break;
-          }
-        }
-      }
-    }
-  }
-  if( rc!=SQLITE_OK ) goto fts3_init_out;
+  initStringBuffer(&sb);
+  append(&sb, "insert into %_content (docid, ");
+  appendList(&sb, v->nColumn, v->azContentColumn);
+  append(&sb, ") values (?");
+  for(i=0; i<v->nColumn; ++i)
+    append(&sb, ", ?");
+  append(&sb, ")");
+  return stringBufferData(&sb);
+}
+
+/* Return a dynamically generated statement of the form
+ *   select <content columns> from %_content where docid = ?
+ */
+static const char *contentSelectStatement(fulltext_vtab *v){
+  StringBuffer sb;
+  initStringBuffer(&sb);
+  append(&sb, "SELECT ");
+  appendList(&sb, v->nColumn, v->azContentColumn);
+  append(&sb, " FROM %_content WHERE docid = ?");
+  return stringBufferData(&sb);
+}
+
+/* Return a dynamically generated statement of the form
+ *   update %_content set [col_0] = ?, [col_1] = ?, ...
+ *                    where docid = ?
+ */
+static const char *contentUpdateStatement(fulltext_vtab *v){
+  StringBuffer sb;
+  int i;
 
-  if( nCol==0 ){
-    assert( nString==0 );
-    aCol[0] = "content";
-    nString = 8;
-    nCol = 1;
-  }
-
-  if( pTokenizer==0 ){
-    rc = sqlite3Fts3InitTokenizer(pHash, "simple", &pTokenizer, pzErr);
-    if( rc!=SQLITE_OK ) goto fts3_init_out;
-  }
-  assert( pTokenizer );
-
-  rc = fts3PrefixParameter(zPrefix, &nIndex, &aIndex);
-  if( rc==SQLITE_ERROR ){
-    assert( zPrefix );
-    sqlite3Fts3ErrMsg(pzErr, "error parsing prefix parameter: %s", zPrefix);
-  }
-  if( rc!=SQLITE_OK ) goto fts3_init_out;
-
-  /* Allocate and populate the Fts3Table structure. */
-  nByte = sizeof(Fts3Table) +                  /* Fts3Table */
-          nCol * sizeof(char *) +              /* azColumn */
-          nIndex * sizeof(struct Fts3Index) +  /* aIndex */
-          nCol * sizeof(u8) +                  /* abNotindexed */
-          nName +                              /* zName */
-          nDb +                                /* zDb */
-          nString;                             /* Space for azColumn strings */
-  p = (Fts3Table*)sqlite3_malloc(nByte);
-  if( p==0 ){
-    rc = SQLITE_NOMEM;
-    goto fts3_init_out;
-  }
-  memset(p, 0, nByte);
-  p->db = db;
-  p->nColumn = nCol;
-  p->nPendingData = 0;
-  p->azColumn = (char **)&p[1];
-  p->pTokenizer = pTokenizer;
-  p->nMaxPendingData = FTS3_MAX_PENDING_DATA;
-  p->bHasDocsize = (isFts4 && bNoDocsize==0);
-  p->bHasStat = (u8)isFts4;
-  p->bFts4 = (u8)isFts4;
-  p->bDescIdx = (u8)bDescIdx;
-  p->nAutoincrmerge = 0xff;   /* 0xff means setting unknown */
-  p->zContentTbl = zContent;
-  p->zLanguageid = zLanguageid;
-  zContent = 0;
-  zLanguageid = 0;
-  TESTONLY( p->inTransaction = -1 );
-  TESTONLY( p->mxSavepoint = -1 );
-
-  p->aIndex = (struct Fts3Index *)&p->azColumn[nCol];
-  memcpy(p->aIndex, aIndex, sizeof(struct Fts3Index) * nIndex);
-  p->nIndex = nIndex;
-  for(i=0; i<nIndex; i++){
-    fts3HashInit(&p->aIndex[i].hPending, FTS3_HASH_STRING, 1);
-  }
-  p->abNotindexed = (u8 *)&p->aIndex[nIndex];
-
-  /* Fill in the zName and zDb fields of the vtab structure. */
-  zCsr = (char *)&p->abNotindexed[nCol];
-  p->zName = zCsr;
-  memcpy(zCsr, argv[2], nName);
-  zCsr += nName;
-  p->zDb = zCsr;
-  memcpy(zCsr, argv[1], nDb);
-  zCsr += nDb;
-
-  /* Fill in the azColumn array */
-  for(iCol=0; iCol<nCol; iCol++){
-    char *z; 
-    int n = 0;
-    z = (char *)sqlite3Fts3NextToken(aCol[iCol], &n);
-    if( n>0 ){
-      memcpy(zCsr, z, n);
-    }
-    zCsr[n] = '\0';
-    sqlite3Fts3Dequote(zCsr);
-    p->azColumn[iCol] = zCsr;
-    zCsr += n+1;
-    assert( zCsr <= &((char *)p)[nByte] );
-  }
-
-  /* Fill in the abNotindexed array */
-  for(iCol=0; iCol<nCol; iCol++){
-    int n = (int)strlen(p->azColumn[iCol]);
-    for(i=0; i<nNotindexed; i++){
-      char *zNot = azNotindexed[i];
-      if( zNot && n==(int)strlen(zNot)
-       && 0==sqlite3_strnicmp(p->azColumn[iCol], zNot, n) 
-      ){
-        p->abNotindexed[iCol] = 1;
-        sqlite3_free(zNot);
-        azNotindexed[i] = 0;
-      }
-    }
-  }
-  for(i=0; i<nNotindexed; i++){
-    if( azNotindexed[i] ){
-      sqlite3Fts3ErrMsg(pzErr, "no such column: %s", azNotindexed[i]);
-      rc = SQLITE_ERROR;
-    }
+  initStringBuffer(&sb);
+  append(&sb, "update %_content set ");
+  for(i=0; i<v->nColumn; ++i) {
+    if( i>0 ){
+      append(&sb, ", ");
+    }
+    append(&sb, v->azContentColumn[i]);
+    append(&sb, " = ?");
+  }
+  append(&sb, " where docid = ?");
+  return stringBufferData(&sb);
+}
+
+/* Puts a freshly-prepared statement determined by iStmt in *ppStmt.
+** If the indicated statement has never been prepared, it is prepared
+** and cached, otherwise the cached version is reset.
+*/
+static int sql_get_statement(fulltext_vtab *v, fulltext_statement iStmt,
+                             sqlite3_stmt **ppStmt){
+  assert( iStmt<MAX_STMT );
+  if( v->pFulltextStatements[iStmt]==NULL ){
+    const char *zStmt;
+    int rc;
+    switch( iStmt ){
+      case CONTENT_INSERT_STMT:
+        zStmt = contentInsertStatement(v); break;
+      case CONTENT_SELECT_STMT:
+        zStmt = contentSelectStatement(v); break;
+      case CONTENT_UPDATE_STMT:
+        zStmt = contentUpdateStatement(v); break;
+      default:
+        zStmt = fulltext_zStatement[iStmt];
+    }
+    rc = sql_prepare(v->db, v->zDb, v->zName, &v->pFulltextStatements[iStmt],
+                         zStmt);
+    if( zStmt != fulltext_zStatement[iStmt]) sqlite3_free((void *) zStmt);
+    if( rc!=SQLITE_OK ) return rc;
+  } else {
+    int rc = sqlite3_reset(v->pFulltextStatements[iStmt]);
+    if( rc!=SQLITE_OK ) return rc;
   }
 
-  if( rc==SQLITE_OK && (zCompress==0)!=(zUncompress==0) ){
-    char const *zMiss = (zCompress==0 ? "compress" : "uncompress");
-    rc = SQLITE_ERROR;
-    sqlite3Fts3ErrMsg(pzErr, "missing %s parameter in fts4 constructor", zMiss);
-  }
-  p->zReadExprlist = fts3ReadExprList(p, zUncompress, &rc);
-  p->zWriteExprlist = fts3WriteExprList(p, zCompress, &rc);
-  if( rc!=SQLITE_OK ) goto fts3_init_out;
+  *ppStmt = v->pFulltextStatements[iStmt];
+  return SQLITE_OK;
+}
 
-  /* If this is an xCreate call, create the underlying tables in the 
-  ** database. TODO: For xConnect(), it could verify that said tables exist.
-  */
-  if( isCreate ){
-    rc = fts3CreateTables(p);
+/* Like sqlite3_step(), but convert SQLITE_DONE to SQLITE_OK and
+** SQLITE_ROW to SQLITE_ERROR.  Useful for statements like UPDATE,
+** where we expect no results.
+*/
+static int sql_single_step(sqlite3_stmt *s){
+  int rc = sqlite3_step(s);
+  return (rc==SQLITE_DONE) ? SQLITE_OK : rc;
+}
+
+/* Like sql_get_statement(), but for special replicated LEAF_SELECT
+** statements.  idx -1 is a special case for an uncached version of
+** the statement (used in the optimize implementation).
+*/
+/* TODO(shess) Write version for generic statements and then share
+** that between the cached-statement functions.
+*/
+static int sql_get_leaf_statement(fulltext_vtab *v, int idx,
+                                  sqlite3_stmt **ppStmt){
+  assert( idx>=-1 && idx<MERGE_COUNT );
+  if( idx==-1 ){
+    return sql_prepare(v->db, v->zDb, v->zName, ppStmt, LEAF_SELECT);
+  }else if( v->pLeafSelectStmts[idx]==NULL ){
+    int rc = sql_prepare(v->db, v->zDb, v->zName, &v->pLeafSelectStmts[idx],
+                         LEAF_SELECT);
+    if( rc!=SQLITE_OK ) return rc;
+  }else{
+    int rc = sqlite3_reset(v->pLeafSelectStmts[idx]);
+    if( rc!=SQLITE_OK ) return rc;
   }
 
-  /* Check to see if a legacy fts3 table has been "upgraded" by the
-  ** addition of a %_stat table so that it can use incremental merge.
-  */
-  if( !isFts4 && !isCreate ){
-    p->bHasStat = 2;
-  }
+  *ppStmt = v->pLeafSelectStmts[idx];
+  return SQLITE_OK;
+}
 
-  /* Figure out the page-size for the database. This is required in order to
-  ** estimate the cost of loading large doclists from the database.  */
-  fts3DatabasePageSize(&rc, p);
-  p->nNodeSize = p->nPgsz-35;
+/* insert into %_content (docid, ...) values ([docid], [pValues])
+** If the docid contains SQL NULL, then a unique docid will be
+** generated.
+*/
+static int content_insert(fulltext_vtab *v, sqlite3_value *docid,
+                          sqlite3_value **pValues){
+  sqlite3_stmt *s;
+  int i;
+  int rc = sql_get_statement(v, CONTENT_INSERT_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-  /* Declare the table schema to SQLite. */
-  fts3DeclareVtab(&rc, p);
+  rc = sqlite3_bind_value(s, 1, docid);
+  if( rc!=SQLITE_OK ) return rc;
 
-fts3_init_out:
-  sqlite3_free(zPrefix);
-  sqlite3_free(aIndex);
-  sqlite3_free(zCompress);
-  sqlite3_free(zUncompress);
-  sqlite3_free(zContent);
-  sqlite3_free(zLanguageid);
-  for(i=0; i<nNotindexed; i++) sqlite3_free(azNotindexed[i]);
-  sqlite3_free((void *)aCol);
-  sqlite3_free((void *)azNotindexed);
-  if( rc!=SQLITE_OK ){
-    if( p ){
-      fts3DisconnectMethod((sqlite3_vtab *)p);
-    }else if( pTokenizer ){
-      pTokenizer->pModule->xDestroy(pTokenizer);
-    }
-  }else{
-    assert( p->pSegments==0 );
-    *ppVTab = &p->base;
+  for(i=0; i<v->nColumn; ++i){
+    rc = sqlite3_bind_value(s, 2+i, pValues[i]);
+    if( rc!=SQLITE_OK ) return rc;
   }
-  return rc;
-}
 
-/*
-** The xConnect() and xCreate() methods for the virtual table. All the
-** work is done in function fts3InitVtab().
-*/
-static int fts3ConnectMethod(
-  sqlite3 *db,                    /* Database connection */
-  void *pAux,                     /* Pointer to tokenizer hash table */
-  int argc,                       /* Number of elements in argv array */
-  const char * const *argv,       /* xCreate/xConnect argument array */
-  sqlite3_vtab **ppVtab,          /* OUT: New sqlite3_vtab object */
-  char **pzErr                    /* OUT: sqlite3_malloc'd error message */
-){
-  return fts3InitVtab(0, db, pAux, argc, argv, ppVtab, pzErr);
-}
-static int fts3CreateMethod(
-  sqlite3 *db,                    /* Database connection */
-  void *pAux,                     /* Pointer to tokenizer hash table */
-  int argc,                       /* Number of elements in argv array */
-  const char * const *argv,       /* xCreate/xConnect argument array */
-  sqlite3_vtab **ppVtab,          /* OUT: New sqlite3_vtab object */
-  char **pzErr                    /* OUT: sqlite3_malloc'd error message */
-){
-  return fts3InitVtab(1, db, pAux, argc, argv, ppVtab, pzErr);
+  return sql_single_step(s);
 }
 
-/*
-** Set the pIdxInfo->estimatedRows variable to nRow. Unless this
-** extension is currently being used by a version of SQLite too old to
-** support estimatedRows. In that case this function is a no-op.
-*/
-static void fts3SetEstimatedRows(sqlite3_index_info *pIdxInfo, i64 nRow){
-#if SQLITE_VERSION_NUMBER>=3008002
-  if( sqlite3_libversion_number()>=3008002 ){
-    pIdxInfo->estimatedRows = nRow;
+/* update %_content set col0 = pValues[0], col1 = pValues[1], ...
+ *                  where docid = [iDocid] */
+static int content_update(fulltext_vtab *v, sqlite3_value **pValues,
+                          sqlite_int64 iDocid){
+  sqlite3_stmt *s;
+  int i;
+  int rc = sql_get_statement(v, CONTENT_UPDATE_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  for(i=0; i<v->nColumn; ++i){
+    rc = sqlite3_bind_value(s, 1+i, pValues[i]);
+    if( rc!=SQLITE_OK ) return rc;
   }
-#endif
+
+  rc = sqlite3_bind_int64(s, 1+v->nColumn, iDocid);
+  if( rc!=SQLITE_OK ) return rc;
+
+  return sql_single_step(s);
 }
 
-/*
-** Set the SQLITE_INDEX_SCAN_UNIQUE flag in pIdxInfo->flags. Unless this
-** extension is currently being used by a version of SQLite too old to
-** support index-info flags. In that case this function is a no-op.
-*/
-static void fts3SetUniqueFlag(sqlite3_index_info *pIdxInfo){
-#if SQLITE_VERSION_NUMBER>=3008012
-  if( sqlite3_libversion_number()>=3008012 ){
-    pIdxInfo->idxFlags |= SQLITE_INDEX_SCAN_UNIQUE;
+static void freeStringArray(int nString, const char **pString){
+  int i;
+
+  for (i=0 ; i < nString ; ++i) {
+    if( pString[i]!=NULL ) sqlite3_free((void *) pString[i]);
   }
-#endif
+  sqlite3_free((void *) pString);
 }
 
-/* 
-** Implementation of the xBestIndex method for FTS3 tables. There
-** are three possible strategies, in order of preference:
-**
-**   1. Direct lookup by rowid or docid. 
-**   2. Full-text search using a MATCH operator on a non-docid column.
-**   3. Linear scan of %_content table.
-*/
-static int fts3BestIndexMethod(sqlite3_vtab *pVTab, sqlite3_index_info *pInfo){
-  Fts3Table *p = (Fts3Table *)pVTab;
-  int i;                          /* Iterator variable */
-  int iCons = -1;                 /* Index of constraint to use */
-
-  int iLangidCons = -1;           /* Index of langid=x constraint, if present */
-  int iDocidGe = -1;              /* Index of docid>=x constraint, if present */
-  int iDocidLe = -1;              /* Index of docid<=x constraint, if present */
-  int iIdx;
-
-  /* By default use a full table scan. This is an expensive option,
-  ** so search through the constraints to see if a more efficient 
-  ** strategy is possible.
-  */
-  pInfo->idxNum = FTS3_FULLSCAN_SEARCH;
-  pInfo->estimatedCost = 5000000;
-  for(i=0; i<pInfo->nConstraint; i++){
-    int bDocid;                 /* True if this constraint is on docid */
-    struct sqlite3_index_constraint *pCons = &pInfo->aConstraint[i];
-    if( pCons->usable==0 ){
-      if( pCons->op==SQLITE_INDEX_CONSTRAINT_MATCH ){
-        /* There exists an unusable MATCH constraint. This means that if
-        ** the planner does elect to use the results of this call as part
-        ** of the overall query plan the user will see an "unable to use
-        ** function MATCH in the requested context" error. To discourage
-        ** this, return a very high cost here.  */
-        pInfo->idxNum = FTS3_FULLSCAN_SEARCH;
-        pInfo->estimatedCost = 1e50;
-        fts3SetEstimatedRows(pInfo, ((sqlite3_int64)1) << 50);
-        return SQLITE_OK;
-      }
-      continue;
-    }
+/* select * from %_content where docid = [iDocid]
+ * The caller must delete the returned array and all strings in it.
+ * null fields will be NULL in the returned array.
+ *
+ * TODO: Perhaps we should return pointer/length strings here for consistency
+ * with other code which uses pointer/length. */
+static int content_select(fulltext_vtab *v, sqlite_int64 iDocid,
+                          const char ***pValues){
+  sqlite3_stmt *s;
+  const char **values;
+  int i;
+  int rc;
 
-    bDocid = (pCons->iColumn<0 || pCons->iColumn==p->nColumn+1);
+  *pValues = NULL;
 
-    /* A direct lookup on the rowid or docid column. Assign a cost of 1.0. */
-    if( iCons<0 && pCons->op==SQLITE_INDEX_CONSTRAINT_EQ && bDocid ){
-      pInfo->idxNum = FTS3_DOCID_SEARCH;
-      pInfo->estimatedCost = 1.0;
-      iCons = i;
-    }
-
-    /* A MATCH constraint. Use a full-text search.
-    **
-    ** If there is more than one MATCH constraint available, use the first
-    ** one encountered. If there is both a MATCH constraint and a direct
-    ** rowid/docid lookup, prefer the MATCH strategy. This is done even 
-    ** though the rowid/docid lookup is faster than a MATCH query, selecting
-    ** it would lead to an "unable to use function MATCH in the requested 
-    ** context" error.
-    */
-    if( pCons->op==SQLITE_INDEX_CONSTRAINT_MATCH 
-     && pCons->iColumn>=0 && pCons->iColumn<=p->nColumn
-    ){
-      pInfo->idxNum = FTS3_FULLTEXT_SEARCH + pCons->iColumn;
-      pInfo->estimatedCost = 2.0;
-      iCons = i;
-    }
+  rc = sql_get_statement(v, CONTENT_SELECT_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-    /* Equality constraint on the langid column */
-    if( pCons->op==SQLITE_INDEX_CONSTRAINT_EQ 
-     && pCons->iColumn==p->nColumn + 2
-    ){
-      iLangidCons = i;
-    }
+  rc = sqlite3_bind_int64(s, 1, iDocid);
+  if( rc!=SQLITE_OK ) return rc;
 
-    if( bDocid ){
-      switch( pCons->op ){
-        case SQLITE_INDEX_CONSTRAINT_GE:
-        case SQLITE_INDEX_CONSTRAINT_GT:
-          iDocidGe = i;
-          break;
-
-        case SQLITE_INDEX_CONSTRAINT_LE:
-        case SQLITE_INDEX_CONSTRAINT_LT:
-          iDocidLe = i;
-          break;
-      }
+  rc = sqlite3_step(s);
+  if( rc!=SQLITE_ROW ) return rc;
+
+  values = (const char **) sqlite3_malloc(v->nColumn * sizeof(const char *));
+  for(i=0; i<v->nColumn; ++i){
+    if( sqlite3_column_type(s, i)==SQLITE_NULL ){
+      values[i] = NULL;
+    }else{
+      values[i] = string_dup((char*)sqlite3_column_text(s, i));
     }
   }
 
-  /* If using a docid=? or rowid=? strategy, set the UNIQUE flag. */
-  if( pInfo->idxNum==FTS3_DOCID_SEARCH ) fts3SetUniqueFlag(pInfo);
-
-  iIdx = 1;
-  if( iCons>=0 ){
-    pInfo->aConstraintUsage[iCons].argvIndex = iIdx++;
-    pInfo->aConstraintUsage[iCons].omit = 1;
-  } 
-  if( iLangidCons>=0 ){
-    pInfo->idxNum |= FTS3_HAVE_LANGID;
-    pInfo->aConstraintUsage[iLangidCons].argvIndex = iIdx++;
-  } 
-  if( iDocidGe>=0 ){
-    pInfo->idxNum |= FTS3_HAVE_DOCID_GE;
-    pInfo->aConstraintUsage[iDocidGe].argvIndex = iIdx++;
-  } 
-  if( iDocidLe>=0 ){
-    pInfo->idxNum |= FTS3_HAVE_DOCID_LE;
-    pInfo->aConstraintUsage[iDocidLe].argvIndex = iIdx++;
-  } 
-
-  /* Regardless of the strategy selected, FTS can deliver rows in rowid (or
-  ** docid) order. Both ascending and descending are possible. 
-  */
-  if( pInfo->nOrderBy==1 ){
-    struct sqlite3_index_orderby *pOrder = &pInfo->aOrderBy[0];
-    if( pOrder->iColumn<0 || pOrder->iColumn==p->nColumn+1 ){
-      if( pOrder->desc ){
-        pInfo->idxStr = "DESC";
-      }else{
-        pInfo->idxStr = "ASC";
-      }
-      pInfo->orderByConsumed = 1;
-    }
+  /* We expect only one row.  We must execute another sqlite3_step()
+   * to complete the iteration; otherwise the table will remain locked. */
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_DONE ){
+    *pValues = values;
+    return SQLITE_OK;
   }
 
-  assert( p->pSegments==0 );
-  return SQLITE_OK;
+  freeStringArray(v->nColumn, values);
+  return rc;
 }
 
-/*
-** Implementation of xOpen method.
-*/
-static int fts3OpenMethod(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCsr){
-  sqlite3_vtab_cursor *pCsr;               /* Allocated cursor */
-
-  UNUSED_PARAMETER(pVTab);
+/* delete from %_content where docid = [iDocid ] */
+static int content_delete(fulltext_vtab *v, sqlite_int64 iDocid){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, CONTENT_DELETE_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-  /* Allocate a buffer large enough for an Fts3Cursor structure. If the
-  ** allocation succeeds, zero it and return SQLITE_OK. Otherwise, 
-  ** if the allocation fails, return SQLITE_NOMEM.
-  */
-  *ppCsr = pCsr = (sqlite3_vtab_cursor *)sqlite3_malloc(sizeof(Fts3Cursor));
-  if( !pCsr ){
-    return SQLITE_NOMEM;
-  }
-  memset(pCsr, 0, sizeof(Fts3Cursor));
-  return SQLITE_OK;
-}
+  rc = sqlite3_bind_int64(s, 1, iDocid);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** Finalize the statement handle at pCsr->pStmt.
-**
-** Or, if that statement handle is one created by fts3CursorSeekStmt(),
-** and the Fts3Table.pSeekStmt slot is currently NULL, save the statement
-** pointer there instead of finalizing it.
-*/
-static void fts3CursorFinalizeStmt(Fts3Cursor *pCsr){
-  if( pCsr->bSeekStmt ){
-    Fts3Table *p = (Fts3Table *)pCsr->base.pVtab;
-    if( p->pSeekStmt==0 ){
-      p->pSeekStmt = pCsr->pStmt;
-      sqlite3_reset(pCsr->pStmt);
-      pCsr->pStmt = 0;
-    }
-    pCsr->bSeekStmt = 0;
-  }
-  sqlite3_finalize(pCsr->pStmt);
+  return sql_single_step(s);
 }
 
-/*
-** Free all resources currently held by the cursor passed as the only
-** argument.
+/* Returns SQLITE_ROW if any rows exist in %_content, SQLITE_DONE if
+** no rows exist, and any error in case of failure.
 */
-static void fts3ClearCursor(Fts3Cursor *pCsr){
-  fts3CursorFinalizeStmt(pCsr);
-  sqlite3Fts3FreeDeferredTokens(pCsr);
-  sqlite3_free(pCsr->aDoclist);
-  sqlite3Fts3MIBufferFree(pCsr->pMIBuffer);
-  sqlite3Fts3ExprFree(pCsr->pExpr);
-  memset(&(&pCsr->base)[1], 0, sizeof(Fts3Cursor)-sizeof(sqlite3_vtab_cursor));
+static int content_exists(fulltext_vtab *v){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, CONTENT_EXISTS_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_step(s);
+  if( rc!=SQLITE_ROW ) return rc;
+
+  /* We expect only one row.  We must execute another sqlite3_step()
+   * to complete the iteration; otherwise the table will remain locked. */
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_DONE ) return SQLITE_ROW;
+  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
+  return rc;
 }
 
-/*
-** Close the cursor.  For additional information see the documentation
-** on the xClose method of the virtual table interface.
+/* insert into %_segments values ([pData])
+**   returns assigned blockid in *piBlockid
 */
-static int fts3CloseMethod(sqlite3_vtab_cursor *pCursor){
-  Fts3Cursor *pCsr = (Fts3Cursor *)pCursor;
-  assert( ((Fts3Table *)pCsr->base.pVtab)->pSegments==0 );
-  fts3ClearCursor(pCsr);
-  assert( ((Fts3Table *)pCsr->base.pVtab)->pSegments==0 );
-  sqlite3_free(pCsr);
+static int block_insert(fulltext_vtab *v, const char *pData, int nData,
+                        sqlite_int64 *piBlockid){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, BLOCK_INSERT_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_bind_blob(s, 1, pData, nData, SQLITE_STATIC);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
+  if( rc!=SQLITE_DONE ) return rc;
+
+  /* blockid column is an alias for rowid. */
+  *piBlockid = sqlite3_last_insert_rowid(v->db);
   return SQLITE_OK;
 }
 
-/*
-** If pCsr->pStmt has not been prepared (i.e. if pCsr->pStmt==0), then
-** compose and prepare an SQL statement of the form:
+/* delete from %_segments
+**   where blockid between [iStartBlockid] and [iEndBlockid]
 **
-**    "SELECT <columns> FROM %_content WHERE rowid = ?"
-**
-** (or the equivalent for a content=xxx table) and set pCsr->pStmt to
-** it. If an error occurs, return an SQLite error code.
+** Deletes the range of blocks, inclusive, used to delete the blocks
+** which form a segment.
 */
-static int fts3CursorSeekStmt(Fts3Cursor *pCsr){
-  int rc = SQLITE_OK;
-  if( pCsr->pStmt==0 ){
-    Fts3Table *p = (Fts3Table *)pCsr->base.pVtab;
-    char *zSql;
-    if( p->pSeekStmt ){
-      pCsr->pStmt = p->pSeekStmt;
-      p->pSeekStmt = 0;
-    }else{
-      zSql = sqlite3_mprintf("SELECT %s WHERE rowid = ?", p->zReadExprlist);
-      if( !zSql ) return SQLITE_NOMEM;
-      rc = sqlite3_prepare_v3(p->db, zSql,-1,SQLITE_PREPARE_PERSISTENT,&pCsr->pStmt,0);
-      sqlite3_free(zSql);
-    }
-    if( rc==SQLITE_OK ) pCsr->bSeekStmt = 1;
-  }
-  return rc;
+static int block_delete(fulltext_vtab *v,
+                        sqlite_int64 iStartBlockid, sqlite_int64 iEndBlockid){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, BLOCK_DELETE_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_bind_int64(s, 1, iStartBlockid);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_bind_int64(s, 2, iEndBlockid);
+  if( rc!=SQLITE_OK ) return rc;
+
+  return sql_single_step(s);
 }
 
-/*
-** Position the pCsr->pStmt statement so that it is on the row
-** of the %_content table that contains the last match.  Return
-** SQLITE_OK on success.  
+/* Returns SQLITE_ROW with *pidx set to the maximum segment idx found
+** at iLevel.  Returns SQLITE_DONE if there are no segments at
+** iLevel.  Otherwise returns an error.
 */
-static int fts3CursorSeek(sqlite3_context *pContext, Fts3Cursor *pCsr){
-  int rc = SQLITE_OK;
-  if( pCsr->isRequireSeek ){
-    rc = fts3CursorSeekStmt(pCsr);
-    if( rc==SQLITE_OK ){
-      sqlite3_bind_int64(pCsr->pStmt, 1, pCsr->iPrevId);
-      pCsr->isRequireSeek = 0;
-      if( SQLITE_ROW==sqlite3_step(pCsr->pStmt) ){
-        return SQLITE_OK;
-      }else{
-        rc = sqlite3_reset(pCsr->pStmt);
-        if( rc==SQLITE_OK && ((Fts3Table *)pCsr->base.pVtab)->zContentTbl==0 ){
-          /* If no row was found and no error has occurred, then the %_content
-          ** table is missing a row that is present in the full-text index.
-          ** The data structures are corrupt.  */
-          rc = FTS_CORRUPT_VTAB;
-          pCsr->isEof = 1;
-        }
-      }
-    }
-  }
+static int segdir_max_index(fulltext_vtab *v, int iLevel, int *pidx){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, SEGDIR_MAX_INDEX_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-  if( rc!=SQLITE_OK && pContext ){
-    sqlite3_result_error_code(pContext, rc);
-  }
-  return rc;
-}
+  rc = sqlite3_bind_int(s, 1, iLevel);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** This function is used to process a single interior node when searching
-** a b-tree for a term or term prefix. The node data is passed to this 
-** function via the zNode/nNode parameters. The term to search for is
-** passed in zTerm/nTerm.
-**
-** If piFirst is not NULL, then this function sets *piFirst to the blockid
-** of the child node that heads the sub-tree that may contain the term.
-**
-** If piLast is not NULL, then *piLast is set to the right-most child node
-** that heads a sub-tree that may contain a term for which zTerm/nTerm is
-** a prefix.
-**
-** If an OOM error occurs, SQLITE_NOMEM is returned. Otherwise, SQLITE_OK.
-*/
-static int fts3ScanInteriorNode(
-  const char *zTerm,              /* Term to select leaves for */
-  int nTerm,                      /* Size of term zTerm in bytes */
-  const char *zNode,              /* Buffer containing segment interior node */
-  int nNode,                      /* Size of buffer at zNode */
-  sqlite3_int64 *piFirst,         /* OUT: Selected child node */
-  sqlite3_int64 *piLast           /* OUT: Selected child node */
-){
-  int rc = SQLITE_OK;             /* Return code */
-  const char *zCsr = zNode;       /* Cursor to iterate through node */
-  const char *zEnd = &zCsr[nNode];/* End of interior node buffer */
-  char *zBuffer = 0;              /* Buffer to load terms into */
-  int nAlloc = 0;                 /* Size of allocated buffer */
-  int isFirstTerm = 1;            /* True when processing first term on page */
-  sqlite3_int64 iChild;           /* Block id of child node to descend to */
-
-  /* Skip over the 'height' varint that occurs at the start of every 
-  ** interior node. Then load the blockid of the left-child of the b-tree
-  ** node into variable iChild.  
-  **
-  ** Even if the data structure on disk is corrupted, this (reading two
-  ** varints from the buffer) does not risk an overread. If zNode is a
-  ** root node, then the buffer comes from a SELECT statement. SQLite does
-  ** not make this guarantee explicitly, but in practice there are always
-  ** either more than 20 bytes of allocated space following the nNode bytes of
-  ** contents, or two zero bytes. Or, if the node is read from the %_segments
-  ** table, then there are always 20 bytes of zeroed padding following the
-  ** nNode bytes of content (see sqlite3Fts3ReadBlock() for details).
-  */
-  zCsr += sqlite3Fts3GetVarint(zCsr, &iChild);
-  zCsr += sqlite3Fts3GetVarint(zCsr, &iChild);
-  if( zCsr>zEnd ){
-    return FTS_CORRUPT_VTAB;
+  rc = sqlite3_step(s);
+  /* Should always get at least one row due to how max() works. */
+  if( rc==SQLITE_DONE ) return SQLITE_DONE;
+  if( rc!=SQLITE_ROW ) return rc;
+
+  /* NULL means that there were no inputs to max(). */
+  if( SQLITE_NULL==sqlite3_column_type(s, 0) ){
+    rc = sqlite3_step(s);
+    if( rc==SQLITE_ROW ) return SQLITE_ERROR;
+    return rc;
   }
-  
-  while( zCsr<zEnd && (piFirst || piLast) ){
-    int cmp;                      /* memcmp() result */
-    int nSuffix;                  /* Size of term suffix */
-    int nPrefix = 0;              /* Size of term prefix */
-    int nBuffer;                  /* Total term size */
-  
-    /* Load the next term on the node into zBuffer. Use realloc() to expand
-    ** the size of zBuffer if required.  */
-    if( !isFirstTerm ){
-      zCsr += fts3GetVarint32(zCsr, &nPrefix);
-    }
-    isFirstTerm = 0;
-    zCsr += fts3GetVarint32(zCsr, &nSuffix);
-    
-    assert( nPrefix>=0 && nSuffix>=0 );
-    if( &zCsr[nSuffix]>zEnd ){
-      rc = FTS_CORRUPT_VTAB;
-      goto finish_scan;
-    }
-    if( nPrefix+nSuffix>nAlloc ){
-      char *zNew;
-      nAlloc = (nPrefix+nSuffix) * 2;
-      zNew = (char *)sqlite3_realloc(zBuffer, nAlloc);
-      if( !zNew ){
-        rc = SQLITE_NOMEM;
-        goto finish_scan;
-      }
-      zBuffer = zNew;
-    }
-    assert( zBuffer );
-    memcpy(&zBuffer[nPrefix], zCsr, nSuffix);
-    nBuffer = nPrefix + nSuffix;
-    zCsr += nSuffix;
-
-    /* Compare the term we are searching for with the term just loaded from
-    ** the interior node. If the specified term is greater than or equal
-    ** to the term from the interior node, then all terms on the sub-tree 
-    ** headed by node iChild are smaller than zTerm. No need to search 
-    ** iChild.
-    **
-    ** If the interior node term is larger than the specified term, then
-    ** the tree headed by iChild may contain the specified term.
-    */
-    cmp = memcmp(zTerm, zBuffer, (nBuffer>nTerm ? nTerm : nBuffer));
-    if( piFirst && (cmp<0 || (cmp==0 && nBuffer>nTerm)) ){
-      *piFirst = iChild;
-      piFirst = 0;
-    }
 
-    if( piLast && cmp<0 ){
-      *piLast = iChild;
-      piLast = 0;
-    }
+  *pidx = sqlite3_column_int(s, 0);
+
+  /* We expect only one row.  We must execute another sqlite3_step()
+   * to complete the iteration; otherwise the table will remain locked. */
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
+  if( rc!=SQLITE_DONE ) return rc;
+  return SQLITE_ROW;
+}
+
+/* insert into %_segdir values (
+**   [iLevel], [idx],
+**   [iStartBlockid], [iLeavesEndBlockid], [iEndBlockid],
+**   [pRootData]
+** )
+*/
+static int segdir_set(fulltext_vtab *v, int iLevel, int idx,
+                      sqlite_int64 iStartBlockid,
+                      sqlite_int64 iLeavesEndBlockid,
+                      sqlite_int64 iEndBlockid,
+                      const char *pRootData, int nRootData){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, SEGDIR_SET_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-    iChild++;
-  };
+  rc = sqlite3_bind_int(s, 1, iLevel);
+  if( rc!=SQLITE_OK ) return rc;
 
-  if( piFirst ) *piFirst = iChild;
-  if( piLast ) *piLast = iChild;
+  rc = sqlite3_bind_int(s, 2, idx);
+  if( rc!=SQLITE_OK ) return rc;
 
- finish_scan:
-  sqlite3_free(zBuffer);
-  return rc;
-}
+  rc = sqlite3_bind_int64(s, 3, iStartBlockid);
+  if( rc!=SQLITE_OK ) return rc;
 
+  rc = sqlite3_bind_int64(s, 4, iLeavesEndBlockid);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** The buffer pointed to by argument zNode (size nNode bytes) contains an
-** interior node of a b-tree segment. The zTerm buffer (size nTerm bytes)
-** contains a term. This function searches the sub-tree headed by the zNode
-** node for the range of leaf nodes that may contain the specified term
-** or terms for which the specified term is a prefix.
-**
-** If piLeaf is not NULL, then *piLeaf is set to the blockid of the 
-** left-most leaf node in the tree that may contain the specified term.
-** If piLeaf2 is not NULL, then *piLeaf2 is set to the blockid of the
-** right-most leaf node that may contain a term for which the specified
-** term is a prefix.
-**
-** It is possible that the range of returned leaf nodes does not contain 
-** the specified term or any terms for which it is a prefix. However, if the 
-** segment does contain any such terms, they are stored within the identified
-** range. Because this function only inspects interior segment nodes (and
-** never loads leaf nodes into memory), it is not possible to be sure.
-**
-** If an error occurs, an error code other than SQLITE_OK is returned.
-*/ 
-static int fts3SelectLeaf(
-  Fts3Table *p,                   /* Virtual table handle */
-  const char *zTerm,              /* Term to select leaves for */
-  int nTerm,                      /* Size of term zTerm in bytes */
-  const char *zNode,              /* Buffer containing segment interior node */
-  int nNode,                      /* Size of buffer at zNode */
-  sqlite3_int64 *piLeaf,          /* Selected leaf node */
-  sqlite3_int64 *piLeaf2          /* Selected leaf node */
-){
-  int rc = SQLITE_OK;             /* Return code */
-  int iHeight;                    /* Height of this node in tree */
+  rc = sqlite3_bind_int64(s, 5, iEndBlockid);
+  if( rc!=SQLITE_OK ) return rc;
 
-  assert( piLeaf || piLeaf2 );
+  rc = sqlite3_bind_blob(s, 6, pRootData, nRootData, SQLITE_STATIC);
+  if( rc!=SQLITE_OK ) return rc;
 
-  fts3GetVarint32(zNode, &iHeight);
-  rc = fts3ScanInteriorNode(zTerm, nTerm, zNode, nNode, piLeaf, piLeaf2);
-  assert( !piLeaf2 || !piLeaf || rc!=SQLITE_OK || (*piLeaf<=*piLeaf2) );
+  return sql_single_step(s);
+}
 
-  if( rc==SQLITE_OK && iHeight>1 ){
-    char *zBlob = 0;              /* Blob read from %_segments table */
-    int nBlob = 0;                /* Size of zBlob in bytes */
+/* Queries %_segdir for the block span of the segments in level
+** iLevel.  Returns SQLITE_DONE if there are no blocks for iLevel,
+** SQLITE_ROW if there are blocks, else an error.
+*/
+static int segdir_span(fulltext_vtab *v, int iLevel,
+                       sqlite_int64 *piStartBlockid,
+                       sqlite_int64 *piEndBlockid){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, SEGDIR_SPAN_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-    if( piLeaf && piLeaf2 && (*piLeaf!=*piLeaf2) ){
-      rc = sqlite3Fts3ReadBlock(p, *piLeaf, &zBlob, &nBlob, 0);
-      if( rc==SQLITE_OK ){
-        rc = fts3SelectLeaf(p, zTerm, nTerm, zBlob, nBlob, piLeaf, 0);
-      }
-      sqlite3_free(zBlob);
-      piLeaf = 0;
-      zBlob = 0;
-    }
+  rc = sqlite3_bind_int(s, 1, iLevel);
+  if( rc!=SQLITE_OK ) return rc;
 
-    if( rc==SQLITE_OK ){
-      rc = sqlite3Fts3ReadBlock(p, piLeaf?*piLeaf:*piLeaf2, &zBlob, &nBlob, 0);
-    }
-    if( rc==SQLITE_OK ){
-      rc = fts3SelectLeaf(p, zTerm, nTerm, zBlob, nBlob, piLeaf, piLeaf2);
-    }
-    sqlite3_free(zBlob);
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_DONE ) return SQLITE_DONE;  /* Should never happen */
+  if( rc!=SQLITE_ROW ) return rc;
+
+  /* This happens if all segments at this level are entirely inline. */
+  if( SQLITE_NULL==sqlite3_column_type(s, 0) ){
+    /* We expect only one row.  We must execute another sqlite3_step()
+     * to complete the iteration; otherwise the table will remain locked. */
+    int rc2 = sqlite3_step(s);
+    if( rc2==SQLITE_ROW ) return SQLITE_ERROR;
+    return rc2;
+  }
+
+  *piStartBlockid = sqlite3_column_int64(s, 0);
+  *piEndBlockid = sqlite3_column_int64(s, 1);
+
+  /* We expect only one row.  We must execute another sqlite3_step()
+   * to complete the iteration; otherwise the table will remain locked. */
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
+  if( rc!=SQLITE_DONE ) return rc;
+  return SQLITE_ROW;
+}
+
+/* Delete the segment blocks and segment directory records for all
+** segments at iLevel.
+*/
+static int segdir_delete(fulltext_vtab *v, int iLevel){
+  sqlite3_stmt *s;
+  sqlite_int64 iStartBlockid, iEndBlockid;
+  int rc = segdir_span(v, iLevel, &iStartBlockid, &iEndBlockid);
+  if( rc!=SQLITE_ROW && rc!=SQLITE_DONE ) return rc;
+
+  if( rc==SQLITE_ROW ){
+    rc = block_delete(v, iStartBlockid, iEndBlockid);
+    if( rc!=SQLITE_OK ) return rc;
   }
 
-  return rc;
+  /* Delete the segment directory itself. */
+  rc = sql_get_statement(v, SEGDIR_DELETE_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_bind_int64(s, 1, iLevel);
+  if( rc!=SQLITE_OK ) return rc;
+
+  return sql_single_step(s);
 }
 
-/*
-** This function is used to create delta-encoded serialized lists of FTS3 
-** varints. Each call to this function appends a single varint to a list.
+/* Delete entire fts index, SQLITE_OK on success, relevant error on
+** failure.
 */
-static void fts3PutDeltaVarint(
-  char **pp,                      /* IN/OUT: Output pointer */
-  sqlite3_int64 *piPrev,          /* IN/OUT: Previous value written to list */
-  sqlite3_int64 iVal              /* Write this value to the list */
-){
-  assert( iVal-*piPrev > 0 || (*piPrev==0 && iVal==0) );
-  *pp += sqlite3Fts3PutVarint(*pp, iVal-*piPrev);
-  *piPrev = iVal;
-}
+static int segdir_delete_all(fulltext_vtab *v){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, SEGDIR_DELETE_ALL_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** When this function is called, *ppPoslist is assumed to point to the 
-** start of a position-list. After it returns, *ppPoslist points to the
-** first byte after the position-list.
-**
-** A position list is list of positions (delta encoded) and columns for 
-** a single document record of a doclist.  So, in other words, this
-** routine advances *ppPoslist so that it points to the next docid in
-** the doclist, or to the first byte past the end of the doclist.
-**
-** If pp is not NULL, then the contents of the position list are copied
-** to *pp. *pp is set to point to the first byte past the last byte copied
-** before this function returns.
-*/
-static void fts3PoslistCopy(char **pp, char **ppPoslist){
-  char *pEnd = *ppPoslist;
-  char c = 0;
-
-  /* The end of a position list is marked by a zero encoded as an FTS3 
-  ** varint. A single POS_END (0) byte. Except, if the 0 byte is preceded by
-  ** a byte with the 0x80 bit set, then it is not a varint 0, but the tail
-  ** of some other, multi-byte, value.
-  **
-  ** The following while-loop moves pEnd to point to the first byte that is not 
-  ** immediately preceded by a byte with the 0x80 bit set. Then increments
-  ** pEnd once more so that it points to the byte immediately following the
-  ** last byte in the position-list.
-  */
-  while( *pEnd | c ){
-    c = *pEnd++ & 0x80;
-    testcase( c!=0 && (*pEnd)==0 );
-  }
-  pEnd++;  /* Advance past the POS_END terminator byte */
-
-  if( pp ){
-    int n = (int)(pEnd - *ppPoslist);
-    char *p = *pp;
-    memcpy(p, *ppPoslist, n);
-    p += n;
-    *pp = p;
-  }
-  *ppPoslist = pEnd;
-}
+  rc = sql_single_step(s);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** When this function is called, *ppPoslist is assumed to point to the 
-** start of a column-list. After it returns, *ppPoslist points to the
-** to the terminator (POS_COLUMN or POS_END) byte of the column-list.
-**
-** A column-list is list of delta-encoded positions for a single column
-** within a single document within a doclist.
-**
-** The column-list is terminated either by a POS_COLUMN varint (1) or
-** a POS_END varint (0).  This routine leaves *ppPoslist pointing to
-** the POS_COLUMN or POS_END that terminates the column-list.
-**
-** If pp is not NULL, then the contents of the column-list are copied
-** to *pp. *pp is set to point to the first byte past the last byte copied
-** before this function returns.  The POS_COLUMN or POS_END terminator
-** is not copied into *pp.
-*/
-static void fts3ColumnlistCopy(char **pp, char **ppPoslist){
-  char *pEnd = *ppPoslist;
-  char c = 0;
-
-  /* A column-list is terminated by either a 0x01 or 0x00 byte that is
-  ** not part of a multi-byte varint.
-  */
-  while( 0xFE & (*pEnd | c) ){
-    c = *pEnd++ & 0x80;
-    testcase( c!=0 && ((*pEnd)&0xfe)==0 );
-  }
-  if( pp ){
-    int n = (int)(pEnd - *ppPoslist);
-    char *p = *pp;
-    memcpy(p, *ppPoslist, n);
-    p += n;
-    *pp = p;
-  }
-  *ppPoslist = pEnd;
+  rc = sql_get_statement(v, BLOCK_DELETE_ALL_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  return sql_single_step(s);
 }
 
-/*
-** Value used to signify the end of an position-list. This is safe because
-** it is not possible to have a document with 2^31 terms.
+/* Returns SQLITE_OK with *pnSegments set to the number of entries in
+** %_segdir and *piMaxLevel set to the highest level which has a
+** segment.  Otherwise returns the SQLite error which caused failure.
 */
-#define POSITION_LIST_END 0x7fffffff
+static int segdir_count(fulltext_vtab *v, int *pnSegments, int *piMaxLevel){
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, SEGDIR_COUNT_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** This function is used to help parse position-lists. When this function is
-** called, *pp may point to the start of the next varint in the position-list
-** being parsed, or it may point to 1 byte past the end of the position-list
-** (in which case **pp will be a terminator bytes POS_END (0) or
-** (1)).
-**
-** If *pp points past the end of the current position-list, set *pi to 
-** POSITION_LIST_END and return. Otherwise, read the next varint from *pp,
-** increment the current value of *pi by the value read, and set *pp to
-** point to the next value before returning.
-**
-** Before calling this routine *pi must be initialized to the value of
-** the previous position, or zero if we are reading the first position
-** in the position-list.  Because positions are delta-encoded, the value
-** of the previous position is needed in order to compute the value of
-** the next position.
-*/
-static void fts3ReadNextPos(
-  char **pp,                    /* IN/OUT: Pointer into position-list buffer */
-  sqlite3_int64 *pi             /* IN/OUT: Value read from position-list */
-){
-  if( (**pp)&0xFE ){
-    fts3GetDeltaVarint(pp, pi);
-    *pi -= 2;
-  }else{
-    *pi = POSITION_LIST_END;
+  rc = sqlite3_step(s);
+  /* TODO(shess): This case should not be possible?  Should stronger
+  ** measures be taken if it happens?
+  */
+  if( rc==SQLITE_DONE ){
+    *pnSegments = 0;
+    *piMaxLevel = 0;
+    return SQLITE_OK;
   }
+  if( rc!=SQLITE_ROW ) return rc;
+
+  *pnSegments = sqlite3_column_int(s, 0);
+  *piMaxLevel = sqlite3_column_int(s, 1);
+
+  /* We expect only one row.  We must execute another sqlite3_step()
+   * to complete the iteration; otherwise the table will remain locked. */
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_DONE ) return SQLITE_OK;
+  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
+  return rc;
 }
 
+/* TODO(shess) clearPendingTerms() is far down the file because
+** writeZeroSegment() is far down the file because LeafWriter is far
+** down the file.  Consider refactoring the code to move the non-vtab
+** code above the vtab code so that we don't need this forward
+** reference.
+*/
+static int clearPendingTerms(fulltext_vtab *v);
+
 /*
-** If parameter iCol is not 0, write an POS_COLUMN (1) byte followed by
-** the value of iCol encoded as a varint to *pp.   This will start a new
-** column list.
-**
-** Set *pp to point to the byte just after the last byte written before 
-** returning (do not modify it if iCol==0). Return the total number of bytes
-** written (0 if iCol==0).
-*/
-static int fts3PutColNumber(char **pp, int iCol){
-  int n = 0;                      /* Number of bytes written */
-  if( iCol ){
-    char *p = *pp;                /* Output pointer */
-    n = 1 + sqlite3Fts3PutVarint(&p[1], iCol);
-    *p = 0x01;
-    *pp = &p[n];
+** Free the memory used to contain a fulltext_vtab structure.
+*/
+static void fulltext_vtab_destroy(fulltext_vtab *v){
+  int iStmt, i;
+
+  FTSTRACE(("FTS3 Destroy %p\n", v));
+  for( iStmt=0; iStmt<MAX_STMT; iStmt++ ){
+    if( v->pFulltextStatements[iStmt]!=NULL ){
+      sqlite3_finalize(v->pFulltextStatements[iStmt]);
+      v->pFulltextStatements[iStmt] = NULL;
+    }
   }
-  return n;
-}
 
-/*
-** Compute the union of two position lists.  The output written
-** into *pp contains all positions of both *pp1 and *pp2 in sorted
-** order and with any duplicates removed.  All pointers are
-** updated appropriately.   The caller is responsible for insuring
-** that there is enough space in *pp to hold the complete output.
-*/
-static void fts3PoslistMerge(
-  char **pp,                      /* Output buffer */
-  char **pp1,                     /* Left input list */
-  char **pp2                      /* Right input list */
-){
-  char *p = *pp;
-  char *p1 = *pp1;
-  char *p2 = *pp2;
-
-  while( *p1 || *p2 ){
-    int iCol1;         /* The current column index in pp1 */
-    int iCol2;         /* The current column index in pp2 */
-
-    if( *p1==POS_COLUMN ) fts3GetVarint32(&p1[1], &iCol1);
-    else if( *p1==POS_END ) iCol1 = POSITION_LIST_END;
-    else iCol1 = 0;
-
-    if( *p2==POS_COLUMN ) fts3GetVarint32(&p2[1], &iCol2);
-    else if( *p2==POS_END ) iCol2 = POSITION_LIST_END;
-    else iCol2 = 0;
-
-    if( iCol1==iCol2 ){
-      sqlite3_int64 i1 = 0;       /* Last position from pp1 */
-      sqlite3_int64 i2 = 0;       /* Last position from pp2 */
-      sqlite3_int64 iPrev = 0;
-      int n = fts3PutColNumber(&p, iCol1);
-      p1 += n;
-      p2 += n;
-
-      /* At this point, both p1 and p2 point to the start of column-lists
-      ** for the same column (the column with index iCol1 and iCol2).
-      ** A column-list is a list of non-negative delta-encoded varints, each 
-      ** incremented by 2 before being stored. Each list is terminated by a
-      ** POS_END (0) or POS_COLUMN (1). The following block merges the two lists
-      ** and writes the results to buffer p. p is left pointing to the byte
-      ** after the list written. No terminator (POS_END or POS_COLUMN) is
-      ** written to the output.
-      */
-      fts3GetDeltaVarint(&p1, &i1);
-      fts3GetDeltaVarint(&p2, &i2);
-      do {
-        fts3PutDeltaVarint(&p, &iPrev, (i1<i2) ? i1 : i2); 
-        iPrev -= 2;
-        if( i1==i2 ){
-          fts3ReadNextPos(&p1, &i1);
-          fts3ReadNextPos(&p2, &i2);
-        }else if( i1<i2 ){
-          fts3ReadNextPos(&p1, &i1);
-        }else{
-          fts3ReadNextPos(&p2, &i2);
-        }
-      }while( i1!=POSITION_LIST_END || i2!=POSITION_LIST_END );
-    }else if( iCol1<iCol2 ){
-      p1 += fts3PutColNumber(&p, iCol1);
-      fts3ColumnlistCopy(&p, &p1);
-    }else{
-      p2 += fts3PutColNumber(&p, iCol2);
-      fts3ColumnlistCopy(&p, &p2);
+  for( i=0; i<MERGE_COUNT; i++ ){
+    if( v->pLeafSelectStmts[i]!=NULL ){
+      sqlite3_finalize(v->pLeafSelectStmts[i]);
+      v->pLeafSelectStmts[i] = NULL;
     }
   }
 
-  *p++ = POS_END;
-  *pp = p;
-  *pp1 = p1 + 1;
-  *pp2 = p2 + 1;
+  if( v->pTokenizer!=NULL ){
+    v->pTokenizer->pModule->xDestroy(v->pTokenizer);
+    v->pTokenizer = NULL;
+  }
+
+  clearPendingTerms(v);
+
+  sqlite3_free(v->azColumn);
+  for(i = 0; i < v->nColumn; ++i) {
+    sqlite3_free(v->azContentColumn[i]);
+  }
+  sqlite3_free(v->azContentColumn);
+  sqlite3_free(v);
 }
 
 /*
-** This function is used to merge two position lists into one. When it is
-** called, *pp1 and *pp2 must both point to position lists. A position-list is
-** the part of a doclist that follows each document id. For example, if a row
-** contains:
-**
-**     'a b c'|'x y z'|'a b b a'
-**
-** Then the position list for this row for token 'b' would consist of:
-**
-**     0x02 0x01 0x02 0x03 0x03 0x00
-**
-** When this function returns, both *pp1 and *pp2 are left pointing to the
-** byte following the 0x00 terminator of their respective position lists.
-**
-** If isSaveLeft is 0, an entry is added to the output position list for 
-** each position in *pp2 for which there exists one or more positions in
-** *pp1 so that (pos(*pp2)>pos(*pp1) && pos(*pp2)-pos(*pp1)<=nToken). i.e.
-** when the *pp1 token appears before the *pp2 token, but not more than nToken
-** slots before it.
-**
-** e.g. nToken==1 searches for adjacent positions.
-*/
-static int fts3PoslistPhraseMerge(
-  char **pp,                      /* IN/OUT: Preallocated output buffer */
-  int nToken,                     /* Maximum difference in token positions */
-  int isSaveLeft,                 /* Save the left position */
-  int isExact,                    /* If *pp1 is exactly nTokens before *pp2 */
-  char **pp1,                     /* IN/OUT: Left input list */
-  char **pp2                      /* IN/OUT: Right input list */
-){
-  char *p = *pp;
-  char *p1 = *pp1;
-  char *p2 = *pp2;
-  int iCol1 = 0;
-  int iCol2 = 0;
-
-  /* Never set both isSaveLeft and isExact for the same invocation. */
-  assert( isSaveLeft==0 || isExact==0 );
-
-  assert( p!=0 && *p1!=0 && *p2!=0 );
-  if( *p1==POS_COLUMN ){ 
-    p1++;
-    p1 += fts3GetVarint32(p1, &iCol1);
-  }
-  if( *p2==POS_COLUMN ){ 
-    p2++;
-    p2 += fts3GetVarint32(p2, &iCol2);
-  }
-
-  while( 1 ){
-    if( iCol1==iCol2 ){
-      char *pSave = p;
-      sqlite3_int64 iPrev = 0;
-      sqlite3_int64 iPos1 = 0;
-      sqlite3_int64 iPos2 = 0;
-
-      if( iCol1 ){
-        *p++ = POS_COLUMN;
-        p += sqlite3Fts3PutVarint(p, iCol1);
-      }
+** Token types for parsing the arguments to xConnect or xCreate.
+*/
+#define TOKEN_EOF         0    /* End of file */
+#define TOKEN_SPACE       1    /* Any kind of whitespace */
+#define TOKEN_ID          2    /* An identifier */
+#define TOKEN_STRING      3    /* A string literal */
+#define TOKEN_PUNCT       4    /* A single punctuation character */
 
-      assert( *p1!=POS_END && *p1!=POS_COLUMN );
-      assert( *p2!=POS_END && *p2!=POS_COLUMN );
-      fts3GetDeltaVarint(&p1, &iPos1); iPos1 -= 2;
-      fts3GetDeltaVarint(&p2, &iPos2); iPos2 -= 2;
+/*
+** If X is a character that can be used in an identifier then
+** ftsIdChar(X) will be true.  Otherwise it is false.
+**
+** For ASCII, any character with the high-order bit set is
+** allowed in an identifier.  For 7-bit characters, 
+** isFtsIdChar[X] must be 1.
+**
+** Ticket #1066.  the SQL standard does not allow '$' in the
+** middle of identfiers.  But many SQL implementations do. 
+** SQLite will allow '$' in identifiers for compatibility.
+** But the feature is undocumented.
+*/
+static const char isFtsIdChar[] = {
+/* x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC xD xE xF */
+    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 2x */
+    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,  /* 3x */
+    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 4x */
+    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,  /* 5x */
+    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 6x */
+    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,  /* 7x */
+};
+#define ftsIdChar(C)  (((c=C)&0x80)!=0 || (c>0x1f && isFtsIdChar[c-0x20]))
 
-      while( 1 ){
-        if( iPos2==iPos1+nToken 
-         || (isExact==0 && iPos2>iPos1 && iPos2<=iPos1+nToken) 
-        ){
-          sqlite3_int64 iSave;
-          iSave = isSaveLeft ? iPos1 : iPos2;
-          fts3PutDeltaVarint(&p, &iPrev, iSave+2); iPrev -= 2;
-          pSave = 0;
-          assert( p );
-        }
-        if( (!isSaveLeft && iPos2<=(iPos1+nToken)) || iPos2<=iPos1 ){
-          if( (*p2&0xFE)==0 ) break;
-          fts3GetDeltaVarint(&p2, &iPos2); iPos2 -= 2;
-        }else{
-          if( (*p1&0xFE)==0 ) break;
-          fts3GetDeltaVarint(&p1, &iPos1); iPos1 -= 2;
-        }
-      }
 
-      if( pSave ){
-        assert( pp && p );
-        p = pSave;
+/*
+** Return the length of the token that begins at z[0]. 
+** Store the token type in *tokenType before returning.
+*/
+static int ftsGetToken(const char *z, int *tokenType){
+  int i, c;
+  switch( *z ){
+    case 0: {
+      *tokenType = TOKEN_EOF;
+      return 0;
+    }
+    case ' ': case '\t': case '\n': case '\f': case '\r': {
+      for(i=1; safe_isspace(z[i]); i++){}
+      *tokenType = TOKEN_SPACE;
+      return i;
+    }
+    case '`':
+    case '\'':
+    case '"': {
+      int delim = z[0];
+      for(i=1; (c=z[i])!=0; i++){
+        if( c==delim ){
+          if( z[i+1]==delim ){
+            i++;
+          }else{
+            break;
+          }
+        }
       }
-
-      fts3ColumnlistCopy(0, &p1);
-      fts3ColumnlistCopy(0, &p2);
-      assert( (*p1&0xFE)==0 && (*p2&0xFE)==0 );
-      if( 0==*p1 || 0==*p2 ) break;
-
-      p1++;
-      p1 += fts3GetVarint32(p1, &iCol1);
-      p2++;
-      p2 += fts3GetVarint32(p2, &iCol2);
+      *tokenType = TOKEN_STRING;
+      return i + (c!=0);
     }
-
-    /* Advance pointer p1 or p2 (whichever corresponds to the smaller of
-    ** iCol1 and iCol2) so that it points to either the 0x00 that marks the
-    ** end of the position list, or the 0x01 that precedes the next 
-    ** column-number in the position list. 
-    */
-    else if( iCol1<iCol2 ){
-      fts3ColumnlistCopy(0, &p1);
-      if( 0==*p1 ) break;
-      p1++;
-      p1 += fts3GetVarint32(p1, &iCol1);
-    }else{
-      fts3ColumnlistCopy(0, &p2);
-      if( 0==*p2 ) break;
-      p2++;
-      p2 += fts3GetVarint32(p2, &iCol2);
+    case '[': {
+      for(i=1, c=z[0]; c!=']' && (c=z[i])!=0; i++){}
+      *tokenType = TOKEN_ID;
+      return i;
+    }
+    default: {
+      if( !ftsIdChar(*z) ){
+        break;
+      }
+      for(i=1; ftsIdChar(z[i]); i++){}
+      *tokenType = TOKEN_ID;
+      return i;
     }
   }
-
-  fts3PoslistCopy(0, &p2);
-  fts3PoslistCopy(0, &p1);
-  *pp1 = p1;
-  *pp2 = p2;
-  if( *pp==p ){
-    return 0;
-  }
-  *p++ = 0x00;
-  *pp = p;
+  *tokenType = TOKEN_PUNCT;
   return 1;
 }
 
 /*
-** Merge two position-lists as required by the NEAR operator. The argument
-** position lists correspond to the left and right phrases of an expression 
-** like:
-**
-**     "phrase 1" NEAR "phrase number 2"
-**
-** Position list *pp1 corresponds to the left-hand side of the NEAR 
-** expression and *pp2 to the right. As usual, the indexes in the position 
-** lists are the offsets of the last token in each phrase (tokens "1" and "2" 
-** in the example above).
-**
-** The output position list - written to *pp - is a copy of *pp2 with those
-** entries that are not sufficiently NEAR entries in *pp1 removed.
-*/
-static int fts3PoslistNearMerge(
-  char **pp,                      /* Output buffer */
-  char *aTmp,                     /* Temporary buffer space */
-  int nRight,                     /* Maximum difference in token positions */
-  int nLeft,                      /* Maximum difference in token positions */
-  char **pp1,                     /* IN/OUT: Left input list */
-  char **pp2                      /* IN/OUT: Right input list */
-){
-  char *p1 = *pp1;
-  char *p2 = *pp2;
+** A token extracted from a string is an instance of the following
+** structure.
+*/
+typedef struct FtsToken {
+  const char *z;       /* Pointer to token text.  Not '\000' terminated */
+  short int n;         /* Length of the token text in bytes. */
+} FtsToken;
 
-  char *pTmp1 = aTmp;
-  char *pTmp2;
-  char *aTmp2;
-  int res = 1;
-
-  fts3PoslistPhraseMerge(&pTmp1, nRight, 0, 0, pp1, pp2);
-  aTmp2 = pTmp2 = pTmp1;
-  *pp1 = p1;
-  *pp2 = p2;
-  fts3PoslistPhraseMerge(&pTmp2, nLeft, 1, 0, pp2, pp1);
-  if( pTmp1!=aTmp && pTmp2!=aTmp2 ){
-    fts3PoslistMerge(pp, &aTmp, &aTmp2);
-  }else if( pTmp1!=aTmp ){
-    fts3PoslistCopy(pp, &aTmp);
-  }else if( pTmp2!=aTmp2 ){
-    fts3PoslistCopy(pp, &aTmp2);
-  }else{
-    res = 0;
+/*
+** Given a input string (which is really one of the argv[] parameters
+** passed into xConnect or xCreate) split the string up into tokens.
+** Return an array of pointers to '\000' terminated strings, one string
+** for each non-whitespace token.
+**
+** The returned array is terminated by a single NULL pointer.
+**
+** Space to hold the returned array is obtained from a single
+** malloc and should be freed by passing the return value to free().
+** The individual strings within the token list are all a part of
+** the single memory allocation and will all be freed at once.
+*/
+static char **tokenizeString(const char *z, int *pnToken){
+  int nToken = 0;
+  FtsToken *aToken = sqlite3_malloc( strlen(z) * sizeof(aToken[0]) );
+  int n = 1;
+  int e, i;
+  int totalSize = 0;
+  char **azToken;
+  char *zCopy;
+  while( n>0 ){
+    n = ftsGetToken(z, &e);
+    if( e!=TOKEN_SPACE ){
+      aToken[nToken].z = z;
+      aToken[nToken].n = n;
+      nToken++;
+      totalSize += n+1;
+    }
+    z += n;
   }
-
-  return res;
+  azToken = (char**)sqlite3_malloc( nToken*sizeof(char*) + totalSize );
+  zCopy = (char*)&azToken[nToken];
+  nToken--;
+  for(i=0; i<nToken; i++){
+    azToken[i] = zCopy;
+    n = aToken[i].n;
+    memcpy(zCopy, aToken[i].z, n);
+    zCopy[n] = 0;
+    zCopy += n+1;
+  }
+  azToken[nToken] = 0;
+  sqlite3_free(aToken);
+  *pnToken = nToken;
+  return azToken;
 }
 
-/* 
-** An instance of this function is used to merge together the (potentially
-** large number of) doclists for each term that matches a prefix query.
-** See function fts3TermSelectMerge() for details.
-*/
-typedef struct TermSelect TermSelect;
-struct TermSelect {
-  char *aaOutput[16];             /* Malloc'd output buffers */
-  int anOutput[16];               /* Size each output buffer in bytes */
-};
-
 /*
-** This function is used to read a single varint from a buffer. Parameter
-** pEnd points 1 byte past the end of the buffer. When this function is
-** called, if *pp points to pEnd or greater, then the end of the buffer
-** has been reached. In this case *pp is set to 0 and the function returns.
-**
-** If *pp does not point to or past pEnd, then a single varint is read
-** from *pp. *pp is then set to point 1 byte past the end of the read varint.
-**
-** If bDescIdx is false, the value read is added to *pVal before returning.
-** If it is true, the value read is subtracted from *pVal before this 
-** function returns.
-*/
-static void fts3GetDeltaVarint3(
-  char **pp,                      /* IN/OUT: Point to read varint from */
-  char *pEnd,                     /* End of buffer */
-  int bDescIdx,                   /* True if docids are descending */
-  sqlite3_int64 *pVal             /* IN/OUT: Integer value */
-){
-  if( *pp>=pEnd ){
-    *pp = 0;
-  }else{
-    sqlite3_int64 iVal;
-    *pp += sqlite3Fts3GetVarint(*pp, &iVal);
-    if( bDescIdx ){
-      *pVal -= iVal;
+** Convert an SQL-style quoted string into a normal string by removing
+** the quote characters.  The conversion is done in-place.  If the
+** input does not begin with a quote character, then this routine
+** is a no-op.
+**
+** Examples:
+**
+**     "abc"   becomes   abc
+**     'xyz'   becomes   xyz
+**     [pqr]   becomes   pqr
+**     `mno`   becomes   mno
+*/
+static void dequoteString(char *z){
+  int quote;
+  int i, j;
+  if( z==0 ) return;
+  quote = z[0];
+  switch( quote ){
+    case '\'':  break;
+    case '"':   break;
+    case '`':   break;                /* For MySQL compatibility */
+    case '[':   quote = ']';  break;  /* For MS SqlServer compatibility */
+    default:    return;
+  }
+  for(i=1, j=0; z[i]; i++){
+    if( z[i]==quote ){
+      if( z[i+1]==quote ){
+        z[j++] = quote;
+        i++;
+      }else{
+        z[j++] = 0;
+        break;
+      }
     }else{
-      *pVal += iVal;
+      z[j++] = z[i];
     }
   }
 }
 
 /*
-** This function is used to write a single varint to a buffer. The varint
-** is written to *pp. Before returning, *pp is set to point 1 byte past the
-** end of the value written.
-**
-** If *pbFirst is zero when this function is called, the value written to
-** the buffer is that of parameter iVal. 
-**
-** If *pbFirst is non-zero when this function is called, then the value 
-** written is either (iVal-*piPrev) (if bDescIdx is zero) or (*piPrev-iVal)
-** (if bDescIdx is non-zero).
-**
-** Before returning, this function always sets *pbFirst to 1 and *piPrev
-** to the value of parameter iVal.
-*/
-static void fts3PutDeltaVarint3(
-  char **pp,                      /* IN/OUT: Output pointer */
-  int bDescIdx,                   /* True for descending docids */
-  sqlite3_int64 *piPrev,          /* IN/OUT: Previous value written to list */
-  int *pbFirst,                   /* IN/OUT: True after first int written */
-  sqlite3_int64 iVal              /* Write this value to the list */
-){
-  sqlite3_int64 iWrite;
-  if( bDescIdx==0 || *pbFirst==0 ){
-    iWrite = iVal - *piPrev;
-  }else{
-    iWrite = *piPrev - iVal;
+** The input azIn is a NULL-terminated list of tokens.  Remove the first
+** token and all punctuation tokens.  Remove the quotes from
+** around string literal tokens.
+**
+** Example:
+**
+**     input:      tokenize chinese ( 'simplifed' , 'mixed' )
+**     output:     chinese simplifed mixed
+**
+** Another example:
+**
+**     input:      delimiters ( '[' , ']' , '...' )
+**     output:     [ ] ...
+*/
+static void tokenListToIdList(char **azIn){
+  int i, j;
+  if( azIn ){
+    for(i=0, j=-1; azIn[i]; i++){
+      if( safe_isalnum(azIn[i][0]) || azIn[i][1] ){
+        dequoteString(azIn[i]);
+        if( j>=0 ){
+          azIn[j] = azIn[i];
+        }
+        j++;
+      }
+    }
+    azIn[j] = 0;
   }
-  assert( *pbFirst || *piPrev==0 );
-  assert( *pbFirst==0 || iWrite>0 );
-  *pp += sqlite3Fts3PutVarint(*pp, iWrite);
-  *piPrev = iVal;
-  *pbFirst = 1;
 }
 
 
 /*
-** This macro is used by various functions that merge doclists. The two
-** arguments are 64-bit docid values. If the value of the stack variable
-** bDescDoclist is 0 when this macro is invoked, then it returns (i1-i2). 
-** Otherwise, (i2-i1).
-**
-** Using this makes it easier to write code that can merge doclists that are
-** sorted in either ascending or descending order.
+** Find the first alphanumeric token in the string zIn.  Null-terminate
+** this token.  Remove any quotation marks.  And return a pointer to
+** the result.
 */
-#define DOCID_CMP(i1, i2) ((bDescDoclist?-1:1) * (i1-i2))
-
-/*
-** This function does an "OR" merge of two doclists (output contains all
-** positions contained in either argument doclist). If the docids in the 
-** input doclists are sorted in ascending order, parameter bDescDoclist
-** should be false. If they are sorted in ascending order, it should be
-** passed a non-zero value.
-**
-** If no error occurs, *paOut is set to point at an sqlite3_malloc'd buffer
-** containing the output doclist and SQLITE_OK is returned. In this case
-** *pnOut is set to the number of bytes in the output doclist.
-**
-** If an error occurs, an SQLite error code is returned. The output values
-** are undefined in this case.
-*/
-static int fts3DoclistOrMerge(
-  int bDescDoclist,               /* True if arguments are desc */
-  char *a1, int n1,               /* First doclist */
-  char *a2, int n2,               /* Second doclist */
-  char **paOut, int *pnOut        /* OUT: Malloc'd doclist */
-){
-  sqlite3_int64 i1 = 0;
-  sqlite3_int64 i2 = 0;
-  sqlite3_int64 iPrev = 0;
-  char *pEnd1 = &a1[n1];
-  char *pEnd2 = &a2[n2];
-  char *p1 = a1;
-  char *p2 = a2;
-  char *p;
-  char *aOut;
-  int bFirstOut = 0;
-
-  *paOut = 0;
-  *pnOut = 0;
-
-  /* Allocate space for the output. Both the input and output doclists
-  ** are delta encoded. If they are in ascending order (bDescDoclist==0),
-  ** then the first docid in each list is simply encoded as a varint. For
-  ** each subsequent docid, the varint stored is the difference between the
-  ** current and previous docid (a positive number - since the list is in
-  ** ascending order).
-  **
-  ** The first docid written to the output is therefore encoded using the 
-  ** same number of bytes as it is in whichever of the input lists it is
-  ** read from. And each subsequent docid read from the same input list 
-  ** consumes either the same or less bytes as it did in the input (since
-  ** the difference between it and the previous value in the output must
-  ** be a positive value less than or equal to the delta value read from 
-  ** the input list). The same argument applies to all but the first docid
-  ** read from the 'other' list. And to the contents of all position lists
-  ** that will be copied and merged from the input to the output.
-  **
-  ** However, if the first docid copied to the output is a negative number,
-  ** then the encoding of the first docid from the 'other' input list may
-  ** be larger in the output than it was in the input (since the delta value
-  ** may be a larger positive integer than the actual docid).
-  **
-  ** The space required to store the output is therefore the sum of the
-  ** sizes of the two inputs, plus enough space for exactly one of the input
-  ** docids to grow. 
-  **
-  ** A symetric argument may be made if the doclists are in descending 
-  ** order.
-  */
-  aOut = sqlite3_malloc(n1+n2+FTS3_VARINT_MAX-1);
-  if( !aOut ) return SQLITE_NOMEM;
-
-  p = aOut;
-  fts3GetDeltaVarint3(&p1, pEnd1, 0, &i1);
-  fts3GetDeltaVarint3(&p2, pEnd2, 0, &i2);
-  while( p1 || p2 ){
-    sqlite3_int64 iDiff = DOCID_CMP(i1, i2);
-
-    if( p2 && p1 && iDiff==0 ){
-      fts3PutDeltaVarint3(&p, bDescDoclist, &iPrev, &bFirstOut, i1);
-      fts3PoslistMerge(&p, &p1, &p2);
-      fts3GetDeltaVarint3(&p1, pEnd1, bDescDoclist, &i1);
-      fts3GetDeltaVarint3(&p2, pEnd2, bDescDoclist, &i2);
-    }else if( !p2 || (p1 && iDiff<0) ){
-      fts3PutDeltaVarint3(&p, bDescDoclist, &iPrev, &bFirstOut, i1);
-      fts3PoslistCopy(&p, &p1);
-      fts3GetDeltaVarint3(&p1, pEnd1, bDescDoclist, &i1);
+static char *firstToken(char *zIn, char **pzTail){
+  int n, ttype;
+  while(1){
+    n = ftsGetToken(zIn, &ttype);
+    if( ttype==TOKEN_SPACE ){
+      zIn += n;
+    }else if( ttype==TOKEN_EOF ){
+      *pzTail = zIn;
+      return 0;
     }else{
-      fts3PutDeltaVarint3(&p, bDescDoclist, &iPrev, &bFirstOut, i2);
-      fts3PoslistCopy(&p, &p2);
-      fts3GetDeltaVarint3(&p2, pEnd2, bDescDoclist, &i2);
+      zIn[n] = 0;
+      *pzTail = &zIn[1];
+      dequoteString(zIn);
+      return zIn;
     }
   }
+  /*NOTREACHED*/
+}
 
-  *paOut = aOut;
-  *pnOut = (int)(p-aOut);
-  assert( *pnOut<=n1+n2+FTS3_VARINT_MAX-1 );
-  return SQLITE_OK;
+/* Return true if...
+**
+**   *  s begins with the string t, ignoring case
+**   *  s is longer than t
+**   *  The first character of s beyond t is not a alphanumeric
+** 
+** Ignore leading space in *s.
+**
+** To put it another way, return true if the first token of
+** s[] is t[].
+*/
+static int startsWith(const char *s, const char *t){
+  while( safe_isspace(*s) ){ s++; }
+  while( *t ){
+    if( safe_tolower(*s++)!=safe_tolower(*t++) ) return 0;
+  }
+  return *s!='_' && !safe_isalnum(*s);
 }
 
 /*
-** This function does a "phrase" merge of two doclists. In a phrase merge,
-** the output contains a copy of each position from the right-hand input
-** doclist for which there is a position in the left-hand input doclist
-** exactly nDist tokens before it.
-**
-** If the docids in the input doclists are sorted in ascending order,
-** parameter bDescDoclist should be false. If they are sorted in ascending 
-** order, it should be passed a non-zero value.
-**
-** The right-hand input doclist is overwritten by this function.
-*/
-static int fts3DoclistPhraseMerge(
-  int bDescDoclist,               /* True if arguments are desc */
-  int nDist,                      /* Distance from left to right (1=adjacent) */
-  char *aLeft, int nLeft,         /* Left doclist */
-  char **paRight, int *pnRight    /* IN/OUT: Right/output doclist */
-){
-  sqlite3_int64 i1 = 0;
-  sqlite3_int64 i2 = 0;
-  sqlite3_int64 iPrev = 0;
-  char *aRight = *paRight;
-  char *pEnd1 = &aLeft[nLeft];
-  char *pEnd2 = &aRight[*pnRight];
-  char *p1 = aLeft;
-  char *p2 = aRight;
-  char *p;
-  int bFirstOut = 0;
-  char *aOut;
-
-  assert( nDist>0 );
-  if( bDescDoclist ){
-    aOut = sqlite3_malloc(*pnRight + FTS3_VARINT_MAX);
-    if( aOut==0 ) return SQLITE_NOMEM;
-  }else{
-    aOut = aRight;
-  }
-  p = aOut;
+** An instance of this structure defines the "spec" of a
+** full text index.  This structure is populated by parseSpec
+** and use by fulltextConnect and fulltextCreate.
+*/
+typedef struct TableSpec {
+  const char *zDb;         /* Logical database name */
+  const char *zName;       /* Name of the full-text index */
+  int nColumn;             /* Number of columns to be indexed */
+  char **azColumn;         /* Original names of columns to be indexed */
+  char **azContentColumn;  /* Column names for %_content */
+  char **azTokenizer;      /* Name of tokenizer and its arguments */
+} TableSpec;
+
+/*
+** Reclaim all of the memory used by a TableSpec
+*/
+static void clearTableSpec(TableSpec *p) {
+  sqlite3_free(p->azColumn);
+  sqlite3_free(p->azContentColumn);
+  sqlite3_free(p->azTokenizer);
+}
+
+/* Parse a CREATE VIRTUAL TABLE statement, which looks like this:
+ *
+ * CREATE VIRTUAL TABLE email
+ *        USING fts3(subject, body, tokenize mytokenizer(myarg))
+ *
+ * We return parsed information in a TableSpec structure.
+ * 
+ */
+static int parseSpec(TableSpec *pSpec, int argc, const char *const*argv,
+                     char**pzErr){
+  int i, n;
+  char *z, *zDummy;
+  char **azArg;
+  const char *zTokenizer = 0;    /* argv[] entry describing the tokenizer */
+
+  assert( argc>=3 );
+  /* Current interface:
+  ** argv[0] - module name
+  ** argv[1] - database name
+  ** argv[2] - table name
+  ** argv[3..] - columns, optionally followed by tokenizer specification
+  **             and snippet delimiters specification.
+  */
 
-  fts3GetDeltaVarint3(&p1, pEnd1, 0, &i1);
-  fts3GetDeltaVarint3(&p2, pEnd2, 0, &i2);
+  /* Make a copy of the complete argv[][] array in a single allocation.
+  ** The argv[][] array is read-only and transient.  We can write to the
+  ** copy in order to modify things and the copy is persistent.
+  */
+  CLEAR(pSpec);
+  for(i=n=0; i<argc; i++){
+    n += strlen(argv[i]) + 1;
+  }
+  azArg = sqlite3_malloc( sizeof(char*)*argc + n );
+  if( azArg==0 ){
+    return SQLITE_NOMEM;
+  }
+  z = (char*)&azArg[argc];
+  for(i=0; i<argc; i++){
+    azArg[i] = z;
+    strcpy(z, argv[i]);
+    z += strlen(z)+1;
+  }
 
-  while( p1 && p2 ){
-    sqlite3_int64 iDiff = DOCID_CMP(i1, i2);
-    if( iDiff==0 ){
-      char *pSave = p;
-      sqlite3_int64 iPrevSave = iPrev;
-      int bFirstOutSave = bFirstOut;
-
-      fts3PutDeltaVarint3(&p, bDescDoclist, &iPrev, &bFirstOut, i1);
-      if( 0==fts3PoslistPhraseMerge(&p, nDist, 0, 1, &p1, &p2) ){
-        p = pSave;
-        iPrev = iPrevSave;
-        bFirstOut = bFirstOutSave;
-      }
-      fts3GetDeltaVarint3(&p1, pEnd1, bDescDoclist, &i1);
-      fts3GetDeltaVarint3(&p2, pEnd2, bDescDoclist, &i2);
-    }else if( iDiff<0 ){
-      fts3PoslistCopy(0, &p1);
-      fts3GetDeltaVarint3(&p1, pEnd1, bDescDoclist, &i1);
+  /* Identify the column names and the tokenizer and delimiter arguments
+  ** in the argv[][] array.
+  */
+  pSpec->zDb = azArg[1];
+  pSpec->zName = azArg[2];
+  pSpec->nColumn = 0;
+  pSpec->azColumn = azArg;
+  zTokenizer = "tokenize simple";
+  for(i=3; i<argc; ++i){
+    if( startsWith(azArg[i],"tokenize") ){
+      zTokenizer = azArg[i];
     }else{
-      fts3PoslistCopy(0, &p2);
-      fts3GetDeltaVarint3(&p2, pEnd2, bDescDoclist, &i2);
+      z = azArg[pSpec->nColumn] = firstToken(azArg[i], &zDummy);
+      pSpec->nColumn++;
     }
   }
+  if( pSpec->nColumn==0 ){
+    azArg[0] = "content";
+    pSpec->nColumn = 1;
+  }
 
-  *pnRight = (int)(p - aOut);
-  if( bDescDoclist ){
-    sqlite3_free(aRight);
-    *paRight = aOut;
+  /*
+  ** Construct the list of content column names.
+  **
+  ** Each content column name will be of the form cNNAAAA
+  ** where NN is the column number and AAAA is the sanitized
+  ** column name.  "sanitized" means that special characters are
+  ** converted to "_".  The cNN prefix guarantees that all column
+  ** names are unique.
+  **
+  ** The AAAA suffix is not strictly necessary.  It is included
+  ** for the convenience of people who might examine the generated
+  ** %_content table and wonder what the columns are used for.
+  */
+  pSpec->azContentColumn = sqlite3_malloc( pSpec->nColumn * sizeof(char *) );
+  if( pSpec->azContentColumn==0 ){
+    clearTableSpec(pSpec);
+    return SQLITE_NOMEM;
+  }
+  for(i=0; i<pSpec->nColumn; i++){
+    char *p;
+    pSpec->azContentColumn[i] = sqlite3_mprintf("c%d%s", i, azArg[i]);
+    for (p = pSpec->azContentColumn[i]; *p ; ++p) {
+      if( !safe_isalnum(*p) ) *p = '_';
+    }
   }
 
+  /*
+  ** Parse the tokenizer specification string.
+  */
+  pSpec->azTokenizer = tokenizeString(zTokenizer, &n);
+  tokenListToIdList(pSpec->azTokenizer);
+
   return SQLITE_OK;
 }
 
 /*
-** Argument pList points to a position list nList bytes in size. This
-** function checks to see if the position list contains any entries for
-** a token in position 0 (of any column). If so, it writes argument iDelta
-** to the output buffer pOut, followed by a position list consisting only
-** of the entries from pList at position 0, and terminated by an 0x00 byte.
-** The value returned is the number of bytes written to pOut (if any).
-*/
-int sqlite3Fts3FirstFilter(
-  sqlite3_int64 iDelta,           /* Varint that may be written to pOut */
-  char *pList,                    /* Position list (no 0x00 term) */
-  int nList,                      /* Size of pList in bytes */
-  char *pOut                      /* Write output here */
+** Generate a CREATE TABLE statement that describes the schema of
+** the virtual table.  Return a pointer to this schema string.
+**
+** Space is obtained from sqlite3_mprintf() and should be freed
+** using sqlite3_free().
+*/
+static char *fulltextSchema(
+  int nColumn,                  /* Number of columns */
+  const char *const* azColumn,  /* List of columns */
+  const char *zTableName        /* Name of the table */
 ){
-  int nOut = 0;
-  int bWritten = 0;               /* True once iDelta has been written */
-  char *p = pList;
-  char *pEnd = &pList[nList];
-
-  if( *p!=0x01 ){
-    if( *p==0x02 ){
-      nOut += sqlite3Fts3PutVarint(&pOut[nOut], iDelta);
-      pOut[nOut++] = 0x02;
-      bWritten = 1;
-    }
-    fts3ColumnlistCopy(0, &p);
+  int i;
+  char *zSchema, *zNext;
+  const char *zSep = "(";
+  zSchema = sqlite3_mprintf("CREATE TABLE x");
+  for(i=0; i<nColumn; i++){
+    zNext = sqlite3_mprintf("%s%s%Q", zSchema, zSep, azColumn[i]);
+    sqlite3_free(zSchema);
+    zSchema = zNext;
+    zSep = ",";
+  }
+  zNext = sqlite3_mprintf("%s,%Q HIDDEN", zSchema, zTableName);
+  sqlite3_free(zSchema);
+  zSchema = zNext;
+  zNext = sqlite3_mprintf("%s,docid HIDDEN)", zSchema);
+  sqlite3_free(zSchema);
+  return zNext;
+}
+
+/*
+** Build a new sqlite3_vtab structure that will describe the
+** fulltext index defined by spec.
+*/
+static int constructVtab(
+  sqlite3 *db,              /* The SQLite database connection */
+  fts3Hash *pHash,          /* Hash table containing tokenizers */
+  TableSpec *spec,          /* Parsed spec information from parseSpec() */
+  sqlite3_vtab **ppVTab,    /* Write the resulting vtab structure here */
+  char **pzErr              /* Write any error message here */
+){
+  int rc;
+  int n;
+  fulltext_vtab *v = 0;
+  const sqlite3_tokenizer_module *m = NULL;
+  char *schema;
+
+  char const *zTok;         /* Name of tokenizer to use for this fts table */
+  int nTok;                 /* Length of zTok, including nul terminator */
+
+  v = (fulltext_vtab *) sqlite3_malloc(sizeof(fulltext_vtab));
+  if( v==0 ) return SQLITE_NOMEM;
+  CLEAR(v);
+  /* sqlite will initialize v->base */
+  v->db = db;
+  v->zDb = spec->zDb;       /* Freed when azColumn is freed */
+  v->zName = spec->zName;   /* Freed when azColumn is freed */
+  v->nColumn = spec->nColumn;
+  v->azContentColumn = spec->azContentColumn;
+  spec->azContentColumn = 0;
+  v->azColumn = spec->azColumn;
+  spec->azColumn = 0;
+
+  if( spec->azTokenizer==0 ){
+    return SQLITE_NOMEM;
   }
 
-  while( p<pEnd ){
-    sqlite3_int64 iCol;
-    p++;
-    p += sqlite3Fts3GetVarint(p, &iCol);
-    if( *p==0x02 ){
-      if( bWritten==0 ){
-        nOut += sqlite3Fts3PutVarint(&pOut[nOut], iDelta);
-        bWritten = 1;
-      }
-      pOut[nOut++] = 0x01;
-      nOut += sqlite3Fts3PutVarint(&pOut[nOut], iCol);
-      pOut[nOut++] = 0x02;
-    }
-    fts3ColumnlistCopy(0, &p);
+  zTok = spec->azTokenizer[0]; 
+  if( !zTok ){
+    zTok = "simple";
+  }
+  nTok = strlen(zTok)+1;
+
+  m = (sqlite3_tokenizer_module *)sqlite3Fts3HashFind(pHash, zTok, nTok);
+  if( !m ){
+    *pzErr = sqlite3_mprintf("unknown tokenizer: %s", spec->azTokenizer[0]);
+    rc = SQLITE_ERROR;
+    goto err;
   }
-  if( bWritten ){
-    pOut[nOut++] = 0x00;
+
+  for(n=0; spec->azTokenizer[n]; n++){}
+  if( n ){
+    rc = m->xCreate(n-1, (const char*const*)&spec->azTokenizer[1],
+                    &v->pTokenizer);
+  }else{
+    rc = m->xCreate(0, 0, &v->pTokenizer);
   }
+  if( rc!=SQLITE_OK ) goto err;
+  v->pTokenizer->pModule = m;
 
-  return nOut;
-}
+  /* TODO: verify the existence of backing tables foo_content, foo_term */
 
+  schema = fulltextSchema(v->nColumn, (const char*const*)v->azColumn,
+                          spec->zName);
+  rc = sqlite3_declare_vtab(db, schema);
+  sqlite3_free(schema);
+  if( rc!=SQLITE_OK ) goto err;
 
-/*
-** Merge all doclists in the TermSelect.aaOutput[] array into a single
-** doclist stored in TermSelect.aaOutput[0]. If successful, delete all
-** other doclists (except the aaOutput[0] one) and return SQLITE_OK.
-**
-** If an OOM error occurs, return SQLITE_NOMEM. In this case it is
-** the responsibility of the caller to free any doclists left in the
-** TermSelect.aaOutput[] array.
-*/
-static int fts3TermSelectFinishMerge(Fts3Table *p, TermSelect *pTS){
-  char *aOut = 0;
-  int nOut = 0;
-  int i;
+  memset(v->pFulltextStatements, 0, sizeof(v->pFulltextStatements));
 
-  /* Loop through the doclists in the aaOutput[] array. Merge them all
-  ** into a single doclist.
-  */
-  for(i=0; i<SizeofArray(pTS->aaOutput); i++){
-    if( pTS->aaOutput[i] ){
-      if( !aOut ){
-        aOut = pTS->aaOutput[i];
-        nOut = pTS->anOutput[i];
-        pTS->aaOutput[i] = 0;
-      }else{
-        int nNew;
-        char *aNew;
+  /* Indicate that the buffer is not live. */
+  v->nPendingData = -1;
 
-        int rc = fts3DoclistOrMerge(p->bDescIdx, 
-            pTS->aaOutput[i], pTS->anOutput[i], aOut, nOut, &aNew, &nNew
-        );
-        if( rc!=SQLITE_OK ){
-          sqlite3_free(aOut);
-          return rc;
-        }
+  *ppVTab = &v->base;
+  FTSTRACE(("FTS3 Connect %p\n", v));
 
-        sqlite3_free(pTS->aaOutput[i]);
-        sqlite3_free(aOut);
-        pTS->aaOutput[i] = 0;
-        aOut = aNew;
-        nOut = nNew;
-      }
-    }
-  }
+  return rc;
 
-  pTS->aaOutput[0] = aOut;
-  pTS->anOutput[0] = nOut;
-  return SQLITE_OK;
+err:
+  fulltext_vtab_destroy(v);
+  return rc;
 }
 
-/*
-** Merge the doclist aDoclist/nDoclist into the TermSelect object passed
-** as the first argument. The merge is an "OR" merge (see function
-** fts3DoclistOrMerge() for details).
-**
-** This function is called with the doclist for each term that matches
-** a queried prefix. It merges all these doclists into one, the doclist
-** for the specified prefix. Since there can be a very large number of
-** doclists to merge, the merging is done pair-wise using the TermSelect
-** object.
-**
-** This function returns SQLITE_OK if the merge is successful, or an
-** SQLite error code (SQLITE_NOMEM) if an error occurs.
-*/
-static int fts3TermSelectMerge(
-  Fts3Table *p,                   /* FTS table handle */
-  TermSelect *pTS,                /* TermSelect object to merge into */
-  char *aDoclist,                 /* Pointer to doclist */
-  int nDoclist                    /* Size of aDoclist in bytes */
+static int fulltextConnect(
+  sqlite3 *db,
+  void *pAux,
+  int argc, const char *const*argv,
+  sqlite3_vtab **ppVTab,
+  char **pzErr
 ){
-  if( pTS->aaOutput[0]==0 ){
-    /* If this is the first term selected, copy the doclist to the output
-    ** buffer using memcpy(). 
-    **
-    ** Add FTS3_VARINT_MAX bytes of unused space to the end of the 
-    ** allocation. This is so as to ensure that the buffer is big enough
-    ** to hold the current doclist AND'd with any other doclist. If the
-    ** doclists are stored in order=ASC order, this padding would not be
-    ** required (since the size of [doclistA AND doclistB] is always less
-    ** than or equal to the size of [doclistA] in that case). But this is
-    ** not true for order=DESC. For example, a doclist containing (1, -1) 
-    ** may be smaller than (-1), as in the first example the -1 may be stored
-    ** as a single-byte delta, whereas in the second it must be stored as a
-    ** FTS3_VARINT_MAX byte varint.
-    **
-    ** Similar padding is added in the fts3DoclistOrMerge() function.
-    */
-    pTS->aaOutput[0] = sqlite3_malloc(nDoclist + FTS3_VARINT_MAX + 1);
-    pTS->anOutput[0] = nDoclist;
-    if( pTS->aaOutput[0] ){
-      memcpy(pTS->aaOutput[0], aDoclist, nDoclist);
-    }else{
-      return SQLITE_NOMEM;
-    }
-  }else{
-    char *aMerge = aDoclist;
-    int nMerge = nDoclist;
-    int iOut;
-
-    for(iOut=0; iOut<SizeofArray(pTS->aaOutput); iOut++){
-      if( pTS->aaOutput[iOut]==0 ){
-        assert( iOut>0 );
-        pTS->aaOutput[iOut] = aMerge;
-        pTS->anOutput[iOut] = nMerge;
-        break;
-      }else{
-        char *aNew;
-        int nNew;
-
-        int rc = fts3DoclistOrMerge(p->bDescIdx, aMerge, nMerge, 
-            pTS->aaOutput[iOut], pTS->anOutput[iOut], &aNew, &nNew
-        );
-        if( rc!=SQLITE_OK ){
-          if( aMerge!=aDoclist ) sqlite3_free(aMerge);
-          return rc;
-        }
+  TableSpec spec;
+  int rc = parseSpec(&spec, argc, argv, pzErr);
+  if( rc!=SQLITE_OK ) return rc;
 
-        if( aMerge!=aDoclist ) sqlite3_free(aMerge);
-        sqlite3_free(pTS->aaOutput[iOut]);
-        pTS->aaOutput[iOut] = 0;
-  
-        aMerge = aNew;
-        nMerge = nNew;
-        if( (iOut+1)==SizeofArray(pTS->aaOutput) ){
-          pTS->aaOutput[iOut] = aMerge;
-          pTS->anOutput[iOut] = nMerge;
-        }
-      }
-    }
-  }
-  return SQLITE_OK;
+  rc = constructVtab(db, (fts3Hash *)pAux, &spec, ppVTab, pzErr);
+  clearTableSpec(&spec);
+  return rc;
 }
 
-/*
-** Append SegReader object pNew to the end of the pCsr->apSegment[] array.
+/* The %_content table holds the text of each document, with
+** the docid column exposed as the SQLite rowid for the table.
 */
-static int fts3SegReaderCursorAppend(
-  Fts3MultiSegReader *pCsr, 
-  Fts3SegReader *pNew
-){
-  if( (pCsr->nSegment%16)==0 ){
-    Fts3SegReader **apNew;
-    int nByte = (pCsr->nSegment + 16)*sizeof(Fts3SegReader*);
-    apNew = (Fts3SegReader **)sqlite3_realloc(pCsr->apSegment, nByte);
-    if( !apNew ){
-      sqlite3Fts3SegReaderFree(pNew);
-      return SQLITE_NOMEM;
+/* TODO(shess) This comment needs elaboration to match the updated
+** code.  Work it into the top-of-file comment at that time.
+*/
+static int fulltextCreate(sqlite3 *db, void *pAux,
+                          int argc, const char * const *argv,
+                          sqlite3_vtab **ppVTab, char **pzErr){
+  int rc;
+  TableSpec spec;
+  StringBuffer schema;
+  FTSTRACE(("FTS3 Create\n"));
+
+  rc = parseSpec(&spec, argc, argv, pzErr);
+  if( rc!=SQLITE_OK ) return rc;
+
+  initStringBuffer(&schema);
+  append(&schema, "CREATE TABLE %_content(");
+  append(&schema, "  docid INTEGER PRIMARY KEY,");
+  appendList(&schema, spec.nColumn, spec.azContentColumn);
+  append(&schema, ")");
+  rc = sql_exec(db, spec.zDb, spec.zName, stringBufferData(&schema));
+  stringBufferDestroy(&schema);
+  if( rc!=SQLITE_OK ) goto out;
+
+  rc = sql_exec(db, spec.zDb, spec.zName,
+                "create table %_segments("
+                "  blockid INTEGER PRIMARY KEY,"
+                "  block blob"
+                ");"
+                );
+  if( rc!=SQLITE_OK ) goto out;
+
+  rc = sql_exec(db, spec.zDb, spec.zName,
+                "create table %_segdir("
+                "  level integer,"
+                "  idx integer,"
+                "  start_block integer,"
+                "  leaves_end_block integer,"
+                "  end_block integer,"
+                "  root blob,"
+                "  primary key(level, idx)"
+                ");");
+  if( rc!=SQLITE_OK ) goto out;
+
+  rc = constructVtab(db, (fts3Hash *)pAux, &spec, ppVTab, pzErr);
+
+out:
+  clearTableSpec(&spec);
+  return rc;
+}
+
+/* Decide how to handle an SQL query. */
+static int fulltextBestIndex(sqlite3_vtab *pVTab, sqlite3_index_info *pInfo){
+  fulltext_vtab *v = (fulltext_vtab *)pVTab;
+  int i;
+  FTSTRACE(("FTS3 BestIndex\n"));
+
+  for(i=0; i<pInfo->nConstraint; ++i){
+    const struct sqlite3_index_constraint *pConstraint;
+    pConstraint = &pInfo->aConstraint[i];
+    if( pConstraint->usable ) {
+      if( (pConstraint->iColumn==-1 || pConstraint->iColumn==v->nColumn+1) &&
+          pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ ){
+        pInfo->idxNum = QUERY_DOCID;      /* lookup by docid */
+        FTSTRACE(("FTS3 QUERY_DOCID\n"));
+      } else if( pConstraint->iColumn>=0 && pConstraint->iColumn<=v->nColumn &&
+                 pConstraint->op==SQLITE_INDEX_CONSTRAINT_MATCH ){
+        /* full-text search */
+        pInfo->idxNum = QUERY_FULLTEXT + pConstraint->iColumn;
+        FTSTRACE(("FTS3 QUERY_FULLTEXT %d\n", pConstraint->iColumn));
+      } else continue;
+
+      pInfo->aConstraintUsage[i].argvIndex = 1;
+      pInfo->aConstraintUsage[i].omit = 1;
+
+      /* An arbitrary value for now.
+       * TODO: Perhaps docid matches should be considered cheaper than
+       * full-text searches. */
+      pInfo->estimatedCost = 1.0;   
+
+      return SQLITE_OK;
     }
-    pCsr->apSegment = apNew;
   }
-  pCsr->apSegment[pCsr->nSegment++] = pNew;
+  pInfo->idxNum = QUERY_GENERIC;
   return SQLITE_OK;
 }
 
-/*
-** Add seg-reader objects to the Fts3MultiSegReader object passed as the
-** 8th argument.
-**
-** This function returns SQLITE_OK if successful, or an SQLite error code
-** otherwise.
-*/
-static int fts3SegReaderCursor(
-  Fts3Table *p,                   /* FTS3 table handle */
-  int iLangid,                    /* Language id */
-  int iIndex,                     /* Index to search (from 0 to p->nIndex-1) */
-  int iLevel,                     /* Level of segments to scan */
-  const char *zTerm,              /* Term to query for */
-  int nTerm,                      /* Size of zTerm in bytes */
-  int isPrefix,                   /* True for a prefix search */
-  int isScan,                     /* True to scan from zTerm to EOF */
-  Fts3MultiSegReader *pCsr        /* Cursor object to populate */
-){
-  int rc = SQLITE_OK;             /* Error code */
-  sqlite3_stmt *pStmt = 0;        /* Statement to iterate through segments */
-  int rc2;                        /* Result of sqlite3_reset() */
-
-  /* If iLevel is less than 0 and this is not a scan, include a seg-reader 
-  ** for the pending-terms. If this is a scan, then this call must be being
-  ** made by an fts4aux module, not an FTS table. In this case calling
-  ** Fts3SegReaderPending might segfault, as the data structures used by 
-  ** fts4aux are not completely populated. So it's easiest to filter these
-  ** calls out here.  */
-  if( iLevel<0 && p->aIndex ){
-    Fts3SegReader *pSeg = 0;
-    rc = sqlite3Fts3SegReaderPending(p, iIndex, zTerm, nTerm, isPrefix||isScan, &pSeg);
-    if( rc==SQLITE_OK && pSeg ){
-      rc = fts3SegReaderCursorAppend(pCsr, pSeg);
-    }
-  }
+static int fulltextDisconnect(sqlite3_vtab *pVTab){
+  FTSTRACE(("FTS3 Disconnect %p\n", pVTab));
+  fulltext_vtab_destroy((fulltext_vtab *)pVTab);
+  return SQLITE_OK;
+}
 
-  if( iLevel!=FTS3_SEGCURSOR_PENDING ){
-    if( rc==SQLITE_OK ){
-      rc = sqlite3Fts3AllSegdirs(p, iLangid, iIndex, iLevel, &pStmt);
-    }
+static int fulltextDestroy(sqlite3_vtab *pVTab){
+  fulltext_vtab *v = (fulltext_vtab *)pVTab;
+  int rc;
 
-    while( rc==SQLITE_OK && SQLITE_ROW==(rc = sqlite3_step(pStmt)) ){
-      Fts3SegReader *pSeg = 0;
+  FTSTRACE(("FTS3 Destroy %p\n", pVTab));
+  rc = sql_exec(v->db, v->zDb, v->zName,
+                "drop table if exists %_content;"
+                "drop table if exists %_segments;"
+                "drop table if exists %_segdir;"
+                );
+  if( rc!=SQLITE_OK ) return rc;
 
-      /* Read the values returned by the SELECT into local variables. */
-      sqlite3_int64 iStartBlock = sqlite3_column_int64(pStmt, 1);
-      sqlite3_int64 iLeavesEndBlock = sqlite3_column_int64(pStmt, 2);
-      sqlite3_int64 iEndBlock = sqlite3_column_int64(pStmt, 3);
-      int nRoot = sqlite3_column_bytes(pStmt, 4);
-      char const *zRoot = sqlite3_column_blob(pStmt, 4);
-
-      /* If zTerm is not NULL, and this segment is not stored entirely on its
-      ** root node, the range of leaves scanned can be reduced. Do this. */
-      if( iStartBlock && zTerm ){
-        sqlite3_int64 *pi = (isPrefix ? &iLeavesEndBlock : 0);
-        rc = fts3SelectLeaf(p, zTerm, nTerm, zRoot, nRoot, &iStartBlock, pi);
-        if( rc!=SQLITE_OK ) goto finished;
-        if( isPrefix==0 && isScan==0 ) iLeavesEndBlock = iStartBlock;
-      }
- 
-      rc = sqlite3Fts3SegReaderNew(pCsr->nSegment+1, 
-          (isPrefix==0 && isScan==0),
-          iStartBlock, iLeavesEndBlock, 
-          iEndBlock, zRoot, nRoot, &pSeg
-      );
-      if( rc!=SQLITE_OK ) goto finished;
-      rc = fts3SegReaderCursorAppend(pCsr, pSeg);
-    }
-  }
+  fulltext_vtab_destroy((fulltext_vtab *)pVTab);
+  return SQLITE_OK;
+}
 
- finished:
-  rc2 = sqlite3_reset(pStmt);
-  if( rc==SQLITE_DONE ) rc = rc2;
+static int fulltextOpen(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor){
+  fulltext_cursor *c;
 
-  return rc;
+  c = (fulltext_cursor *) sqlite3_malloc(sizeof(fulltext_cursor));
+  if( c ){
+    memset(c, 0, sizeof(fulltext_cursor));
+    /* sqlite will initialize c->base */
+    *ppCursor = &c->base;
+    FTSTRACE(("FTS3 Open %p: %p\n", pVTab, c));
+    return SQLITE_OK;
+  }else{
+    return SQLITE_NOMEM;
+  }
 }
 
-/*
-** Set up a cursor object for iterating through a full-text index or a 
-** single level therein.
+/* Free all of the dynamically allocated memory held by the
+** Snippet
 */
-int sqlite3Fts3SegReaderCursor(
-  Fts3Table *p,                   /* FTS3 table handle */
-  int iLangid,                    /* Language-id to search */
-  int iIndex,                     /* Index to search (from 0 to p->nIndex-1) */
-  int iLevel,                     /* Level of segments to scan */
-  const char *zTerm,              /* Term to query for */
-  int nTerm,                      /* Size of zTerm in bytes */
-  int isPrefix,                   /* True for a prefix search */
-  int isScan,                     /* True to scan from zTerm to EOF */
-  Fts3MultiSegReader *pCsr       /* Cursor object to populate */
-){
-  assert( iIndex>=0 && iIndex<p->nIndex );
-  assert( iLevel==FTS3_SEGCURSOR_ALL
-      ||  iLevel==FTS3_SEGCURSOR_PENDING 
-      ||  iLevel>=0
-  );
-  assert( iLevel<FTS3_SEGDIR_MAXLEVEL );
-  assert( FTS3_SEGCURSOR_ALL<0 && FTS3_SEGCURSOR_PENDING<0 );
-  assert( isPrefix==0 || isScan==0 );
-
-  memset(pCsr, 0, sizeof(Fts3MultiSegReader));
-  return fts3SegReaderCursor(
-      p, iLangid, iIndex, iLevel, zTerm, nTerm, isPrefix, isScan, pCsr
-  );
+static void snippetClear(Snippet *p){
+  sqlite3_free(p->aMatch);
+  sqlite3_free(p->zOffset);
+  sqlite3_free(p->zSnippet);
+  CLEAR(p);
 }
 
 /*
-** In addition to its current configuration, have the Fts3MultiSegReader
-** passed as the 4th argument also scan the doclist for term zTerm/nTerm.
-**
-** SQLITE_OK is returned if no error occurs, otherwise an SQLite error code.
+** Append a single entry to the p->aMatch[] log.
 */
-static int fts3SegReaderCursorAddZero(
-  Fts3Table *p,                   /* FTS virtual table handle */
-  int iLangid,
-  const char *zTerm,              /* Term to scan doclist of */
-  int nTerm,                      /* Number of bytes in zTerm */
-  Fts3MultiSegReader *pCsr        /* Fts3MultiSegReader to modify */
+static void snippetAppendMatch(
+  Snippet *p,               /* Append the entry to this snippet */
+  int iCol, int iTerm,      /* The column and query term */
+  int iToken,               /* Matching token in document */
+  int iStart, int nByte     /* Offset and size of the match */
 ){
-  return fts3SegReaderCursor(p, 
-      iLangid, 0, FTS3_SEGCURSOR_ALL, zTerm, nTerm, 0, 0,pCsr
-  );
+  int i;
+  struct snippetMatch *pMatch;
+  if( p->nMatch+1>=p->nAlloc ){
+    p->nAlloc = p->nAlloc*2 + 10;
+    p->aMatch = sqlite3_realloc(p->aMatch, p->nAlloc*sizeof(p->aMatch[0]) );
+    if( p->aMatch==0 ){
+      p->nMatch = 0;
+      p->nAlloc = 0;
+      return;
+    }
+  }
+  i = p->nMatch++;
+  pMatch = &p->aMatch[i];
+  pMatch->iCol = iCol;
+  pMatch->iTerm = iTerm;
+  pMatch->iToken = iToken;
+  pMatch->iStart = iStart;
+  pMatch->nByte = nByte;
 }
 
 /*
-** Open an Fts3MultiSegReader to scan the doclist for term zTerm/nTerm. Or,
-** if isPrefix is true, to scan the doclist for all terms for which 
-** zTerm/nTerm is a prefix. If successful, return SQLITE_OK and write
-** a pointer to the new Fts3MultiSegReader to *ppSegcsr. Otherwise, return
-** an SQLite error code.
-**
-** It is the responsibility of the caller to free this object by eventually
-** passing it to fts3SegReaderCursorFree() 
-**
-** SQLITE_OK is returned if no error occurs, otherwise an SQLite error code.
-** Output parameter *ppSegcsr is set to 0 if an error occurs.
-*/
-static int fts3TermSegReaderCursor(
-  Fts3Cursor *pCsr,               /* Virtual table cursor handle */
-  const char *zTerm,              /* Term to query for */
-  int nTerm,                      /* Size of zTerm in bytes */
-  int isPrefix,                   /* True for a prefix search */
-  Fts3MultiSegReader **ppSegcsr   /* OUT: Allocated seg-reader cursor */
-){
-  Fts3MultiSegReader *pSegcsr;    /* Object to allocate and return */
-  int rc = SQLITE_NOMEM;          /* Return code */
-
-  pSegcsr = sqlite3_malloc(sizeof(Fts3MultiSegReader));
-  if( pSegcsr ){
-    int i;
-    int bFound = 0;               /* True once an index has been found */
-    Fts3Table *p = (Fts3Table *)pCsr->base.pVtab;
-
-    if( isPrefix ){
-      for(i=1; bFound==0 && i<p->nIndex; i++){
-        if( p->aIndex[i].nPrefix==nTerm ){
-          bFound = 1;
-          rc = sqlite3Fts3SegReaderCursor(p, pCsr->iLangid, 
-              i, FTS3_SEGCURSOR_ALL, zTerm, nTerm, 0, 0, pSegcsr
-          );
-          pSegcsr->bLookup = 1;
-        }
-      }
+** Sizing information for the circular buffer used in snippetOffsetsOfColumn()
+*/
+#define FTS3_ROTOR_SZ   (32)
+#define FTS3_ROTOR_MASK (FTS3_ROTOR_SZ-1)
 
-      for(i=1; bFound==0 && i<p->nIndex; i++){
-        if( p->aIndex[i].nPrefix==nTerm+1 ){
-          bFound = 1;
-          rc = sqlite3Fts3SegReaderCursor(p, pCsr->iLangid, 
-              i, FTS3_SEGCURSOR_ALL, zTerm, nTerm, 1, 0, pSegcsr
-          );
-          if( rc==SQLITE_OK ){
-            rc = fts3SegReaderCursorAddZero(
-                p, pCsr->iLangid, zTerm, nTerm, pSegcsr
-            );
-          }
+/*
+** Function to iterate through the tokens of a compiled expression.
+**
+** Except, skip all tokens on the right-hand side of a NOT operator.
+** This function is used to find tokens as part of snippet and offset
+** generation and we do nt want snippets and offsets to report matches
+** for tokens on the RHS of a NOT.
+*/
+static int fts3NextExprToken(Fts3Expr **ppExpr, int *piToken){
+  Fts3Expr *p = *ppExpr;
+  int iToken = *piToken;
+  if( iToken<0 ){
+    /* In this case the expression p is the root of an expression tree.
+    ** Move to the first token in the expression tree.
+    */
+    while( p->pLeft ){
+      p = p->pLeft;
+    }
+    iToken = 0;
+  }else{
+    assert(p && p->eType==FTSQUERY_PHRASE );
+    if( iToken<(p->pPhrase->nToken-1) ){
+      iToken++;
+    }else{
+      iToken = 0;
+      while( p->pParent && p->pParent->pLeft!=p ){
+        assert( p->pParent->pRight==p );
+        p = p->pParent;
+      }
+      p = p->pParent;
+      if( p ){
+        assert( p->pRight!=0 );
+        p = p->pRight;
+        while( p->pLeft ){
+          p = p->pLeft;
         }
       }
     }
-
-    if( bFound==0 ){
-      rc = sqlite3Fts3SegReaderCursor(p, pCsr->iLangid, 
-          0, FTS3_SEGCURSOR_ALL, zTerm, nTerm, isPrefix, 0, pSegcsr
-      );
-      pSegcsr->bLookup = !isPrefix;
-    }
   }
 
-  *ppSegcsr = pSegcsr;
-  return rc;
+  *ppExpr = p;
+  *piToken = iToken;
+  return p?1:0;
 }
 
 /*
-** Free an Fts3MultiSegReader allocated by fts3TermSegReaderCursor().
+** Return TRUE if the expression node pExpr is located beneath the
+** RHS of a NOT operator.
 */
-static void fts3SegReaderCursorFree(Fts3MultiSegReader *pSegcsr){
-  sqlite3Fts3SegReaderFinish(pSegcsr);
-  sqlite3_free(pSegcsr);
-}
-
-/*
-** This function retrieves the doclist for the specified term (or term
-** prefix) from the database.
-*/
-static int fts3TermSelect(
-  Fts3Table *p,                   /* Virtual table handle */
-  Fts3PhraseToken *pTok,          /* Token to query for */
-  int iColumn,                    /* Column to query (or -ve for all columns) */
-  int *pnOut,                     /* OUT: Size of buffer at *ppOut */
-  char **ppOut                    /* OUT: Malloced result buffer */
-){
-  int rc;                         /* Return code */
-  Fts3MultiSegReader *pSegcsr;    /* Seg-reader cursor for this term */
-  TermSelect tsc;                 /* Object for pair-wise doclist merging */
-  Fts3SegFilter filter;           /* Segment term filter configuration */
-
-  pSegcsr = pTok->pSegcsr;
-  memset(&tsc, 0, sizeof(TermSelect));
-
-  filter.flags = FTS3_SEGMENT_IGNORE_EMPTY | FTS3_SEGMENT_REQUIRE_POS
-        | (pTok->isPrefix ? FTS3_SEGMENT_PREFIX : 0)
-        | (pTok->bFirst ? FTS3_SEGMENT_FIRST : 0)
-        | (iColumn<p->nColumn ? FTS3_SEGMENT_COLUMN_FILTER : 0);
-  filter.iCol = iColumn;
-  filter.zTerm = pTok->z;
-  filter.nTerm = pTok->n;
-
-  rc = sqlite3Fts3SegReaderStart(p, pSegcsr, &filter);
-  while( SQLITE_OK==rc
-      && SQLITE_ROW==(rc = sqlite3Fts3SegReaderStep(p, pSegcsr)) 
-  ){
-    rc = fts3TermSelectMerge(p, &tsc, pSegcsr->aDoclist, pSegcsr->nDoclist);
+static int fts3ExprBeneathNot(Fts3Expr *p){
+  Fts3Expr *pParent;
+  while( p ){
+    pParent = p->pParent;
+    if( pParent && pParent->eType==FTSQUERY_NOT && pParent->pRight==p ){
+      return 1;
+    }
+    p = pParent;
   }
+  return 0;
+}
 
-  if( rc==SQLITE_OK ){
-    rc = fts3TermSelectFinishMerge(p, &tsc);
-  }
-  if( rc==SQLITE_OK ){
-    *ppOut = tsc.aaOutput[0];
-    *pnOut = tsc.anOutput[0];
-  }else{
-    int i;
-    for(i=0; i<SizeofArray(tsc.aaOutput); i++){
-      sqlite3_free(tsc.aaOutput[i]);
+/*
+** Add entries to pSnippet->aMatch[] for every match that occurs against
+** document zDoc[0..nDoc-1] which is stored in column iColumn.
+*/
+static void snippetOffsetsOfColumn(
+  fulltext_cursor *pCur,         /* The fulltest search cursor */
+  Snippet *pSnippet,             /* The Snippet object to be filled in */
+  int iColumn,                   /* Index of fulltext table column */
+  const char *zDoc,              /* Text of the fulltext table column */
+  int nDoc                       /* Length of zDoc in bytes */
+){
+  const sqlite3_tokenizer_module *pTModule;  /* The tokenizer module */
+  sqlite3_tokenizer *pTokenizer;             /* The specific tokenizer */
+  sqlite3_tokenizer_cursor *pTCursor;        /* Tokenizer cursor */
+  fulltext_vtab *pVtab;                /* The full text index */
+  int nColumn;                         /* Number of columns in the index */
+  int i, j;                            /* Loop counters */
+  int rc;                              /* Return code */
+  unsigned int match, prevMatch;       /* Phrase search bitmasks */
+  const char *zToken;                  /* Next token from the tokenizer */
+  int nToken;                          /* Size of zToken */
+  int iBegin, iEnd, iPos;              /* Offsets of beginning and end */
+
+  /* The following variables keep a circular buffer of the last
+  ** few tokens */
+  unsigned int iRotor = 0;             /* Index of current token */
+  int iRotorBegin[FTS3_ROTOR_SZ];      /* Beginning offset of token */
+  int iRotorLen[FTS3_ROTOR_SZ];        /* Length of token */
+
+  pVtab = cursor_vtab(pCur);
+  nColumn = pVtab->nColumn;
+  pTokenizer = pVtab->pTokenizer;
+  pTModule = pTokenizer->pModule;
+  rc = pTModule->xOpen(pTokenizer, zDoc, nDoc, &pTCursor);
+  if( rc ) return;
+  pTCursor->pTokenizer = pTokenizer;
+
+  prevMatch = 0;
+  while( !pTModule->xNext(pTCursor, &zToken, &nToken, &iBegin, &iEnd, &iPos) ){
+    Fts3Expr *pIter = pCur->pExpr;
+    int iIter = -1;
+    iRotorBegin[iRotor&FTS3_ROTOR_MASK] = iBegin;
+    iRotorLen[iRotor&FTS3_ROTOR_MASK] = iEnd-iBegin;
+    match = 0;
+    for(i=0; i<(FTS3_ROTOR_SZ-1) && fts3NextExprToken(&pIter, &iIter); i++){
+      int nPhrase;                    /* Number of tokens in current phrase */
+      struct PhraseToken *pToken;     /* Current token */
+      int iCol;                       /* Column index */
+
+      if( fts3ExprBeneathNot(pIter) ) continue;
+      nPhrase = pIter->pPhrase->nToken;
+      pToken = &pIter->pPhrase->aToken[iIter];
+      iCol = pIter->pPhrase->iColumn;
+      if( iCol>=0 && iCol<nColumn && iCol!=iColumn ) continue;
+      if( pToken->n>nToken ) continue;
+      if( !pToken->isPrefix && pToken->n<nToken ) continue;
+      assert( pToken->n<=nToken );
+      if( memcmp(pToken->z, zToken, pToken->n) ) continue;
+      if( iIter>0 && (prevMatch & (1<<i))==0 ) continue;
+      match |= 1<<i;
+      if( i==(FTS3_ROTOR_SZ-2) || nPhrase==iIter+1 ){
+        for(j=nPhrase-1; j>=0; j--){
+          int k = (iRotor-j) & FTS3_ROTOR_MASK;
+          snippetAppendMatch(pSnippet, iColumn, i-j, iPos-j,
+                iRotorBegin[k], iRotorLen[k]);
+        }
+      }
     }
+    prevMatch = match<<1;
+    iRotor++;
   }
-
-  fts3SegReaderCursorFree(pSegcsr);
-  pTok->pSegcsr = 0;
-  return rc;
+  pTModule->xClose(pTCursor);  
 }
 
 /*
-** This function counts the total number of docids in the doclist stored
-** in buffer aList[], size nList bytes.
+** Remove entries from the pSnippet structure to account for the NEAR
+** operator. When this is called, pSnippet contains the list of token 
+** offsets produced by treating all NEAR operators as AND operators.
+** This function removes any entries that should not be present after
+** accounting for the NEAR restriction. For example, if the queried
+** document is:
+**
+**     "A B C D E A"
+**
+** and the query is:
+** 
+**     A NEAR/0 E
 **
-** If the isPoslist argument is true, then it is assumed that the doclist
-** contains a position-list following each docid. Otherwise, it is assumed
-** that the doclist is simply a list of docids stored as delta encoded 
-** varints.
-*/
-static int fts3DoclistCountDocids(char *aList, int nList){
-  int nDoc = 0;                   /* Return value */
-  if( aList ){
-    char *aEnd = &aList[nList];   /* Pointer to one byte after EOF */
-    char *p = aList;              /* Cursor */
-    while( p<aEnd ){
-      nDoc++;
-      while( (*p++)&0x80 );     /* Skip docid varint */
-      fts3PoslistCopy(0, &p);   /* Skip over position list */
+** then when this function is called the Snippet contains token offsets
+** 0, 4 and 5. This function removes the "0" entry (because the first A
+** is not near enough to an E).
+**
+** When this function is called, the value pointed to by parameter piLeft is
+** the integer id of the left-most token in the expression tree headed by
+** pExpr. This function increments *piLeft by the total number of tokens
+** in the expression tree headed by pExpr.
+**
+** Return 1 if any trimming occurs.  Return 0 if no trimming is required.
+*/
+static int trimSnippetOffsets(
+  Fts3Expr *pExpr,      /* The search expression */
+  Snippet *pSnippet,    /* The set of snippet offsets to be trimmed */
+  int *piLeft           /* Index of left-most token in pExpr */
+){
+  if( pExpr ){
+    if( trimSnippetOffsets(pExpr->pLeft, pSnippet, piLeft) ){
+      return 1;
+    }
+
+    switch( pExpr->eType ){
+      case FTSQUERY_PHRASE:
+        *piLeft += pExpr->pPhrase->nToken;
+        break;
+      case FTSQUERY_NEAR: {
+        /* The right-hand-side of a NEAR operator is always a phrase. The
+        ** left-hand-side is either a phrase or an expression tree that is 
+        ** itself headed by a NEAR operator. The following initializations
+        ** set local variable iLeft to the token number of the left-most
+        ** token in the right-hand phrase, and iRight to the right most
+        ** token in the same phrase. For example, if we had:
+        **
+        **     <col> MATCH '"abc def" NEAR/2 "ghi jkl"'
+        **
+        ** then iLeft will be set to 2 (token number of ghi) and nToken will
+        ** be set to 4.
+        */
+        Fts3Expr *pLeft = pExpr->pLeft;
+        Fts3Expr *pRight = pExpr->pRight;
+        int iLeft = *piLeft;
+        int nNear = pExpr->nNear;
+        int nToken = pRight->pPhrase->nToken;
+        int jj, ii;
+        if( pLeft->eType==FTSQUERY_NEAR ){
+          pLeft = pLeft->pRight;
+        }
+        assert( pRight->eType==FTSQUERY_PHRASE );
+        assert( pLeft->eType==FTSQUERY_PHRASE );
+        nToken += pLeft->pPhrase->nToken;
+
+        for(ii=0; ii<pSnippet->nMatch; ii++){
+          struct snippetMatch *p = &pSnippet->aMatch[ii];
+          if( p->iTerm==iLeft ){
+            int isOk = 0;
+            /* Snippet ii is an occurence of query term iLeft in the document.
+            ** It occurs at position (p->iToken) of the document. We now
+            ** search for an instance of token (iLeft-1) somewhere in the 
+            ** range (p->iToken - nNear)...(p->iToken + nNear + nToken) within 
+            ** the set of snippetMatch structures. If one is found, proceed. 
+            ** If one cannot be found, then remove snippets ii..(ii+N-1) 
+            ** from the matching snippets, where N is the number of tokens 
+            ** in phrase pRight->pPhrase.
+            */
+            for(jj=0; isOk==0 && jj<pSnippet->nMatch; jj++){
+              struct snippetMatch *p2 = &pSnippet->aMatch[jj];
+              if( p2->iTerm==(iLeft-1) ){
+                if( p2->iToken>=(p->iToken-nNear-1) 
+                 && p2->iToken<(p->iToken+nNear+nToken) 
+                ){
+                  isOk = 1;
+                }
+              }
+            }
+            if( !isOk ){
+              int kk;
+              for(kk=0; kk<pRight->pPhrase->nToken; kk++){
+                pSnippet->aMatch[kk+ii].iTerm = -2;
+              }
+              return 1;
+            }
+          }
+          if( p->iTerm==(iLeft-1) ){
+            int isOk = 0;
+            for(jj=0; isOk==0 && jj<pSnippet->nMatch; jj++){
+              struct snippetMatch *p2 = &pSnippet->aMatch[jj];
+              if( p2->iTerm==iLeft ){
+                if( p2->iToken<=(p->iToken+nNear+1) 
+                 && p2->iToken>(p->iToken-nNear-nToken) 
+                ){
+                  isOk = 1;
+                }
+              }
+            }
+            if( !isOk ){
+              int kk;
+              for(kk=0; kk<pLeft->pPhrase->nToken; kk++){
+                pSnippet->aMatch[ii-kk].iTerm = -2;
+              }
+              return 1;
+            }
+          }
+        }
+        break;
+      }
     }
-  }
 
-  return nDoc;
+    if( trimSnippetOffsets(pExpr->pRight, pSnippet, piLeft) ){
+      return 1;
+    }
+  }
+  return 0;
 }
 
 /*
-** Advance the cursor to the next row in the %_content table that
-** matches the search criteria.  For a MATCH search, this will be
-** the next row that matches. For a full-table scan, this will be
-** simply the next row in the %_content table.  For a docid lookup,
-** this routine simply sets the EOF flag.
-**
-** Return SQLITE_OK if nothing goes wrong.  SQLITE_OK is returned
-** even if we reach end-of-file.  The fts3EofMethod() will be called
-** subsequently to determine whether or not an EOF was hit.
+** Compute all offsets for the current row of the query.  
+** If the offsets have already been computed, this routine is a no-op.
 */
-static int fts3NextMethod(sqlite3_vtab_cursor *pCursor){
-  int rc;
-  Fts3Cursor *pCsr = (Fts3Cursor *)pCursor;
-  if( pCsr->eSearch==FTS3_DOCID_SEARCH || pCsr->eSearch==FTS3_FULLSCAN_SEARCH ){
-    if( SQLITE_ROW!=sqlite3_step(pCsr->pStmt) ){
-      pCsr->isEof = 1;
-      rc = sqlite3_reset(pCsr->pStmt);
-    }else{
-      pCsr->iPrevId = sqlite3_column_int64(pCsr->pStmt, 0);
-      rc = SQLITE_OK;
-    }
+static void snippetAllOffsets(fulltext_cursor *p){
+  int nColumn;
+  int iColumn, i;
+  int iFirst, iLast;
+  int iTerm = 0;
+  fulltext_vtab *pFts = cursor_vtab(p);
+
+  if( p->snippet.nMatch || p->pExpr==0 ){
+    return;
+  }
+  nColumn = pFts->nColumn;
+  iColumn = (p->iCursorType - QUERY_FULLTEXT);
+  if( iColumn<0 || iColumn>=nColumn ){
+    /* Look for matches over all columns of the full-text index */
+    iFirst = 0;
+    iLast = nColumn-1;
   }else{
-    rc = fts3EvalNext((Fts3Cursor *)pCursor);
+    /* Look for matches in the iColumn-th column of the index only */
+    iFirst = iColumn;
+    iLast = iColumn;
+  }
+  for(i=iFirst; i<=iLast; i++){
+    const char *zDoc;
+    int nDoc;
+    zDoc = (const char*)sqlite3_column_text(p->pStmt, i+1);
+    nDoc = sqlite3_column_bytes(p->pStmt, i+1);
+    snippetOffsetsOfColumn(p, &p->snippet, i, zDoc, nDoc);
   }
-  assert( ((Fts3Table *)pCsr->base.pVtab)->pSegments==0 );
-  return rc;
-}
 
-/*
-** The following are copied from sqliteInt.h.
-**
-** Constants for the largest and smallest possible 64-bit signed integers.
-** These macros are designed to work correctly on both 32-bit and 64-bit
-** compilers.
-*/
-#ifndef SQLITE_AMALGAMATION
-# define LARGEST_INT64  (0xffffffff|(((sqlite3_int64)0x7fffffff)<<32))
-# define SMALLEST_INT64 (((sqlite3_int64)-1) - LARGEST_INT64)
-#endif
+  while( trimSnippetOffsets(p->pExpr, &p->snippet, &iTerm) ){
+    iTerm = 0;
+  }
+}
 
 /*
-** If the numeric type of argument pVal is "integer", then return it
-** converted to a 64-bit signed integer. Otherwise, return a copy of
-** the second parameter, iDefault.
-*/
-static sqlite3_int64 fts3DocidRange(sqlite3_value *pVal, i64 iDefault){
-  if( pVal ){
-    int eType = sqlite3_value_numeric_type(pVal);
-    if( eType==SQLITE_INTEGER ){
-      return sqlite3_value_int64(pVal);
+** Convert the information in the aMatch[] array of the snippet
+** into the string zOffset[0..nOffset-1]. This string is used as
+** the return of the SQL offsets() function.
+*/
+static void snippetOffsetText(Snippet *p){
+  int i;
+  int cnt = 0;
+  StringBuffer sb;
+  char zBuf[200];
+  if( p->zOffset ) return;
+  initStringBuffer(&sb);
+  for(i=0; i<p->nMatch; i++){
+    struct snippetMatch *pMatch = &p->aMatch[i];
+    if( pMatch->iTerm>=0 ){
+      /* If snippetMatch.iTerm is less than 0, then the match was 
+      ** discarded as part of processing the NEAR operator (see the 
+      ** trimSnippetOffsetsForNear() function for details). Ignore 
+      ** it in this case
+      */
+      zBuf[0] = ' ';
+      sqlite3_snprintf(sizeof(zBuf)-1, &zBuf[cnt>0], "%d %d %d %d",
+          pMatch->iCol, pMatch->iTerm, pMatch->iStart, pMatch->nByte);
+      append(&sb, zBuf);
+      cnt++;
     }
   }
-  return iDefault;
+  p->zOffset = stringBufferData(&sb);
+  p->nOffset = stringBufferLength(&sb);
 }
 
 /*
-** This is the xFilter interface for the virtual table.  See
-** the virtual table xFilter method documentation for additional
-** information.
-**
-** If idxNum==FTS3_FULLSCAN_SEARCH then do a full table scan against
-** the %_content table.
-**
-** If idxNum==FTS3_DOCID_SEARCH then do a docid lookup for a single entry
-** in the %_content table.
+** zDoc[0..nDoc-1] is phrase of text.  aMatch[0..nMatch-1] are a set
+** of matching words some of which might be in zDoc.  zDoc is column
+** number iCol.
 **
-** If idxNum>=FTS3_FULLTEXT_SEARCH then use the full text index.  The
-** column on the left-hand side of the MATCH operator is column
-** number idxNum-FTS3_FULLTEXT_SEARCH, 0 indexed.  argv[0] is the right-hand
-** side of the MATCH operator.
+** iBreak is suggested spot in zDoc where we could begin or end an
+** excerpt.  Return a value similar to iBreak but possibly adjusted
+** to be a little left or right so that the break point is better.
 */
-static int fts3FilterMethod(
-  sqlite3_vtab_cursor *pCursor,   /* The cursor used for this query */
-  int idxNum,                     /* Strategy index */
-  const char *idxStr,             /* Unused */
-  int nVal,                       /* Number of elements in apVal */
-  sqlite3_value **apVal           /* Arguments for the indexing scheme */
+static int wordBoundary(
+  int iBreak,                   /* The suggested break point */
+  const char *zDoc,             /* Document text */
+  int nDoc,                     /* Number of bytes in zDoc[] */
+  struct snippetMatch *aMatch,  /* Matching words */
+  int nMatch,                   /* Number of entries in aMatch[] */
+  int iCol                      /* The column number for zDoc[] */
 ){
-  int rc = SQLITE_OK;
-  char *zSql;                     /* SQL statement used to access %_content */
-  int eSearch;
-  Fts3Table *p = (Fts3Table *)pCursor->pVtab;
-  Fts3Cursor *pCsr = (Fts3Cursor *)pCursor;
-
-  sqlite3_value *pCons = 0;       /* The MATCH or rowid constraint, if any */
-  sqlite3_value *pLangid = 0;     /* The "langid = ?" constraint, if any */
-  sqlite3_value *pDocidGe = 0;    /* The "docid >= ?" constraint, if any */
-  sqlite3_value *pDocidLe = 0;    /* The "docid <= ?" constraint, if any */
-  int iIdx;
-
-  UNUSED_PARAMETER(idxStr);
-  UNUSED_PARAMETER(nVal);
-
-  eSearch = (idxNum & 0x0000FFFF);
-  assert( eSearch>=0 && eSearch<=(FTS3_FULLTEXT_SEARCH+p->nColumn) );
-  assert( p->pSegments==0 );
-
-  /* Collect arguments into local variables */
-  iIdx = 0;
-  if( eSearch!=FTS3_FULLSCAN_SEARCH ) pCons = apVal[iIdx++];
-  if( idxNum & FTS3_HAVE_LANGID ) pLangid = apVal[iIdx++];
-  if( idxNum & FTS3_HAVE_DOCID_GE ) pDocidGe = apVal[iIdx++];
-  if( idxNum & FTS3_HAVE_DOCID_LE ) pDocidLe = apVal[iIdx++];
-  assert( iIdx==nVal );
-
-  /* In case the cursor has been used before, clear it now. */
-  fts3ClearCursor(pCsr);
-
-  /* Set the lower and upper bounds on docids to return */
-  pCsr->iMinDocid = fts3DocidRange(pDocidGe, SMALLEST_INT64);
-  pCsr->iMaxDocid = fts3DocidRange(pDocidLe, LARGEST_INT64);
-
-  if( idxStr ){
-    pCsr->bDesc = (idxStr[0]=='D');
-  }else{
-    pCsr->bDesc = p->bDescIdx;
+  int i;
+  if( iBreak<=10 ){
+    return 0;
   }
-  pCsr->eSearch = (i16)eSearch;
-
-  if( eSearch!=FTS3_DOCID_SEARCH && eSearch!=FTS3_FULLSCAN_SEARCH ){
-    int iCol = eSearch-FTS3_FULLTEXT_SEARCH;
-    const char *zQuery = (const char *)sqlite3_value_text(pCons);
-
-    if( zQuery==0 && sqlite3_value_type(pCons)!=SQLITE_NULL ){
-      return SQLITE_NOMEM;
+  if( iBreak>=nDoc-10 ){
+    return nDoc;
+  }
+  for(i=0; i<nMatch && aMatch[i].iCol<iCol; i++){}
+  while( i<nMatch && aMatch[i].iStart+aMatch[i].nByte<iBreak ){ i++; }
+  if( i<nMatch ){
+    if( aMatch[i].iStart<iBreak+10 ){
+      return aMatch[i].iStart;
     }
-
-    pCsr->iLangid = 0;
-    if( pLangid ) pCsr->iLangid = sqlite3_value_int(pLangid);
-
-    assert( p->base.zErrMsg==0 );
-    rc = sqlite3Fts3ExprParse(p->pTokenizer, pCsr->iLangid,
-        p->azColumn, p->bFts4, p->nColumn, iCol, zQuery, -1, &pCsr->pExpr, 
-        &p->base.zErrMsg
-    );
-    if( rc!=SQLITE_OK ){
-      return rc;
+    if( i>0 && aMatch[i-1].iStart+aMatch[i-1].nByte>=iBreak ){
+      return aMatch[i-1].iStart;
     }
-
-    rc = fts3EvalStart(pCsr);
-    sqlite3Fts3SegmentsClose(p);
-    if( rc!=SQLITE_OK ) return rc;
-    pCsr->pNextId = pCsr->aDoclist;
-    pCsr->iPrevId = 0;
   }
-
-  /* Compile a SELECT statement for this cursor. For a full-table-scan, the
-  ** statement loops through all rows of the %_content table. For a
-  ** full-text query or docid lookup, the statement retrieves a single
-  ** row by docid.
-  */
-  if( eSearch==FTS3_FULLSCAN_SEARCH ){
-    if( pDocidGe || pDocidLe ){
-      zSql = sqlite3_mprintf(
-          "SELECT %s WHERE rowid BETWEEN %lld AND %lld ORDER BY rowid %s",
-          p->zReadExprlist, pCsr->iMinDocid, pCsr->iMaxDocid,
-          (pCsr->bDesc ? "DESC" : "ASC")
-      );
-    }else{
-      zSql = sqlite3_mprintf("SELECT %s ORDER BY rowid %s", 
-          p->zReadExprlist, (pCsr->bDesc ? "DESC" : "ASC")
-      );
-    }
-    if( zSql ){
-      rc = sqlite3_prepare_v3(p->db,zSql,-1,SQLITE_PREPARE_PERSISTENT,&pCsr->pStmt,0);
-      sqlite3_free(zSql);
-    }else{
-      rc = SQLITE_NOMEM;
+  for(i=1; i<=10; i++){
+    if( safe_isspace(zDoc[iBreak-i]) ){
+      return iBreak - i + 1;
     }
-  }else if( eSearch==FTS3_DOCID_SEARCH ){
-    rc = fts3CursorSeekStmt(pCsr);
-    if( rc==SQLITE_OK ){
-      rc = sqlite3_bind_value(pCsr->pStmt, 1, pCons);
+    if( safe_isspace(zDoc[iBreak+i]) ){
+      return iBreak + i + 1;
     }
   }
-  if( rc!=SQLITE_OK ) return rc;
-
-  return fts3NextMethod(pCursor);
+  return iBreak;
 }
 
-/* 
-** This is the xEof method of the virtual table. SQLite calls this 
-** routine to find out if it has reached the end of a result set.
-*/
-static int fts3EofMethod(sqlite3_vtab_cursor *pCursor){
-  Fts3Cursor *pCsr = (Fts3Cursor*)pCursor;
-  if( pCsr->isEof ){
-    fts3ClearCursor(pCsr);
-    pCsr->isEof = 1;
-  }
-  return pCsr->isEof;
-}
 
-/* 
-** This is the xRowid method. The SQLite core calls this routine to
-** retrieve the rowid for the current row of the result set. fts3
-** exposes %_content.docid as the rowid for the virtual table. The
-** rowid should be written to *pRowid.
+
+/*
+** Allowed values for Snippet.aMatch[].snStatus
 */
-static int fts3RowidMethod(sqlite3_vtab_cursor *pCursor, sqlite_int64 *pRowid){
-  Fts3Cursor *pCsr = (Fts3Cursor *) pCursor;
-  *pRowid = pCsr->iPrevId;
-  return SQLITE_OK;
-}
+#define SNIPPET_IGNORE  0   /* It is ok to omit this match from the snippet */
+#define SNIPPET_DESIRED 1   /* We want to include this match in the snippet */
 
-/* 
-** This is the xColumn method, called by SQLite to request a value from
-** the row that the supplied cursor currently points to.
-**
-** If:
-**
-**   (iCol <  p->nColumn)   -> The value of the iCol'th user column.
-**   (iCol == p->nColumn)   -> Magic column with the same name as the table.
-**   (iCol == p->nColumn+1) -> Docid column
-**   (iCol == p->nColumn+2) -> Langid column
-*/
-static int fts3ColumnMethod(
-  sqlite3_vtab_cursor *pCursor,   /* Cursor to retrieve value from */
-  sqlite3_context *pCtx,          /* Context for sqlite3_result_xxx() calls */
-  int iCol                        /* Index of column to read value from */
+/*
+** Generate the text of a snippet.
+*/
+static void snippetText(
+  fulltext_cursor *pCursor,   /* The cursor we need the snippet for */
+  const char *zStartMark,     /* Markup to appear before each match */
+  const char *zEndMark,       /* Markup to appear after each match */
+  const char *zEllipsis       /* Ellipsis mark */
 ){
-  int rc = SQLITE_OK;             /* Return Code */
-  Fts3Cursor *pCsr = (Fts3Cursor *) pCursor;
-  Fts3Table *p = (Fts3Table *)pCursor->pVtab;
-
-  /* The column value supplied by SQLite must be in range. */
-  assert( iCol>=0 && iCol<=p->nColumn+2 );
-
-  switch( iCol-p->nColumn ){
-    case 0:
-      /* The special 'table-name' column */
-      sqlite3_result_pointer(pCtx, pCsr, "fts3cursor", 0);
-      break;
-
-    case 1:
-      /* The docid column */
-      sqlite3_result_int64(pCtx, pCsr->iPrevId);
-      break;
+  int i, j;
+  struct snippetMatch *aMatch;
+  int nMatch;
+  int nDesired;
+  StringBuffer sb;
+  int tailCol;
+  int tailOffset;
+  int iCol;
+  int nDoc;
+  const char *zDoc;
+  int iStart, iEnd;
+  int tailEllipsis = 0;
+  int iMatch;
+  
 
-    case 2:
-      if( pCsr->pExpr ){
-        sqlite3_result_int64(pCtx, pCsr->iLangid);
+  sqlite3_free(pCursor->snippet.zSnippet);
+  pCursor->snippet.zSnippet = 0;
+  aMatch = pCursor->snippet.aMatch;
+  nMatch = pCursor->snippet.nMatch;
+  initStringBuffer(&sb);
+
+  for(i=0; i<nMatch; i++){
+    aMatch[i].snStatus = SNIPPET_IGNORE;
+  }
+  nDesired = 0;
+  for(i=0; i<FTS3_ROTOR_SZ; i++){
+    for(j=0; j<nMatch; j++){
+      if( aMatch[j].iTerm==i ){
+        aMatch[j].snStatus = SNIPPET_DESIRED;
+        nDesired++;
         break;
-      }else if( p->zLanguageid==0 ){
-        sqlite3_result_int(pCtx, 0);
-        break;
-      }else{
-        iCol = p->nColumn;
-        /* fall-through */
       }
+    }
+  }
 
-    default:
-      /* A user column. Or, if this is a full-table scan, possibly the
-      ** language-id column. Seek the cursor. */
-      rc = fts3CursorSeek(0, pCsr);
-      if( rc==SQLITE_OK && sqlite3_data_count(pCsr->pStmt)-1>iCol ){
-        sqlite3_result_value(pCtx, sqlite3_column_value(pCsr->pStmt, iCol+1));
+  iMatch = 0;
+  tailCol = -1;
+  tailOffset = 0;
+  for(i=0; i<nMatch && nDesired>0; i++){
+    if( aMatch[i].snStatus!=SNIPPET_DESIRED ) continue;
+    nDesired--;
+    iCol = aMatch[i].iCol;
+    zDoc = (const char*)sqlite3_column_text(pCursor->pStmt, iCol+1);
+    nDoc = sqlite3_column_bytes(pCursor->pStmt, iCol+1);
+    iStart = aMatch[i].iStart - 40;
+    iStart = wordBoundary(iStart, zDoc, nDoc, aMatch, nMatch, iCol);
+    if( iStart<=10 ){
+      iStart = 0;
+    }
+    if( iCol==tailCol && iStart<=tailOffset+20 ){
+      iStart = tailOffset;
+    }
+    if( (iCol!=tailCol && tailCol>=0) || iStart!=tailOffset ){
+      trimWhiteSpace(&sb);
+      appendWhiteSpace(&sb);
+      append(&sb, zEllipsis);
+      appendWhiteSpace(&sb);
+    }
+    iEnd = aMatch[i].iStart + aMatch[i].nByte + 40;
+    iEnd = wordBoundary(iEnd, zDoc, nDoc, aMatch, nMatch, iCol);
+    if( iEnd>=nDoc-10 ){
+      iEnd = nDoc;
+      tailEllipsis = 0;
+    }else{
+      tailEllipsis = 1;
+    }
+    while( iMatch<nMatch && aMatch[iMatch].iCol<iCol ){ iMatch++; }
+    while( iStart<iEnd ){
+      while( iMatch<nMatch && aMatch[iMatch].iStart<iStart
+             && aMatch[iMatch].iCol<=iCol ){
+        iMatch++;
+      }
+      if( iMatch<nMatch && aMatch[iMatch].iStart<iEnd
+             && aMatch[iMatch].iCol==iCol ){
+        nappend(&sb, &zDoc[iStart], aMatch[iMatch].iStart - iStart);
+        iStart = aMatch[iMatch].iStart;
+        append(&sb, zStartMark);
+        nappend(&sb, &zDoc[iStart], aMatch[iMatch].nByte);
+        append(&sb, zEndMark);
+        iStart += aMatch[iMatch].nByte;
+        for(j=iMatch+1; j<nMatch; j++){
+          if( aMatch[j].iTerm==aMatch[iMatch].iTerm
+              && aMatch[j].snStatus==SNIPPET_DESIRED ){
+            nDesired--;
+            aMatch[j].snStatus = SNIPPET_IGNORE;
+          }
+        }
+      }else{
+        nappend(&sb, &zDoc[iStart], iEnd - iStart);
+        iStart = iEnd;
       }
-      break;
+    }
+    tailCol = iCol;
+    tailOffset = iEnd;
   }
-
-  assert( ((Fts3Table *)pCsr->base.pVtab)->pSegments==0 );
-  return rc;
+  trimWhiteSpace(&sb);
+  if( tailEllipsis ){
+    appendWhiteSpace(&sb);
+    append(&sb, zEllipsis);
+  }
+  pCursor->snippet.zSnippet = stringBufferData(&sb);
+  pCursor->snippet.nSnippet = stringBufferLength(&sb);
 }
 
-/* 
-** This function is the implementation of the xUpdate callback used by 
-** FTS3 virtual tables. It is invoked by SQLite each time a row is to be
-** inserted, updated or deleted.
-*/
-static int fts3UpdateMethod(
-  sqlite3_vtab *pVtab,            /* Virtual table handle */
-  int nArg,                       /* Size of argument array */
-  sqlite3_value **apVal,          /* Array of arguments */
-  sqlite_int64 *pRowid            /* OUT: The affected (or effected) rowid */
-){
-  return sqlite3Fts3UpdateMethod(pVtab, nArg, apVal, pRowid);
-}
 
 /*
-** Implementation of xSync() method. Flush the contents of the pending-terms
-** hash-table to the database.
+** Close the cursor.  For additional information see the documentation
+** on the xClose method of the virtual table interface.
 */
-static int fts3SyncMethod(sqlite3_vtab *pVtab){
-
-  /* Following an incremental-merge operation, assuming that the input
-  ** segments are not completely consumed (the usual case), they are updated
-  ** in place to remove the entries that have already been merged. This
-  ** involves updating the leaf block that contains the smallest unmerged
-  ** entry and each block (if any) between the leaf and the root node. So
-  ** if the height of the input segment b-trees is N, and input segments
-  ** are merged eight at a time, updating the input segments at the end
-  ** of an incremental-merge requires writing (8*(1+N)) blocks. N is usually
-  ** small - often between 0 and 2. So the overhead of the incremental
-  ** merge is somewhere between 8 and 24 blocks. To avoid this overhead
-  ** dwarfing the actual productive work accomplished, the incremental merge
-  ** is only attempted if it will write at least 64 leaf blocks. Hence
-  ** nMinMerge.
-  **
-  ** Of course, updating the input segments also involves deleting a bunch
-  ** of blocks from the segments table. But this is not considered overhead
-  ** as it would also be required by a crisis-merge that used the same input 
-  ** segments.
-  */
-  const u32 nMinMerge = 64;       /* Minimum amount of incr-merge work to do */
+static int fulltextClose(sqlite3_vtab_cursor *pCursor){
+  fulltext_cursor *c = (fulltext_cursor *) pCursor;
+  FTSTRACE(("FTS3 Close %p\n", c));
+  sqlite3_finalize(c->pStmt);
+  sqlite3Fts3ExprFree(c->pExpr);
+  snippetClear(&c->snippet);
+  if( c->result.nData!=0 ){
+    dlrDestroy(&c->reader);
+  }
+  dataBufferDestroy(&c->result);
+  sqlite3_free(c);
+  return SQLITE_OK;
+}
 
-  Fts3Table *p = (Fts3Table*)pVtab;
+static int fulltextNext(sqlite3_vtab_cursor *pCursor){
+  fulltext_cursor *c = (fulltext_cursor *) pCursor;
   int rc;
-  i64 iLastRowid = sqlite3_last_insert_rowid(p->db);
 
-  rc = sqlite3Fts3PendingTermsFlush(p);
-  if( rc==SQLITE_OK 
-   && p->nLeafAdd>(nMinMerge/16) 
-   && p->nAutoincrmerge && p->nAutoincrmerge!=0xff
-  ){
-    int mxLevel = 0;              /* Maximum relative level value in db */
-    int A;                        /* Incr-merge parameter A */
+  FTSTRACE(("FTS3 Next %p\n", pCursor));
+  snippetClear(&c->snippet);
+  if( c->iCursorType < QUERY_FULLTEXT ){
+    /* TODO(shess) Handle SQLITE_SCHEMA AND SQLITE_BUSY. */
+    rc = sqlite3_step(c->pStmt);
+    switch( rc ){
+      case SQLITE_ROW:
+        c->eof = 0;
+        return SQLITE_OK;
+      case SQLITE_DONE:
+        c->eof = 1;
+        return SQLITE_OK;
+      default:
+        c->eof = 1;
+        return rc;
+    }
+  } else {  /* full-text query */
+    rc = sqlite3_reset(c->pStmt);
+    if( rc!=SQLITE_OK ) return rc;
 
-    rc = sqlite3Fts3MaxLevel(p, &mxLevel);
-    assert( rc==SQLITE_OK || mxLevel==0 );
-    A = p->nLeafAdd * mxLevel;
-    A += (A/2);
-    if( A>(int)nMinMerge ) rc = sqlite3Fts3Incrmerge(p, A, p->nAutoincrmerge);
+    if( c->result.nData==0 || dlrAtEnd(&c->reader) ){
+      c->eof = 1;
+      return SQLITE_OK;
+    }
+    rc = sqlite3_bind_int64(c->pStmt, 1, dlrDocid(&c->reader));
+    dlrStep(&c->reader);
+    if( rc!=SQLITE_OK ) return rc;
+    /* TODO(shess) Handle SQLITE_SCHEMA AND SQLITE_BUSY. */
+    rc = sqlite3_step(c->pStmt);
+    if( rc==SQLITE_ROW ){   /* the case we expect */
+      c->eof = 0;
+      return SQLITE_OK;
+    }
+    /* an error occurred; abort */
+    return rc==SQLITE_DONE ? SQLITE_ERROR : rc;
   }
-  sqlite3Fts3SegmentsClose(p);
-  sqlite3_set_last_insert_rowid(p->db, iLastRowid);
-  return rc;
 }
 
-/*
-** If it is currently unknown whether or not the FTS table has an %_stat
-** table (if p->bHasStat==2), attempt to determine this (set p->bHasStat
-** to 0 or 1). Return SQLITE_OK if successful, or an SQLite error code
-** if an error occurs.
+
+/* TODO(shess) If we pushed LeafReader to the top of the file, or to
+** another file, term_select() could be pushed above
+** docListOfTerm().
+*/
+static int termSelect(fulltext_vtab *v, int iColumn,
+                      const char *pTerm, int nTerm, int isPrefix,
+                      DocListType iType, DataBuffer *out);
+
+/* 
+** Return a DocList corresponding to the phrase *pPhrase.
+**
+** The resulting DL_DOCIDS doclist is stored in pResult, which is
+** overwritten.
 */
-static int fts3SetHasStat(Fts3Table *p){
+static int docListOfPhrase(
+  fulltext_vtab *pTab,   /* The full text index */
+  Fts3Phrase *pPhrase,   /* Phrase to return a doclist corresponding to */
+  DocListType eListType, /* Either DL_DOCIDS or DL_POSITIONS */
+  DataBuffer *pResult    /* Write the result here */
+){
+  int ii;
   int rc = SQLITE_OK;
-  if( p->bHasStat==2 ){
-    char *zTbl = sqlite3_mprintf("%s_stat", p->zName);
-    if( zTbl ){
-      int res = sqlite3_table_column_metadata(p->db, p->zDb, zTbl, 0,0,0,0,0,0);
-      sqlite3_free(zTbl);
-      p->bHasStat = (res==SQLITE_OK);
-    }else{
-      rc = SQLITE_NOMEM;
-    }
+  int iCol = pPhrase->iColumn;
+  DocListType eType = eListType;
+  assert( eType==DL_POSITIONS || eType==DL_DOCIDS );
+  if( pPhrase->nToken>1 ){
+    eType = DL_POSITIONS;
   }
-  return rc;
-}
 
-/*
-** Implementation of xBegin() method. 
-*/
-static int fts3BeginMethod(sqlite3_vtab *pVtab){
-  Fts3Table *p = (Fts3Table*)pVtab;
-  UNUSED_PARAMETER(pVtab);
-  assert( p->pSegments==0 );
-  assert( p->nPendingData==0 );
-  assert( p->inTransaction!=1 );
-  TESTONLY( p->inTransaction = 1 );
-  TESTONLY( p->mxSavepoint = -1; );
-  p->nLeafAdd = 0;
-  return fts3SetHasStat(p);
-}
+  /* This code should never be called with buffered updates. */
+  assert( pTab->nPendingData<0 );
+
+  for(ii=0; rc==SQLITE_OK && ii<pPhrase->nToken; ii++){
+    DataBuffer tmp;
+    struct PhraseToken *p = &pPhrase->aToken[ii];
+    rc = termSelect(pTab, iCol, p->z, p->n, p->isPrefix, eType, &tmp);
+    if( rc==SQLITE_OK ){
+      if( ii==0 ){
+        *pResult = tmp;
+      }else{
+        DataBuffer res = *pResult;
+        dataBufferInit(pResult, 0);
+        if( ii==(pPhrase->nToken-1) ){
+          eType = eListType;
+        }
+        docListPhraseMerge(
+          res.pData, res.nData, tmp.pData, tmp.nData, 0, 0, eType, pResult
+        );
+        dataBufferDestroy(&res);
+        dataBufferDestroy(&tmp);
+      }
+    }
+  }
 
-/*
-** Implementation of xCommit() method. This is a no-op. The contents of
-** the pending-terms hash-table have already been flushed into the database
-** by fts3SyncMethod().
-*/
-static int fts3CommitMethod(sqlite3_vtab *pVtab){
-  TESTONLY( Fts3Table *p = (Fts3Table*)pVtab );
-  UNUSED_PARAMETER(pVtab);
-  assert( p->nPendingData==0 );
-  assert( p->inTransaction!=0 );
-  assert( p->pSegments==0 );
-  TESTONLY( p->inTransaction = 0 );
-  TESTONLY( p->mxSavepoint = -1; );
-  return SQLITE_OK;
+  return rc;
 }
 
 /*
-** Implementation of xRollback(). Discard the contents of the pending-terms
-** hash-table. Any changes made to the database are reverted by SQLite.
+** Evaluate the full-text expression pExpr against fts3 table pTab. Write
+** the results into pRes.
 */
-static int fts3RollbackMethod(sqlite3_vtab *pVtab){
-  Fts3Table *p = (Fts3Table*)pVtab;
-  sqlite3Fts3PendingTermsClear(p);
-  assert( p->inTransaction!=0 );
-  TESTONLY( p->inTransaction = 0 );
-  TESTONLY( p->mxSavepoint = -1; );
-  return SQLITE_OK;
-}
+static int evalFts3Expr(
+  fulltext_vtab *pTab,           /* Fts3 Virtual table object */
+  Fts3Expr *pExpr,               /* Parsed fts3 expression */
+  DataBuffer *pRes               /* OUT: Write results of the expression here */
+){
+  int rc = SQLITE_OK;
 
-/*
-** When called, *ppPoslist must point to the byte immediately following the
-** end of a position-list. i.e. ( (*ppPoslist)[-1]==POS_END ). This function
-** moves *ppPoslist so that it instead points to the first byte of the
-** same position list.
-*/
-static void fts3ReversePoslist(char *pStart, char **ppPoslist){
-  char *p = &(*ppPoslist)[-2];
-  char c = 0;
-
-  /* Skip backwards passed any trailing 0x00 bytes added by NearTrim() */
-  while( p>pStart && (c=*p--)==0 );
-
-  /* Search backwards for a varint with value zero (the end of the previous 
-  ** poslist). This is an 0x00 byte preceded by some byte that does not
-  ** have the 0x80 bit set.  */
-  while( p>pStart && (*p & 0x80) | c ){ 
-    c = *p--; 
-  }
-  assert( p==pStart || c==0 );
-
-  /* At this point p points to that preceding byte without the 0x80 bit
-  ** set. So to find the start of the poslist, skip forward 2 bytes then
-  ** over a varint. 
-  **
-  ** Normally. The other case is that p==pStart and the poslist to return
-  ** is the first in the doclist. In this case do not skip forward 2 bytes.
-  ** The second part of the if condition (c==0 && *ppPoslist>&p[2])
-  ** is required for cases where the first byte of a doclist and the
-  ** doclist is empty. For example, if the first docid is 10, a doclist
-  ** that begins with:
-  **
-  **   0x0A 0x00 <next docid delta varint>
+  /* Initialize the output buffer. If this is an empty query (pExpr==0), 
+  ** this is all that needs to be done. Empty queries produce empty 
+  ** result sets.
   */
-  if( p>pStart || (c==0 && *ppPoslist>&p[2]) ){ p = &p[2]; }
-  while( *p++&0x80 );
-  *ppPoslist = p;
-}
+  dataBufferInit(pRes, 0);
 
-/*
-** Helper function used by the implementation of the overloaded snippet(),
-** offsets() and optimize() SQL functions.
-**
-** If the value passed as the third argument is a blob of size
-** sizeof(Fts3Cursor*), then the blob contents are copied to the 
-** output variable *ppCsr and SQLITE_OK is returned. Otherwise, an error
-** message is written to context pContext and SQLITE_ERROR returned. The
-** string passed via zFunc is used as part of the error message.
-*/
-static int fts3FunctionArg(
-  sqlite3_context *pContext,      /* SQL function call context */
-  const char *zFunc,              /* Function name */
-  sqlite3_value *pVal,            /* argv[0] passed to function */
-  Fts3Cursor **ppCsr              /* OUT: Store cursor handle here */
-){
-  int rc;
-  *ppCsr = (Fts3Cursor*)sqlite3_value_pointer(pVal, "fts3cursor");
-  if( (*ppCsr)!=0 ){
-    rc = SQLITE_OK;
-  }else{
-    char *zErr = sqlite3_mprintf("illegal first argument to %s", zFunc);
-    sqlite3_result_error(pContext, zErr, -1);
-    sqlite3_free(zErr);
-    rc = SQLITE_ERROR;
+  if( pExpr ){
+    if( pExpr->eType==FTSQUERY_PHRASE ){
+      DocListType eType = DL_DOCIDS;
+      if( pExpr->pParent && pExpr->pParent->eType==FTSQUERY_NEAR ){
+        eType = DL_POSITIONS;
+      }
+      rc = docListOfPhrase(pTab, pExpr->pPhrase, eType, pRes);
+    }else{
+      DataBuffer lhs;
+      DataBuffer rhs;
+
+      dataBufferInit(&rhs, 0);
+      if( SQLITE_OK==(rc = evalFts3Expr(pTab, pExpr->pLeft, &lhs)) 
+       && SQLITE_OK==(rc = evalFts3Expr(pTab, pExpr->pRight, &rhs)) 
+      ){
+        switch( pExpr->eType ){
+          case FTSQUERY_NEAR: {
+            int nToken;
+            Fts3Expr *pLeft;
+            DocListType eType = DL_DOCIDS;
+            if( pExpr->pParent && pExpr->pParent->eType==FTSQUERY_NEAR ){
+              eType = DL_POSITIONS;
+            }
+            pLeft = pExpr->pLeft;
+            while( pLeft->eType==FTSQUERY_NEAR ){ 
+              pLeft=pLeft->pRight;
+            }
+            assert( pExpr->pRight->eType==FTSQUERY_PHRASE );
+            assert( pLeft->eType==FTSQUERY_PHRASE );
+            nToken = pLeft->pPhrase->nToken + pExpr->pRight->pPhrase->nToken;
+            docListPhraseMerge(lhs.pData, lhs.nData, rhs.pData, rhs.nData, 
+                pExpr->nNear+1, nToken, eType, pRes
+            );
+            break;
+          }
+          case FTSQUERY_NOT: {
+            docListExceptMerge(lhs.pData, lhs.nData, rhs.pData, rhs.nData,pRes);
+            break;
+          }
+          case FTSQUERY_AND: {
+            docListAndMerge(lhs.pData, lhs.nData, rhs.pData, rhs.nData, pRes);
+            break;
+          }
+          case FTSQUERY_OR: {
+            docListOrMerge(lhs.pData, lhs.nData, rhs.pData, rhs.nData, pRes);
+            break;
+          }
+        }
+      }
+      dataBufferDestroy(&lhs);
+      dataBufferDestroy(&rhs);
+    }
   }
+
   return rc;
 }
 
-/*
-** Implementation of the snippet() function for FTS3
-*/
-static void fts3SnippetFunc(
-  sqlite3_context *pContext,      /* SQLite function call context */
-  int nVal,                       /* Size of apVal[] array */
-  sqlite3_value **apVal           /* Array of arguments */
+/* TODO(shess) Refactor the code to remove this forward decl. */
+static int flushPendingTerms(fulltext_vtab *v);
+
+/* Perform a full-text query using the search expression in
+** zInput[0..nInput-1].  Return a list of matching documents
+** in pResult.
+**
+** Queries must match column iColumn.  Or if iColumn>=nColumn
+** they are allowed to match against any column.
+*/
+static int fulltextQuery(
+  fulltext_vtab *v,      /* The full text index */
+  int iColumn,           /* Match against this column by default */
+  const char *zInput,    /* The query string */
+  int nInput,            /* Number of bytes in zInput[] */
+  DataBuffer *pResult,   /* Write the result doclist here */
+  Fts3Expr **ppExpr        /* Put parsed query string here */
 ){
-  Fts3Cursor *pCsr;               /* Cursor handle passed through apVal[0] */
-  const char *zStart = "<b>";
-  const char *zEnd = "</b>";
-  const char *zEllipsis = "<b>...</b>";
-  int iCol = -1;
-  int nToken = 15;                /* Default number of tokens in snippet */
-
-  /* There must be at least one argument passed to this function (otherwise
-  ** the non-overloaded version would have been called instead of this one).
-  */
-  assert( nVal>=1 );
-
-  if( nVal>6 ){
-    sqlite3_result_error(pContext, 
-        "wrong number of arguments to function snippet()", -1);
-    return;
+  int rc;
+
+  /* TODO(shess) Instead of flushing pendingTerms, we could query for
+  ** the relevant term and merge the doclist into what we receive from
+  ** the database.  Wait and see if this is a common issue, first.
+  **
+  ** A good reason not to flush is to not generate update-related
+  ** error codes from here.
+  */
+
+  /* Flush any buffered updates before executing the query. */
+  rc = flushPendingTerms(v);
+  if( rc!=SQLITE_OK ){
+    return rc;
   }
-  if( fts3FunctionArg(pContext, "snippet", apVal[0], &pCsr) ) return;
 
-  switch( nVal ){
-    case 6: nToken = sqlite3_value_int(apVal[5]);
-    case 5: iCol = sqlite3_value_int(apVal[4]);
-    case 4: zEllipsis = (const char*)sqlite3_value_text(apVal[3]);
-    case 3: zEnd = (const char*)sqlite3_value_text(apVal[2]);
-    case 2: zStart = (const char*)sqlite3_value_text(apVal[1]);
-  }
-  if( !zEllipsis || !zEnd || !zStart ){
-    sqlite3_result_error_nomem(pContext);
-  }else if( nToken==0 ){
-    sqlite3_result_text(pContext, "", -1, SQLITE_STATIC);
-  }else if( SQLITE_OK==fts3CursorSeek(pContext, pCsr) ){
-    sqlite3Fts3Snippet(pContext, pCsr, zStart, zEnd, zEllipsis, iCol, nToken);
+  /* Parse the query passed to the MATCH operator. */
+  rc = sqlite3Fts3ExprParse(v->pTokenizer, 
+      v->azColumn, v->nColumn, iColumn, zInput, nInput, ppExpr
+  );
+  if( rc!=SQLITE_OK ){
+    assert( 0==(*ppExpr) );
+    return rc;
   }
+
+  return evalFts3Expr(v, *ppExpr, pResult);
 }
 
 /*
-** Implementation of the offsets() function for FTS3
+** This is the xFilter interface for the virtual table.  See
+** the virtual table xFilter method documentation for additional
+** information.
+**
+** If idxNum==QUERY_GENERIC then do a full table scan against
+** the %_content table.
+**
+** If idxNum==QUERY_DOCID then do a docid lookup for a single entry
+** in the %_content table.
+**
+** If idxNum>=QUERY_FULLTEXT then use the full text index.  The
+** column on the left-hand side of the MATCH operator is column
+** number idxNum-QUERY_FULLTEXT, 0 indexed.  argv[0] is the right-hand
+** side of the MATCH operator.
 */
-static void fts3OffsetsFunc(
-  sqlite3_context *pContext,      /* SQLite function call context */
-  int nVal,                       /* Size of argument array */
-  sqlite3_value **apVal           /* Array of arguments */
+/* TODO(shess) Upgrade the cursor initialization and destruction to
+** account for fulltextFilter() being called multiple times on the
+** same cursor.  The current solution is very fragile.  Apply fix to
+** fts3 as appropriate.
+*/
+static int fulltextFilter(
+  sqlite3_vtab_cursor *pCursor,     /* The cursor used for this query */
+  int idxNum, const char *idxStr,   /* Which indexing scheme to use */
+  int argc, sqlite3_value **argv    /* Arguments for the indexing scheme */
 ){
-  Fts3Cursor *pCsr;               /* Cursor handle passed through apVal[0] */
+  fulltext_cursor *c = (fulltext_cursor *) pCursor;
+  fulltext_vtab *v = cursor_vtab(c);
+  int rc;
 
-  UNUSED_PARAMETER(nVal);
+  FTSTRACE(("FTS3 Filter %p\n",pCursor));
 
-  assert( nVal==1 );
-  if( fts3FunctionArg(pContext, "offsets", apVal[0], &pCsr) ) return;
-  assert( pCsr );
-  if( SQLITE_OK==fts3CursorSeek(pContext, pCsr) ){
-    sqlite3Fts3Offsets(pContext, pCsr);
+  /* If the cursor has a statement that was not prepared according to
+  ** idxNum, clear it.  I believe all calls to fulltextFilter with a
+  ** given cursor will have the same idxNum , but in this case it's
+  ** easy to be safe.
+  */
+  if( c->pStmt && c->iCursorType!=idxNum ){
+    sqlite3_finalize(c->pStmt);
+    c->pStmt = NULL;
   }
-}
 
-/* 
-** Implementation of the special optimize() function for FTS3. This 
-** function merges all segments in the database to a single segment.
-** Example usage is:
-**
-**   SELECT optimize(t) FROM t LIMIT 1;
-**
-** where 't' is the name of an FTS3 table.
-*/
-static void fts3OptimizeFunc(
-  sqlite3_context *pContext,      /* SQLite function call context */
-  int nVal,                       /* Size of argument array */
-  sqlite3_value **apVal           /* Array of arguments */
-){
-  int rc;                         /* Return code */
-  Fts3Table *p;                   /* Virtual table handle */
-  Fts3Cursor *pCursor;            /* Cursor handle passed through apVal[0] */
-
-  UNUSED_PARAMETER(nVal);
-
-  assert( nVal==1 );
-  if( fts3FunctionArg(pContext, "optimize", apVal[0], &pCursor) ) return;
-  p = (Fts3Table *)pCursor->base.pVtab;
-  assert( p );
-
-  rc = sqlite3Fts3Optimize(p);
-
-  switch( rc ){
-    case SQLITE_OK:
-      sqlite3_result_text(pContext, "Index optimized", -1, SQLITE_STATIC);
-      break;
-    case SQLITE_DONE:
-      sqlite3_result_text(pContext, "Index already optimal", -1, SQLITE_STATIC);
+  /* Get a fresh statement appropriate to idxNum. */
+  /* TODO(shess): Add a prepared-statement cache in the vt structure.
+  ** The cache must handle multiple open cursors.  Easier to cache the
+  ** statement variants at the vt to reduce malloc/realloc/free here.
+  ** Or we could have a StringBuffer variant which allowed stack
+  ** construction for small values.
+  */
+  if( !c->pStmt ){
+    StringBuffer sb;
+    initStringBuffer(&sb);
+    append(&sb, "SELECT docid, ");
+    appendList(&sb, v->nColumn, v->azContentColumn);
+    append(&sb, " FROM %_content");
+    if( idxNum!=QUERY_GENERIC ) append(&sb, " WHERE docid = ?");
+    rc = sql_prepare(v->db, v->zDb, v->zName, &c->pStmt,
+                     stringBufferData(&sb));
+    stringBufferDestroy(&sb);
+    if( rc!=SQLITE_OK ) return rc;
+    c->iCursorType = idxNum;
+  }else{
+    sqlite3_reset(c->pStmt);
+    assert( c->iCursorType==idxNum );
+  }
+
+  switch( idxNum ){
+    case QUERY_GENERIC:
       break;
-    default:
-      sqlite3_result_error_code(pContext, rc);
+
+    case QUERY_DOCID:
+      rc = sqlite3_bind_int64(c->pStmt, 1, sqlite3_value_int64(argv[0]));
+      if( rc!=SQLITE_OK ) return rc;
       break;
-  }
-}
 
-/*
-** Implementation of the matchinfo() function for FTS3
-*/
-static void fts3MatchinfoFunc(
-  sqlite3_context *pContext,      /* SQLite function call context */
-  int nVal,                       /* Size of argument array */
-  sqlite3_value **apVal           /* Array of arguments */
-){
-  Fts3Cursor *pCsr;               /* Cursor handle passed through apVal[0] */
-  assert( nVal==1 || nVal==2 );
-  if( SQLITE_OK==fts3FunctionArg(pContext, "matchinfo", apVal[0], &pCsr) ){
-    const char *zArg = 0;
-    if( nVal>1 ){
-      zArg = (const char *)sqlite3_value_text(apVal[1]);
+    default:   /* full-text search */
+    {
+      int iCol = idxNum-QUERY_FULLTEXT;
+      const char *zQuery = (const char *)sqlite3_value_text(argv[0]);
+      assert( idxNum<=QUERY_FULLTEXT+v->nColumn);
+      assert( argc==1 );
+      if( c->result.nData!=0 ){
+        /* This case happens if the same cursor is used repeatedly. */
+        dlrDestroy(&c->reader);
+        dataBufferReset(&c->result);
+      }else{
+        dataBufferInit(&c->result, 0);
+      }
+      rc = fulltextQuery(v, iCol, zQuery, -1, &c->result, &c->pExpr);
+      if( rc!=SQLITE_OK ) return rc;
+      if( c->result.nData!=0 ){
+        dlrInit(&c->reader, DL_DOCIDS, c->result.pData, c->result.nData);
+      }
+      break;
     }
-    sqlite3Fts3Matchinfo(pContext, pCsr, zArg);
   }
+
+  return fulltextNext(pCursor);
 }
 
-/*
-** This routine implements the xFindFunction method for the FTS3
-** virtual table.
-*/
-static int fts3FindFunctionMethod(
-  sqlite3_vtab *pVtab,            /* Virtual table handle */
-  int nArg,                       /* Number of SQL function arguments */
-  const char *zName,              /* Name of SQL function */
-  void (**pxFunc)(sqlite3_context*,int,sqlite3_value**), /* OUT: Result */
-  void **ppArg                    /* Unused */
-){
-  struct Overloaded {
-    const char *zName;
-    void (*xFunc)(sqlite3_context*,int,sqlite3_value**);
-  } aOverload[] = {
-    { "snippet", fts3SnippetFunc },
-    { "offsets", fts3OffsetsFunc },
-    { "optimize", fts3OptimizeFunc },
-    { "matchinfo", fts3MatchinfoFunc },
-  };
-  int i;                          /* Iterator variable */
-
-  UNUSED_PARAMETER(pVtab);
-  UNUSED_PARAMETER(nArg);
-  UNUSED_PARAMETER(ppArg);
-
-  for(i=0; i<SizeofArray(aOverload); i++){
-    if( strcmp(zName, aOverload[i].zName)==0 ){
-      *pxFunc = aOverload[i].xFunc;
-      return 1;
-    }
+/* This is the xEof method of the virtual table.  The SQLite core
+** calls this routine to find out if it has reached the end of
+** a query's results set.
+*/
+static int fulltextEof(sqlite3_vtab_cursor *pCursor){
+  fulltext_cursor *c = (fulltext_cursor *) pCursor;
+  return c->eof;
+}
+
+/* This is the xColumn method of the virtual table.  The SQLite
+** core calls this method during a query when it needs the value
+** of a column from the virtual table.  This method needs to use
+** one of the sqlite3_result_*() routines to store the requested
+** value back in the pContext.
+*/
+static int fulltextColumn(sqlite3_vtab_cursor *pCursor,
+                          sqlite3_context *pContext, int idxCol){
+  fulltext_cursor *c = (fulltext_cursor *) pCursor;
+  fulltext_vtab *v = cursor_vtab(c);
+
+  if( idxCol<v->nColumn ){
+    sqlite3_value *pVal = sqlite3_column_value(c->pStmt, idxCol+1);
+    sqlite3_result_value(pContext, pVal);
+  }else if( idxCol==v->nColumn ){
+    /* The extra column whose name is the same as the table.
+    ** Return a blob which is a pointer to the cursor
+    */
+    sqlite3_result_blob(pContext, &c, sizeof(c), SQLITE_TRANSIENT);
+  }else if( idxCol==v->nColumn+1 ){
+    /* The docid column, which is an alias for rowid. */
+    sqlite3_value *pVal = sqlite3_column_value(c->pStmt, 0);
+    sqlite3_result_value(pContext, pVal);
   }
-
-  /* No function of the specified name was found. Return 0. */
-  return 0;
+  return SQLITE_OK;
 }
 
-/*
-** Implementation of FTS3 xRename method. Rename an fts3 table.
+/* This is the xRowid method.  The SQLite core calls this routine to
+** retrieve the rowid for the current row of the result set.  fts3
+** exposes %_content.docid as the rowid for the virtual table.  The
+** rowid should be written to *pRowid.
 */
-static int fts3RenameMethod(
-  sqlite3_vtab *pVtab,            /* Virtual table handle */
-  const char *zName               /* New name of table */
-){
-  Fts3Table *p = (Fts3Table *)pVtab;
-  sqlite3 *db = p->db;            /* Database connection */
-  int rc;                         /* Return Code */
-
-  /* At this point it must be known if the %_stat table exists or not.
-  ** So bHasStat may not be 2.  */
-  rc = fts3SetHasStat(p);
-  
-  /* As it happens, the pending terms table is always empty here. This is
-  ** because an "ALTER TABLE RENAME TABLE" statement inside a transaction 
-  ** always opens a savepoint transaction. And the xSavepoint() method 
-  ** flushes the pending terms table. But leave the (no-op) call to
-  ** PendingTermsFlush() in in case that changes.
-  */
-  assert( p->nPendingData==0 );
-  if( rc==SQLITE_OK ){
-    rc = sqlite3Fts3PendingTermsFlush(p);
-  }
-
-  if( p->zContentTbl==0 ){
-    fts3DbExec(&rc, db,
-      "ALTER TABLE %Q.'%q_content'  RENAME TO '%q_content';",
-      p->zDb, p->zName, zName
-    );
-  }
+static int fulltextRowid(sqlite3_vtab_cursor *pCursor, sqlite_int64 *pRowid){
+  fulltext_cursor *c = (fulltext_cursor *) pCursor;
 
-  if( p->bHasDocsize ){
-    fts3DbExec(&rc, db,
-      "ALTER TABLE %Q.'%q_docsize'  RENAME TO '%q_docsize';",
-      p->zDb, p->zName, zName
-    );
-  }
-  if( p->bHasStat ){
-    fts3DbExec(&rc, db,
-      "ALTER TABLE %Q.'%q_stat'  RENAME TO '%q_stat';",
-      p->zDb, p->zName, zName
-    );
-  }
-  fts3DbExec(&rc, db,
-    "ALTER TABLE %Q.'%q_segments' RENAME TO '%q_segments';",
-    p->zDb, p->zName, zName
-  );
-  fts3DbExec(&rc, db,
-    "ALTER TABLE %Q.'%q_segdir'   RENAME TO '%q_segdir';",
-    p->zDb, p->zName, zName
-  );
-  return rc;
+  *pRowid = sqlite3_column_int64(c->pStmt, 0);
+  return SQLITE_OK;
 }
 
-/*
-** The xSavepoint() method.
-**
-** Flush the contents of the pending-terms table to disk.
-*/
-static int fts3SavepointMethod(sqlite3_vtab *pVtab, int iSavepoint){
-  int rc = SQLITE_OK;
-  UNUSED_PARAMETER(iSavepoint);
-  assert( ((Fts3Table *)pVtab)->inTransaction );
-  assert( ((Fts3Table *)pVtab)->mxSavepoint < iSavepoint );
-  TESTONLY( ((Fts3Table *)pVtab)->mxSavepoint = iSavepoint );
-  if( ((Fts3Table *)pVtab)->bIgnoreSavepoint==0 ){
-    rc = fts3SyncMethod(pVtab);
+/* Add all terms in [zText] to pendingTerms table.  If [iColumn] > 0,
+** we also store positions and offsets in the hash table using that
+** column number.
+*/
+static int buildTerms(fulltext_vtab *v, sqlite_int64 iDocid,
+                      const char *zText, int iColumn){
+  sqlite3_tokenizer *pTokenizer = v->pTokenizer;
+  sqlite3_tokenizer_cursor *pCursor;
+  const char *pToken;
+  int nTokenBytes;
+  int iStartOffset, iEndOffset, iPosition;
+  int rc;
+
+  rc = pTokenizer->pModule->xOpen(pTokenizer, zText, -1, &pCursor);
+  if( rc!=SQLITE_OK ) return rc;
+
+  pCursor->pTokenizer = pTokenizer;
+  while( SQLITE_OK==(rc=pTokenizer->pModule->xNext(pCursor,
+                                                   &pToken, &nTokenBytes,
+                                                   &iStartOffset, &iEndOffset,
+                                                   &iPosition)) ){
+    DLCollector *p;
+    int nData;                   /* Size of doclist before our update. */
+
+    /* Positions can't be negative; we use -1 as a terminator
+     * internally.  Token can't be NULL or empty. */
+    if( iPosition<0 || pToken == NULL || nTokenBytes == 0 ){
+      rc = SQLITE_ERROR;
+      break;
+    }
+
+    p = fts3HashFind(&v->pendingTerms, pToken, nTokenBytes);
+    if( p==NULL ){
+      nData = 0;
+      p = dlcNew(iDocid, DL_DEFAULT);
+      fts3HashInsert(&v->pendingTerms, pToken, nTokenBytes, p);
+
+      /* Overhead for our hash table entry, the key, and the value. */
+      v->nPendingData += sizeof(struct fts3HashElem)+sizeof(*p)+nTokenBytes;
+    }else{
+      nData = p->b.nData;
+      if( p->dlw.iPrevDocid!=iDocid ) dlcNext(p, iDocid);
+    }
+    if( iColumn>=0 ){
+      dlcAddPos(p, iColumn, iPosition, iStartOffset, iEndOffset);
+    }
+
+    /* Accumulate data added by dlcNew or dlcNext, and dlcAddPos. */
+    v->nPendingData += p->b.nData-nData;
   }
+
+  /* TODO(shess) Check return?  Should this be able to cause errors at
+  ** this point?  Actually, same question about sqlite3_finalize(),
+  ** though one could argue that failure there means that the data is
+  ** not durable.  *ponder*
+  */
+  pTokenizer->pModule->xClose(pCursor);
+  if( SQLITE_DONE == rc ) return SQLITE_OK;
   return rc;
 }
 
-/*
-** The xRelease() method.
-**
-** This is a no-op.
-*/
-static int fts3ReleaseMethod(sqlite3_vtab *pVtab, int iSavepoint){
-  TESTONLY( Fts3Table *p = (Fts3Table*)pVtab );
-  UNUSED_PARAMETER(iSavepoint);
-  UNUSED_PARAMETER(pVtab);
-  assert( p->inTransaction );
-  assert( p->mxSavepoint >= iSavepoint );
-  TESTONLY( p->mxSavepoint = iSavepoint-1 );
+/* Add doclists for all terms in [pValues] to pendingTerms table. */
+static int insertTerms(fulltext_vtab *v, sqlite_int64 iDocid,
+                       sqlite3_value **pValues){
+  int i;
+  for(i = 0; i < v->nColumn ; ++i){
+    char *zText = (char*)sqlite3_value_text(pValues[i]);
+    int rc = buildTerms(v, iDocid, zText, i);
+    if( rc!=SQLITE_OK ) return rc;
+  }
   return SQLITE_OK;
 }
 
-/*
-** The xRollbackTo() method.
-**
-** Discard the contents of the pending terms table.
+/* Add empty doclists for all terms in the given row's content to
+** pendingTerms.
 */
-static int fts3RollbackToMethod(sqlite3_vtab *pVtab, int iSavepoint){
-  Fts3Table *p = (Fts3Table*)pVtab;
-  UNUSED_PARAMETER(iSavepoint);
-  assert( p->inTransaction );
-  assert( p->mxSavepoint >= iSavepoint );
-  TESTONLY( p->mxSavepoint = iSavepoint );
-  sqlite3Fts3PendingTermsClear(p);
+static int deleteTerms(fulltext_vtab *v, sqlite_int64 iDocid){
+  const char **pValues;
+  int i, rc;
+
+  /* TODO(shess) Should we allow such tables at all? */
+  if( DL_DEFAULT==DL_DOCIDS ) return SQLITE_ERROR;
+
+  rc = content_select(v, iDocid, &pValues);
+  if( rc!=SQLITE_OK ) return rc;
+
+  for(i = 0 ; i < v->nColumn; ++i) {
+    rc = buildTerms(v, iDocid, pValues[i], -1);
+    if( rc!=SQLITE_OK ) break;
+  }
+
+  freeStringArray(v->nColumn, pValues);
   return SQLITE_OK;
 }
 
-static const sqlite3_module fts3Module = {
-  /* iVersion      */ 2,
-  /* xCreate       */ fts3CreateMethod,
-  /* xConnect      */ fts3ConnectMethod,
-  /* xBestIndex    */ fts3BestIndexMethod,
-  /* xDisconnect   */ fts3DisconnectMethod,
-  /* xDestroy      */ fts3DestroyMethod,
-  /* xOpen         */ fts3OpenMethod,
-  /* xClose        */ fts3CloseMethod,
-  /* xFilter       */ fts3FilterMethod,
-  /* xNext         */ fts3NextMethod,
-  /* xEof          */ fts3EofMethod,
-  /* xColumn       */ fts3ColumnMethod,
-  /* xRowid        */ fts3RowidMethod,
-  /* xUpdate       */ fts3UpdateMethod,
-  /* xBegin        */ fts3BeginMethod,
-  /* xSync         */ fts3SyncMethod,
-  /* xCommit       */ fts3CommitMethod,
-  /* xRollback     */ fts3RollbackMethod,
-  /* xFindFunction */ fts3FindFunctionMethod,
-  /* xRename */       fts3RenameMethod,
-  /* xSavepoint    */ fts3SavepointMethod,
-  /* xRelease      */ fts3ReleaseMethod,
-  /* xRollbackTo   */ fts3RollbackToMethod,
-};
+/* TODO(shess) Refactor the code to remove this forward decl. */
+static int initPendingTerms(fulltext_vtab *v, sqlite_int64 iDocid);
 
-/*
-** This function is registered as the module destructor (called when an
-** FTS3 enabled database connection is closed). It frees the memory
-** allocated for the tokenizer hash table.
+/* Insert a row into the %_content table; set *piDocid to be the ID of the
+** new row.  Add doclists for terms to pendingTerms.
 */
-static void hashDestroy(void *p){
-  Fts3Hash *pHash = (Fts3Hash *)p;
-  sqlite3Fts3HashClear(pHash);
-  sqlite3_free(pHash);
+static int index_insert(fulltext_vtab *v, sqlite3_value *pRequestDocid,
+                        sqlite3_value **pValues, sqlite_int64 *piDocid){
+  int rc;
+
+  rc = content_insert(v, pRequestDocid, pValues);  /* execute an SQL INSERT */
+  if( rc!=SQLITE_OK ) return rc;
+
+  /* docid column is an alias for rowid. */
+  *piDocid = sqlite3_last_insert_rowid(v->db);
+  rc = initPendingTerms(v, *piDocid);
+  if( rc!=SQLITE_OK ) return rc;
+
+  return insertTerms(v, *piDocid, pValues);
 }
 
-/*
-** The fts3 built-in tokenizers - "simple", "porter" and "icu"- are 
-** implemented in files fts3_tokenizer1.c, fts3_porter.c and fts3_icu.c
-** respectively. The following three forward declarations are for functions
-** declared in these files used to retrieve the respective implementations.
-**
-** Calling sqlite3Fts3SimpleTokenizerModule() sets the value pointed
-** to by the argument to point to the "simple" tokenizer implementation.
-** And so on.
+/* Delete a row from the %_content table; add empty doclists for terms
+** to pendingTerms.
 */
-void sqlite3Fts3SimpleTokenizerModule(sqlite3_tokenizer_module const**ppModule);
-void sqlite3Fts3PorterTokenizerModule(sqlite3_tokenizer_module const**ppModule);
-#ifndef SQLITE_DISABLE_FTS3_UNICODE
-void sqlite3Fts3UnicodeTokenizer(sqlite3_tokenizer_module const**ppModule);
-#endif
-#ifdef SQLITE_ENABLE_ICU
-void sqlite3Fts3IcuTokenizerModule(sqlite3_tokenizer_module const**ppModule);
-#endif
+static int index_delete(fulltext_vtab *v, sqlite_int64 iRow){
+  int rc = initPendingTerms(v, iRow);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** Initialize the fts3 extension. If this extension is built as part
-** of the sqlite library, then this function is called directly by
-** SQLite. If fts3 is built as a dynamically loadable extension, this
-** function is called by the sqlite3_extension_init() entry point.
-*/
-int sqlite3Fts3Init(sqlite3 *db){
-  int rc = SQLITE_OK;
-  Fts3Hash *pHash = 0;
-  const sqlite3_tokenizer_module *pSimple = 0;
-  const sqlite3_tokenizer_module *pPorter = 0;
-#ifndef SQLITE_DISABLE_FTS3_UNICODE
-  const sqlite3_tokenizer_module *pUnicode = 0;
-#endif
+  rc = deleteTerms(v, iRow);
+  if( rc!=SQLITE_OK ) return rc;
 
-#ifdef SQLITE_ENABLE_ICU
-  const sqlite3_tokenizer_module *pIcu = 0;
-  sqlite3Fts3IcuTokenizerModule(&pIcu);
-#endif
+  return content_delete(v, iRow);  /* execute an SQL DELETE */
+}
 
-#ifndef SQLITE_DISABLE_FTS3_UNICODE
-  sqlite3Fts3UnicodeTokenizer(&pUnicode);
-#endif
+/* Update a row in the %_content table; add delete doclists to
+** pendingTerms for old terms not in the new data, add insert doclists
+** to pendingTerms for terms in the new data.
+*/
+static int index_update(fulltext_vtab *v, sqlite_int64 iRow,
+                        sqlite3_value **pValues){
+  int rc = initPendingTerms(v, iRow);
+  if( rc!=SQLITE_OK ) return rc;
 
-#ifdef SQLITE_TEST
-  rc = sqlite3Fts3InitTerm(db);
+  /* Generate an empty doclist for each term that previously appeared in this
+   * row. */
+  rc = deleteTerms(v, iRow);
   if( rc!=SQLITE_OK ) return rc;
-#endif
 
-  rc = sqlite3Fts3InitAux(db);
+  rc = content_update(v, pValues, iRow);  /* execute an SQL UPDATE */
   if( rc!=SQLITE_OK ) return rc;
 
-  sqlite3Fts3SimpleTokenizerModule(&pSimple);
-  sqlite3Fts3PorterTokenizerModule(&pPorter);
+  /* Now add positions for terms which appear in the updated row. */
+  return insertTerms(v, iRow, pValues);
+}
 
-  /* Allocate and initialize the hash-table used to store tokenizers. */
-  pHash = sqlite3_malloc(sizeof(Fts3Hash));
-  if( !pHash ){
-    rc = SQLITE_NOMEM;
-  }else{
-    sqlite3Fts3HashInit(pHash, FTS3_HASH_STRING, 1);
-  }
+/*******************************************************************/
+/* InteriorWriter is used to collect terms and block references into
+** interior nodes in %_segments.  See commentary at top of file for
+** format.
+*/
 
-  /* Load the built-in tokenizers into the hash table */
-  if( rc==SQLITE_OK ){
-    if( sqlite3Fts3HashInsert(pHash, "simple", 7, (void *)pSimple)
-     || sqlite3Fts3HashInsert(pHash, "porter", 7, (void *)pPorter) 
+/* How large interior nodes can grow. */
+#define INTERIOR_MAX 2048
 
-#ifndef SQLITE_DISABLE_FTS3_UNICODE
-     || sqlite3Fts3HashInsert(pHash, "unicode61", 10, (void *)pUnicode) 
+/* Minimum number of terms per interior node (except the root). This
+** prevents large terms from making the tree too skinny - must be >0
+** so that the tree always makes progress.  Note that the min tree
+** fanout will be INTERIOR_MIN_TERMS+1.
+*/
+#define INTERIOR_MIN_TERMS 7
+#if INTERIOR_MIN_TERMS<1
+# error INTERIOR_MIN_TERMS must be greater than 0.
 #endif
-#ifdef SQLITE_ENABLE_ICU
-     || (pIcu && sqlite3Fts3HashInsert(pHash, "icu", 4, (void *)pIcu))
+
+/* ROOT_MAX controls how much data is stored inline in the segment
+** directory.
+*/
+/* TODO(shess) Push ROOT_MAX down to whoever is writing things.  It's
+** only here so that interiorWriterRootInfo() and leafWriterRootInfo()
+** can both see it, but if the caller passed it in, we wouldn't even
+** need a define.
+*/
+#define ROOT_MAX 1024
+#if ROOT_MAX<VARINT_MAX*2
+# error ROOT_MAX must have enough space for a header.
 #endif
-    ){
-      rc = SQLITE_NOMEM;
+
+/* InteriorBlock stores a linked-list of interior blocks while a lower
+** layer is being constructed.
+*/
+typedef struct InteriorBlock {
+  DataBuffer term;           /* Leftmost term in block's subtree. */
+  DataBuffer data;           /* Accumulated data for the block. */
+  struct InteriorBlock *next;
+} InteriorBlock;
+
+static InteriorBlock *interiorBlockNew(int iHeight, sqlite_int64 iChildBlock,
+                                       const char *pTerm, int nTerm){
+  InteriorBlock *block = sqlite3_malloc(sizeof(InteriorBlock));
+  char c[VARINT_MAX+VARINT_MAX];
+  int n;
+
+  if( block ){
+    memset(block, 0, sizeof(*block));
+    dataBufferInit(&block->term, 0);
+    dataBufferReplace(&block->term, pTerm, nTerm);
+
+    n = fts3PutVarint(c, iHeight);
+    n += fts3PutVarint(c+n, iChildBlock);
+    dataBufferInit(&block->data, INTERIOR_MAX);
+    dataBufferReplace(&block->data, c, n);
+  }
+  return block;
+}
+
+#ifndef NDEBUG
+/* Verify that the data is readable as an interior node. */
+static void interiorBlockValidate(InteriorBlock *pBlock){
+  const char *pData = pBlock->data.pData;
+  int nData = pBlock->data.nData;
+  int n, iDummy;
+  sqlite_int64 iBlockid;
+
+  assert( nData>0 );
+  assert( pData!=0 );
+  assert( pData+nData>pData );
+
+  /* Must lead with height of node as a varint(n), n>0 */
+  n = fts3GetVarint32(pData, &iDummy);
+  assert( n>0 );
+  assert( iDummy>0 );
+  assert( n<nData );
+  pData += n;
+  nData -= n;
+
+  /* Must contain iBlockid. */
+  n = fts3GetVarint(pData, &iBlockid);
+  assert( n>0 );
+  assert( n<=nData );
+  pData += n;
+  nData -= n;
+
+  /* Zero or more terms of positive length */
+  if( nData!=0 ){
+    /* First term is not delta-encoded. */
+    n = fts3GetVarint32(pData, &iDummy);
+    assert( n>0 );
+    assert( iDummy>0 );
+    assert( n+iDummy>0);
+    assert( n+iDummy<=nData );
+    pData += n+iDummy;
+    nData -= n+iDummy;
+
+    /* Following terms delta-encoded. */
+    while( nData!=0 ){
+      /* Length of shared prefix. */
+      n = fts3GetVarint32(pData, &iDummy);
+      assert( n>0 );
+      assert( iDummy>=0 );
+      assert( n<nData );
+      pData += n;
+      nData -= n;
+
+      /* Length and data of distinct suffix. */
+      n = fts3GetVarint32(pData, &iDummy);
+      assert( n>0 );
+      assert( iDummy>0 );
+      assert( n+iDummy>0);
+      assert( n+iDummy<=nData );
+      pData += n+iDummy;
+      nData -= n+iDummy;
     }
   }
+}
+#define ASSERT_VALID_INTERIOR_BLOCK(x) interiorBlockValidate(x)
+#else
+#define ASSERT_VALID_INTERIOR_BLOCK(x) assert( 1 )
+#endif
 
-#ifdef SQLITE_TEST
-  if( rc==SQLITE_OK ){
-    rc = sqlite3Fts3ExprInitTestInterface(db);
-  }
+typedef struct InteriorWriter {
+  int iHeight;                   /* from 0 at leaves. */
+  InteriorBlock *first, *last;
+  struct InteriorWriter *parentWriter;
+
+  DataBuffer term;               /* Last term written to block "last". */
+  sqlite_int64 iOpeningChildBlock; /* First child block in block "last". */
+#ifndef NDEBUG
+  sqlite_int64 iLastChildBlock;  /* for consistency checks. */
 #endif
+} InteriorWriter;
 
-  /* Create the virtual table wrapper around the hash-table and overload 
-  ** the four scalar functions. If this is successful, register the
-  ** module with sqlite.
+/* Initialize an interior node where pTerm[nTerm] marks the leftmost
+** term in the tree.  iChildBlock is the leftmost child block at the
+** next level down the tree.
+*/
+static void interiorWriterInit(int iHeight, const char *pTerm, int nTerm,
+                               sqlite_int64 iChildBlock,
+                               InteriorWriter *pWriter){
+  InteriorBlock *block;
+  assert( iHeight>0 );
+  CLEAR(pWriter);
+
+  pWriter->iHeight = iHeight;
+  pWriter->iOpeningChildBlock = iChildBlock;
+#ifndef NDEBUG
+  pWriter->iLastChildBlock = iChildBlock;
+#endif
+  block = interiorBlockNew(iHeight, iChildBlock, pTerm, nTerm);
+  pWriter->last = pWriter->first = block;
+  ASSERT_VALID_INTERIOR_BLOCK(pWriter->last);
+  dataBufferInit(&pWriter->term, 0);
+}
+
+/* Append the child node rooted at iChildBlock to the interior node,
+** with pTerm[nTerm] as the leftmost term in iChildBlock's subtree.
+*/
+static void interiorWriterAppend(InteriorWriter *pWriter,
+                                 const char *pTerm, int nTerm,
+                                 sqlite_int64 iChildBlock){
+  char c[VARINT_MAX+VARINT_MAX];
+  int n, nPrefix = 0;
+
+  ASSERT_VALID_INTERIOR_BLOCK(pWriter->last);
+
+  /* The first term written into an interior node is actually
+  ** associated with the second child added (the first child was added
+  ** in interiorWriterInit, or in the if clause at the bottom of this
+  ** function).  That term gets encoded straight up, with nPrefix left
+  ** at 0.
   */
-  if( SQLITE_OK==rc 
-   && SQLITE_OK==(rc = sqlite3Fts3InitHashTable(db, pHash, "fts3_tokenizer"))
-   && SQLITE_OK==(rc = sqlite3_overload_function(db, "snippet", -1))
-   && SQLITE_OK==(rc = sqlite3_overload_function(db, "offsets", 1))
-   && SQLITE_OK==(rc = sqlite3_overload_function(db, "matchinfo", 1))
-   && SQLITE_OK==(rc = sqlite3_overload_function(db, "matchinfo", 2))
-   && SQLITE_OK==(rc = sqlite3_overload_function(db, "optimize", 1))
-  ){
-    rc = sqlite3_create_module_v2(
-        db, "fts3", &fts3Module, (void *)pHash, hashDestroy
-    );
-    if( rc==SQLITE_OK ){
-      rc = sqlite3_create_module_v2(
-          db, "fts4", &fts3Module, (void *)pHash, 0
-      );
-    }
-    if( rc==SQLITE_OK ){
-      rc = sqlite3Fts3InitTok(db, (void *)pHash);
+  if( pWriter->term.nData==0 ){
+    n = fts3PutVarint(c, nTerm);
+  }else{
+    while( nPrefix<pWriter->term.nData &&
+           pTerm[nPrefix]==pWriter->term.pData[nPrefix] ){
+      nPrefix++;
     }
-    return rc;
+
+    n = fts3PutVarint(c, nPrefix);
+    n += fts3PutVarint(c+n, nTerm-nPrefix);
   }
 
+#ifndef NDEBUG
+  pWriter->iLastChildBlock++;
+#endif
+  assert( pWriter->iLastChildBlock==iChildBlock );
 
-  /* An error has occurred. Delete the hash table and return the error code. */
-  assert( rc!=SQLITE_OK );
-  if( pHash ){
-    sqlite3Fts3HashClear(pHash);
-    sqlite3_free(pHash);
+  /* Overflow to a new block if the new term makes the current block
+  ** too big, and the current block already has enough terms.
+  */
+  if( pWriter->last->data.nData+n+nTerm-nPrefix>INTERIOR_MAX &&
+      iChildBlock-pWriter->iOpeningChildBlock>INTERIOR_MIN_TERMS ){
+    pWriter->last->next = interiorBlockNew(pWriter->iHeight, iChildBlock,
+                                           pTerm, nTerm);
+    pWriter->last = pWriter->last->next;
+    pWriter->iOpeningChildBlock = iChildBlock;
+    dataBufferReset(&pWriter->term);
+  }else{
+    dataBufferAppend2(&pWriter->last->data, c, n,
+                      pTerm+nPrefix, nTerm-nPrefix);
+    dataBufferReplace(&pWriter->term, pTerm, nTerm);
   }
-  return rc;
+  ASSERT_VALID_INTERIOR_BLOCK(pWriter->last);
 }
 
-/*
-** Allocate an Fts3MultiSegReader for each token in the expression headed
-** by pExpr. 
-**
-** An Fts3SegReader object is a cursor that can seek or scan a range of
-** entries within a single segment b-tree. An Fts3MultiSegReader uses multiple
-** Fts3SegReader objects internally to provide an interface to seek or scan
-** within the union of all segments of a b-tree. Hence the name.
-**
-** If the allocated Fts3MultiSegReader just seeks to a single entry in a
-** segment b-tree (if the term is not a prefix or it is a prefix for which
-** there exists prefix b-tree of the right length) then it may be traversed
-** and merged incrementally. Otherwise, it has to be merged into an in-memory 
-** doclist and then traversed.
-*/
-static void fts3EvalAllocateReaders(
-  Fts3Cursor *pCsr,               /* FTS cursor handle */
-  Fts3Expr *pExpr,                /* Allocate readers for this expression */
-  int *pnToken,                   /* OUT: Total number of tokens in phrase. */
-  int *pnOr,                      /* OUT: Total number of OR nodes in expr. */
-  int *pRc                        /* IN/OUT: Error code */
-){
-  if( pExpr && SQLITE_OK==*pRc ){
-    if( pExpr->eType==FTSQUERY_PHRASE ){
-      int i;
-      int nToken = pExpr->pPhrase->nToken;
-      *pnToken += nToken;
-      for(i=0; i<nToken; i++){
-        Fts3PhraseToken *pToken = &pExpr->pPhrase->aToken[i];
-        int rc = fts3TermSegReaderCursor(pCsr, 
-            pToken->z, pToken->n, pToken->isPrefix, &pToken->pSegcsr
-        );
-        if( rc!=SQLITE_OK ){
-          *pRc = rc;
-          return;
-        }
-      }
-      assert( pExpr->pPhrase->iDoclistToken==0 );
-      pExpr->pPhrase->iDoclistToken = -1;
-    }else{
-      *pnOr += (pExpr->eType==FTSQUERY_OR);
-      fts3EvalAllocateReaders(pCsr, pExpr->pLeft, pnToken, pnOr, pRc);
-      fts3EvalAllocateReaders(pCsr, pExpr->pRight, pnToken, pnOr, pRc);
-    }
+/* Free the space used by pWriter, including the linked-list of
+** InteriorBlocks, and parentWriter, if present.
+*/
+static int interiorWriterDestroy(InteriorWriter *pWriter){
+  InteriorBlock *block = pWriter->first;
+
+  while( block!=NULL ){
+    InteriorBlock *b = block;
+    block = block->next;
+    dataBufferDestroy(&b->term);
+    dataBufferDestroy(&b->data);
+    sqlite3_free(b);
+  }
+  if( pWriter->parentWriter!=NULL ){
+    interiorWriterDestroy(pWriter->parentWriter);
+    sqlite3_free(pWriter->parentWriter);
   }
+  dataBufferDestroy(&pWriter->term);
+  SCRAMBLE(pWriter);
+  return SQLITE_OK;
 }
 
-/*
-** Arguments pList/nList contain the doclist for token iToken of phrase p.
-** It is merged into the main doclist stored in p->doclist.aAll/nAll.
-**
-** This function assumes that pList points to a buffer allocated using
-** sqlite3_malloc(). This function takes responsibility for eventually
-** freeing the buffer.
-**
-** SQLITE_OK is returned if successful, or SQLITE_NOMEM if an error occurs.
-*/
-static int fts3EvalPhraseMergeToken(
-  Fts3Table *pTab,                /* FTS Table pointer */
-  Fts3Phrase *p,                  /* Phrase to merge pList/nList into */
-  int iToken,                     /* Token pList/nList corresponds to */
-  char *pList,                    /* Pointer to doclist */
-  int nList                       /* Number of bytes in pList */
-){
-  int rc = SQLITE_OK;
-  assert( iToken!=p->iDoclistToken );
-
-  if( pList==0 ){
-    sqlite3_free(p->doclist.aAll);
-    p->doclist.aAll = 0;
-    p->doclist.nAll = 0;
-  }
+/* If pWriter can fit entirely in ROOT_MAX, return it as the root info
+** directly, leaving *piEndBlockid unchanged.  Otherwise, flush
+** pWriter to %_segments, building a new layer of interior nodes, and
+** recursively ask for their root into.
+*/
+static int interiorWriterRootInfo(fulltext_vtab *v, InteriorWriter *pWriter,
+                                  char **ppRootInfo, int *pnRootInfo,
+                                  sqlite_int64 *piEndBlockid){
+  InteriorBlock *block = pWriter->first;
+  sqlite_int64 iBlockid = 0;
+  int rc;
 
-  else if( p->iDoclistToken<0 ){
-    p->doclist.aAll = pList;
-    p->doclist.nAll = nList;
+  /* If we can fit the segment inline */
+  if( block==pWriter->last && block->data.nData<ROOT_MAX ){
+    *ppRootInfo = block->data.pData;
+    *pnRootInfo = block->data.nData;
+    return SQLITE_OK;
   }
 
-  else if( p->doclist.aAll==0 ){
-    sqlite3_free(pList);
-  }
+  /* Flush the first block to %_segments, and create a new level of
+  ** interior node.
+  */
+  ASSERT_VALID_INTERIOR_BLOCK(block);
+  rc = block_insert(v, block->data.pData, block->data.nData, &iBlockid);
+  if( rc!=SQLITE_OK ) return rc;
+  *piEndBlockid = iBlockid;
 
-  else {
-    char *pLeft;
-    char *pRight;
-    int nLeft;
-    int nRight;
-    int nDiff;
+  pWriter->parentWriter = sqlite3_malloc(sizeof(*pWriter->parentWriter));
+  interiorWriterInit(pWriter->iHeight+1,
+                     block->term.pData, block->term.nData,
+                     iBlockid, pWriter->parentWriter);
 
-    if( p->iDoclistToken<iToken ){
-      pLeft = p->doclist.aAll;
-      nLeft = p->doclist.nAll;
-      pRight = pList;
-      nRight = nList;
-      nDiff = iToken - p->iDoclistToken;
-    }else{
-      pRight = p->doclist.aAll;
-      nRight = p->doclist.nAll;
-      pLeft = pList;
-      nLeft = nList;
-      nDiff = p->iDoclistToken - iToken;
-    }
+  /* Flush additional blocks and append to the higher interior
+  ** node.
+  */
+  for(block=block->next; block!=NULL; block=block->next){
+    ASSERT_VALID_INTERIOR_BLOCK(block);
+    rc = block_insert(v, block->data.pData, block->data.nData, &iBlockid);
+    if( rc!=SQLITE_OK ) return rc;
+    *piEndBlockid = iBlockid;
 
-    rc = fts3DoclistPhraseMerge(
-        pTab->bDescIdx, nDiff, pLeft, nLeft, &pRight, &nRight
-    );
-    sqlite3_free(pLeft);
-    p->doclist.aAll = pRight;
-    p->doclist.nAll = nRight;
+    interiorWriterAppend(pWriter->parentWriter,
+                         block->term.pData, block->term.nData, iBlockid);
   }
 
-  if( iToken>p->iDoclistToken ) p->iDoclistToken = iToken;
-  return rc;
+  /* Parent node gets the chance to be the root. */
+  return interiorWriterRootInfo(v, pWriter->parentWriter,
+                                ppRootInfo, pnRootInfo, piEndBlockid);
 }
 
-/*
-** Load the doclist for phrase p into p->doclist.aAll/nAll. The loaded doclist
-** does not take deferred tokens into account.
-**
-** SQLITE_OK is returned if no error occurs, otherwise an SQLite error code.
+/****************************************************************/
+/* InteriorReader is used to read off the data from an interior node
+** (see comment at top of file for the format).
 */
-static int fts3EvalPhraseLoad(
-  Fts3Cursor *pCsr,               /* FTS Cursor handle */
-  Fts3Phrase *p                   /* Phrase object */
-){
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-  int iToken;
-  int rc = SQLITE_OK;
+typedef struct InteriorReader {
+  const char *pData;
+  int nData;
 
-  for(iToken=0; rc==SQLITE_OK && iToken<p->nToken; iToken++){
-    Fts3PhraseToken *pToken = &p->aToken[iToken];
-    assert( pToken->pDeferred==0 || pToken->pSegcsr==0 );
-
-    if( pToken->pSegcsr ){
-      int nThis = 0;
-      char *pThis = 0;
-      rc = fts3TermSelect(pTab, pToken, p->iColumn, &nThis, &pThis);
-      if( rc==SQLITE_OK ){
-        rc = fts3EvalPhraseMergeToken(pTab, p, iToken, pThis, nThis);
-      }
-    }
-    assert( pToken->pSegcsr==0 );
-  }
+  DataBuffer term;          /* previous term, for decoding term delta. */
 
-  return rc;
-}
+  sqlite_int64 iBlockid;
+} InteriorReader;
 
-/*
-** This function is called on each phrase after the position lists for
-** any deferred tokens have been loaded into memory. It updates the phrases
-** current position list to include only those positions that are really
-** instances of the phrase (after considering deferred tokens). If this
-** means that the phrase does not appear in the current row, doclist.pList
-** and doclist.nList are both zeroed.
-**
-** SQLITE_OK is returned if no error occurs, otherwise an SQLite error code.
-*/
-static int fts3EvalDeferredPhrase(Fts3Cursor *pCsr, Fts3Phrase *pPhrase){
-  int iToken;                     /* Used to iterate through phrase tokens */
-  char *aPoslist = 0;             /* Position list for deferred tokens */
-  int nPoslist = 0;               /* Number of bytes in aPoslist */
-  int iPrev = -1;                 /* Token number of previous deferred token */
-
-  assert( pPhrase->doclist.bFreeList==0 );
-
-  for(iToken=0; iToken<pPhrase->nToken; iToken++){
-    Fts3PhraseToken *pToken = &pPhrase->aToken[iToken];
-    Fts3DeferredToken *pDeferred = pToken->pDeferred;
-
-    if( pDeferred ){
-      char *pList;
-      int nList;
-      int rc = sqlite3Fts3DeferredTokenList(pDeferred, &pList, &nList);
-      if( rc!=SQLITE_OK ) return rc;
+static void interiorReaderDestroy(InteriorReader *pReader){
+  dataBufferDestroy(&pReader->term);
+  SCRAMBLE(pReader);
+}
 
-      if( pList==0 ){
-        sqlite3_free(aPoslist);
-        pPhrase->doclist.pList = 0;
-        pPhrase->doclist.nList = 0;
-        return SQLITE_OK;
+/* TODO(shess) The assertions are great, but what if we're in NDEBUG
+** and the blob is empty or otherwise contains suspect data?
+*/
+static void interiorReaderInit(const char *pData, int nData,
+                               InteriorReader *pReader){
+  int n, nTerm;
 
-      }else if( aPoslist==0 ){
-        aPoslist = pList;
-        nPoslist = nList;
+  /* Require at least the leading flag byte */
+  assert( nData>0 );
+  assert( pData[0]!='\0' );
 
-      }else{
-        char *aOut = pList;
-        char *p1 = aPoslist;
-        char *p2 = aOut;
-
-        assert( iPrev>=0 );
-        fts3PoslistPhraseMerge(&aOut, iToken-iPrev, 0, 1, &p1, &p2);
-        sqlite3_free(aPoslist);
-        aPoslist = pList;
-        nPoslist = (int)(aOut - aPoslist);
-        if( nPoslist==0 ){
-          sqlite3_free(aPoslist);
-          pPhrase->doclist.pList = 0;
-          pPhrase->doclist.nList = 0;
-          return SQLITE_OK;
-        }
-      }
-      iPrev = iToken;
-    }
-  }
+  CLEAR(pReader);
 
-  if( iPrev>=0 ){
-    int nMaxUndeferred = pPhrase->iDoclistToken;
-    if( nMaxUndeferred<0 ){
-      pPhrase->doclist.pList = aPoslist;
-      pPhrase->doclist.nList = nPoslist;
-      pPhrase->doclist.iDocid = pCsr->iPrevId;
-      pPhrase->doclist.bFreeList = 1;
-    }else{
-      int nDistance;
-      char *p1;
-      char *p2;
-      char *aOut;
-
-      if( nMaxUndeferred>iPrev ){
-        p1 = aPoslist;
-        p2 = pPhrase->doclist.pList;
-        nDistance = nMaxUndeferred - iPrev;
-      }else{
-        p1 = pPhrase->doclist.pList;
-        p2 = aPoslist;
-        nDistance = iPrev - nMaxUndeferred;
-      }
+  /* Decode the base blockid, and set the cursor to the first term. */
+  n = fts3GetVarint(pData+1, &pReader->iBlockid);
+  assert( 1+n<=nData );
+  pReader->pData = pData+1+n;
+  pReader->nData = nData-(1+n);
 
-      aOut = (char *)sqlite3_malloc(nPoslist+8);
-      if( !aOut ){
-        sqlite3_free(aPoslist);
-        return SQLITE_NOMEM;
-      }
-      
-      pPhrase->doclist.pList = aOut;
-      if( fts3PoslistPhraseMerge(&aOut, nDistance, 0, 1, &p1, &p2) ){
-        pPhrase->doclist.bFreeList = 1;
-        pPhrase->doclist.nList = (int)(aOut - pPhrase->doclist.pList);
-      }else{
-        sqlite3_free(aOut);
-        pPhrase->doclist.pList = 0;
-        pPhrase->doclist.nList = 0;
-      }
-      sqlite3_free(aPoslist);
-    }
+  /* A single-child interior node (such as when a leaf node was too
+  ** large for the segment directory) won't have any terms.
+  ** Otherwise, decode the first term.
+  */
+  if( pReader->nData==0 ){
+    dataBufferInit(&pReader->term, 0);
+  }else{
+    n = fts3GetVarint32(pReader->pData, &nTerm);
+    dataBufferInit(&pReader->term, nTerm);
+    dataBufferReplace(&pReader->term, pReader->pData+n, nTerm);
+    assert( n+nTerm<=pReader->nData );
+    pReader->pData += n+nTerm;
+    pReader->nData -= n+nTerm;
   }
-
-  return SQLITE_OK;
 }
 
-/*
-** Maximum number of tokens a phrase may have to be considered for the
-** incremental doclists strategy.
-*/
-#define MAX_INCR_PHRASE_TOKENS 4
-
-/*
-** This function is called for each Fts3Phrase in a full-text query 
-** expression to initialize the mechanism for returning rows. Once this
-** function has been called successfully on an Fts3Phrase, it may be
-** used with fts3EvalPhraseNext() to iterate through the matching docids.
-**
-** If parameter bOptOk is true, then the phrase may (or may not) use the
-** incremental loading strategy. Otherwise, the entire doclist is loaded into
-** memory within this call.
-**
-** SQLITE_OK is returned if no error occurs, otherwise an SQLite error code.
-*/
-static int fts3EvalPhraseStart(Fts3Cursor *pCsr, int bOptOk, Fts3Phrase *p){
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-  int rc = SQLITE_OK;             /* Error code */
-  int i;
+static int interiorReaderAtEnd(InteriorReader *pReader){
+  return pReader->term.nData==0;
+}
 
-  /* Determine if doclists may be loaded from disk incrementally. This is
-  ** possible if the bOptOk argument is true, the FTS doclists will be
-  ** scanned in forward order, and the phrase consists of 
-  ** MAX_INCR_PHRASE_TOKENS or fewer tokens, none of which are are "^first"
-  ** tokens or prefix tokens that cannot use a prefix-index.  */
-  int bHaveIncr = 0;
-  int bIncrOk = (bOptOk 
-   && pCsr->bDesc==pTab->bDescIdx 
-   && p->nToken<=MAX_INCR_PHRASE_TOKENS && p->nToken>0
-#ifdef SQLITE_TEST
-   && pTab->bNoIncrDoclist==0
-#endif
-  );
-  for(i=0; bIncrOk==1 && i<p->nToken; i++){
-    Fts3PhraseToken *pToken = &p->aToken[i];
-    if( pToken->bFirst || (pToken->pSegcsr!=0 && !pToken->pSegcsr->bLookup) ){
-      bIncrOk = 0;
-    }
-    if( pToken->pSegcsr ) bHaveIncr = 1;
-  }
-
-  if( bIncrOk && bHaveIncr ){
-    /* Use the incremental approach. */
-    int iCol = (p->iColumn >= pTab->nColumn ? -1 : p->iColumn);
-    for(i=0; rc==SQLITE_OK && i<p->nToken; i++){
-      Fts3PhraseToken *pToken = &p->aToken[i];
-      Fts3MultiSegReader *pSegcsr = pToken->pSegcsr;
-      if( pSegcsr ){
-        rc = sqlite3Fts3MsrIncrStart(pTab, pSegcsr, iCol, pToken->z, pToken->n);
-      }
-    }
-    p->bIncr = 1;
-  }else{
-    /* Load the full doclist for the phrase into memory. */
-    rc = fts3EvalPhraseLoad(pCsr, p);
-    p->bIncr = 0;
-  }
+static sqlite_int64 interiorReaderCurrentBlockid(InteriorReader *pReader){
+  return pReader->iBlockid;
+}
 
-  assert( rc!=SQLITE_OK || p->nToken<1 || p->aToken[0].pSegcsr==0 || p->bIncr );
-  return rc;
+static int interiorReaderTermBytes(InteriorReader *pReader){
+  assert( !interiorReaderAtEnd(pReader) );
+  return pReader->term.nData;
+}
+static const char *interiorReaderTerm(InteriorReader *pReader){
+  assert( !interiorReaderAtEnd(pReader) );
+  return pReader->term.pData;
 }
 
-/*
-** This function is used to iterate backwards (from the end to start) 
-** through doclists. It is used by this module to iterate through phrase
-** doclists in reverse and by the fts3_write.c module to iterate through
-** pending-terms lists when writing to databases with "order=desc".
-**
-** The doclist may be sorted in ascending (parameter bDescIdx==0) or 
-** descending (parameter bDescIdx==1) order of docid. Regardless, this
-** function iterates from the end of the doclist to the beginning.
-*/
-void sqlite3Fts3DoclistPrev(
-  int bDescIdx,                   /* True if the doclist is desc */
-  char *aDoclist,                 /* Pointer to entire doclist */
-  int nDoclist,                   /* Length of aDoclist in bytes */
-  char **ppIter,                  /* IN/OUT: Iterator pointer */
-  sqlite3_int64 *piDocid,         /* IN/OUT: Docid pointer */
-  int *pnList,                    /* OUT: List length pointer */
-  u8 *pbEof                       /* OUT: End-of-file flag */
-){
-  char *p = *ppIter;
+/* Step forward to the next term in the node. */
+static void interiorReaderStep(InteriorReader *pReader){
+  assert( !interiorReaderAtEnd(pReader) );
 
-  assert( nDoclist>0 );
-  assert( *pbEof==0 );
-  assert( p || *piDocid==0 );
-  assert( !p || (p>aDoclist && p<&aDoclist[nDoclist]) );
-
-  if( p==0 ){
-    sqlite3_int64 iDocid = 0;
-    char *pNext = 0;
-    char *pDocid = aDoclist;
-    char *pEnd = &aDoclist[nDoclist];
-    int iMul = 1;
-
-    while( pDocid<pEnd ){
-      sqlite3_int64 iDelta;
-      pDocid += sqlite3Fts3GetVarint(pDocid, &iDelta);
-      iDocid += (iMul * iDelta);
-      pNext = pDocid;
-      fts3PoslistCopy(0, &pDocid);
-      while( pDocid<pEnd && *pDocid==0 ) pDocid++;
-      iMul = (bDescIdx ? -1 : 1);
-    }
-
-    *pnList = (int)(pEnd - pNext);
-    *ppIter = pNext;
-    *piDocid = iDocid;
+  /* If the last term has been read, signal eof, else construct the
+  ** next term.
+  */
+  if( pReader->nData==0 ){
+    dataBufferReset(&pReader->term);
   }else{
-    int iMul = (bDescIdx ? -1 : 1);
-    sqlite3_int64 iDelta;
-    fts3GetReverseVarint(&p, aDoclist, &iDelta);
-    *piDocid -= (iMul * iDelta);
+    int n, nPrefix, nSuffix;
 
-    if( p==aDoclist ){
-      *pbEof = 1;
-    }else{
-      char *pSave = p;
-      fts3ReversePoslist(aDoclist, &p);
-      *pnList = (int)(pSave - p);
-    }
-    *ppIter = p;
+    n = fts3GetVarint32(pReader->pData, &nPrefix);
+    n += fts3GetVarint32(pReader->pData+n, &nSuffix);
+
+    /* Truncate the current term and append suffix data. */
+    pReader->term.nData = nPrefix;
+    dataBufferAppend(&pReader->term, pReader->pData+n, nSuffix);
+
+    assert( n+nSuffix<=pReader->nData );
+    pReader->pData += n+nSuffix;
+    pReader->nData -= n+nSuffix;
   }
+  pReader->iBlockid++;
 }
 
-/*
-** Iterate forwards through a doclist.
+/* Compare the current term to pTerm[nTerm], returning strcmp-style
+** results.  If isPrefix, equality means equal through nTerm bytes.
 */
-void sqlite3Fts3DoclistNext(
-  int bDescIdx,                   /* True if the doclist is desc */
-  char *aDoclist,                 /* Pointer to entire doclist */
-  int nDoclist,                   /* Length of aDoclist in bytes */
-  char **ppIter,                  /* IN/OUT: Iterator pointer */
-  sqlite3_int64 *piDocid,         /* IN/OUT: Docid pointer */
-  u8 *pbEof                       /* OUT: End-of-file flag */
-){
-  char *p = *ppIter;
+static int interiorReaderTermCmp(InteriorReader *pReader,
+                                 const char *pTerm, int nTerm, int isPrefix){
+  const char *pReaderTerm = interiorReaderTerm(pReader);
+  int nReaderTerm = interiorReaderTermBytes(pReader);
+  int c, n = nReaderTerm<nTerm ? nReaderTerm : nTerm;
 
-  assert( nDoclist>0 );
-  assert( *pbEof==0 );
-  assert( p || *piDocid==0 );
-  assert( !p || (p>=aDoclist && p<=&aDoclist[nDoclist]) );
-
-  if( p==0 ){
-    p = aDoclist;
-    p += sqlite3Fts3GetVarint(p, piDocid);
-  }else{
-    fts3PoslistCopy(0, &p);
-    while( p<&aDoclist[nDoclist] && *p==0 ) p++; 
-    if( p>=&aDoclist[nDoclist] ){
-      *pbEof = 1;
-    }else{
-      sqlite3_int64 iVar;
-      p += sqlite3Fts3GetVarint(p, &iVar);
-      *piDocid += ((bDescIdx ? -1 : 1) * iVar);
-    }
+  if( n==0 ){
+    if( nReaderTerm>0 ) return -1;
+    if( nTerm>0 ) return 1;
+    return 0;
   }
 
-  *ppIter = p;
+  c = memcmp(pReaderTerm, pTerm, n);
+  if( c!=0 ) return c;
+  if( isPrefix && n==nTerm ) return 0;
+  return nReaderTerm - nTerm;
+}
+
+/****************************************************************/
+/* LeafWriter is used to collect terms and associated doclist data
+** into leaf blocks in %_segments (see top of file for format info).
+** Expected usage is:
+**
+** LeafWriter writer;
+** leafWriterInit(0, 0, &writer);
+** while( sorted_terms_left_to_process ){
+**   // data is doclist data for that term.
+**   rc = leafWriterStep(v, &writer, pTerm, nTerm, pData, nData);
+**   if( rc!=SQLITE_OK ) goto err;
+** }
+** rc = leafWriterFinalize(v, &writer);
+**err:
+** leafWriterDestroy(&writer);
+** return rc;
+**
+** leafWriterStep() may write a collected leaf out to %_segments.
+** leafWriterFinalize() finishes writing any buffered data and stores
+** a root node in %_segdir.  leafWriterDestroy() frees all buffers and
+** InteriorWriters allocated as part of writing this segment.
+**
+** TODO(shess) Document leafWriterStepMerge().
+*/
+
+/* Put terms with data this big in their own block. */
+#define STANDALONE_MIN 1024
+
+/* Keep leaf blocks below this size. */
+#define LEAF_MAX 2048
+
+typedef struct LeafWriter {
+  int iLevel;
+  int idx;
+  sqlite_int64 iStartBlockid;     /* needed to create the root info */
+  sqlite_int64 iEndBlockid;       /* when we're done writing. */
+
+  DataBuffer term;                /* previous encoded term */
+  DataBuffer data;                /* encoding buffer */
+
+  /* bytes of first term in the current node which distinguishes that
+  ** term from the last term of the previous node.
+  */
+  int nTermDistinct;
+
+  InteriorWriter parentWriter;    /* if we overflow */
+  int has_parent;
+} LeafWriter;
+
+static void leafWriterInit(int iLevel, int idx, LeafWriter *pWriter){
+  CLEAR(pWriter);
+  pWriter->iLevel = iLevel;
+  pWriter->idx = idx;
+
+  dataBufferInit(&pWriter->term, 32);
+
+  /* Start out with a reasonably sized block, though it can grow. */
+  dataBufferInit(&pWriter->data, LEAF_MAX);
+}
+
+#ifndef NDEBUG
+/* Verify that the data is readable as a leaf node. */
+static void leafNodeValidate(const char *pData, int nData){
+  int n, iDummy;
+
+  if( nData==0 ) return;
+  assert( nData>0 );
+  assert( pData!=0 );
+  assert( pData+nData>pData );
+
+  /* Must lead with a varint(0) */
+  n = fts3GetVarint32(pData, &iDummy);
+  assert( iDummy==0 );
+  assert( n>0 );
+  assert( n<nData );
+  pData += n;
+  nData -= n;
+
+  /* Leading term length and data must fit in buffer. */
+  n = fts3GetVarint32(pData, &iDummy);
+  assert( n>0 );
+  assert( iDummy>0 );
+  assert( n+iDummy>0 );
+  assert( n+iDummy<nData );
+  pData += n+iDummy;
+  nData -= n+iDummy;
+
+  /* Leading term's doclist length and data must fit. */
+  n = fts3GetVarint32(pData, &iDummy);
+  assert( n>0 );
+  assert( iDummy>0 );
+  assert( n+iDummy>0 );
+  assert( n+iDummy<=nData );
+  ASSERT_VALID_DOCLIST(DL_DEFAULT, pData+n, iDummy, NULL);
+  pData += n+iDummy;
+  nData -= n+iDummy;
+
+  /* Verify that trailing terms and doclists also are readable. */
+  while( nData!=0 ){
+    n = fts3GetVarint32(pData, &iDummy);
+    assert( n>0 );
+    assert( iDummy>=0 );
+    assert( n<nData );
+    pData += n;
+    nData -= n;
+    n = fts3GetVarint32(pData, &iDummy);
+    assert( n>0 );
+    assert( iDummy>0 );
+    assert( n+iDummy>0 );
+    assert( n+iDummy<nData );
+    pData += n+iDummy;
+    nData -= n+iDummy;
+
+    n = fts3GetVarint32(pData, &iDummy);
+    assert( n>0 );
+    assert( iDummy>0 );
+    assert( n+iDummy>0 );
+    assert( n+iDummy<=nData );
+    ASSERT_VALID_DOCLIST(DL_DEFAULT, pData+n, iDummy, NULL);
+    pData += n+iDummy;
+    nData -= n+iDummy;
+  }
 }
+#define ASSERT_VALID_LEAF_NODE(p, n) leafNodeValidate(p, n)
+#else
+#define ASSERT_VALID_LEAF_NODE(p, n) assert( 1 )
+#endif
 
-/*
-** Advance the iterator pDL to the next entry in pDL->aAll/nAll. Set *pbEof
-** to true if EOF is reached.
-*/
-static void fts3EvalDlPhraseNext(
-  Fts3Table *pTab,
-  Fts3Doclist *pDL,
-  u8 *pbEof
-){
-  char *pIter;                            /* Used to iterate through aAll */
-  char *pEnd = &pDL->aAll[pDL->nAll];     /* 1 byte past end of aAll */
- 
-  if( pDL->pNextDocid ){
-    pIter = pDL->pNextDocid;
+/* Flush the current leaf node to %_segments, and adding the resulting
+** blockid and the starting term to the interior node which will
+** contain it.
+*/
+static int leafWriterInternalFlush(fulltext_vtab *v, LeafWriter *pWriter,
+                                   int iData, int nData){
+  sqlite_int64 iBlockid = 0;
+  const char *pStartingTerm;
+  int nStartingTerm, rc, n;
+
+  /* Must have the leading varint(0) flag, plus at least some
+  ** valid-looking data.
+  */
+  assert( nData>2 );
+  assert( iData>=0 );
+  assert( iData+nData<=pWriter->data.nData );
+  ASSERT_VALID_LEAF_NODE(pWriter->data.pData+iData, nData);
+
+  rc = block_insert(v, pWriter->data.pData+iData, nData, &iBlockid);
+  if( rc!=SQLITE_OK ) return rc;
+  assert( iBlockid!=0 );
+
+  /* Reconstruct the first term in the leaf for purposes of building
+  ** the interior node.
+  */
+  n = fts3GetVarint32(pWriter->data.pData+iData+1, &nStartingTerm);
+  pStartingTerm = pWriter->data.pData+iData+1+n;
+  assert( pWriter->data.nData>iData+1+n+nStartingTerm );
+  assert( pWriter->nTermDistinct>0 );
+  assert( pWriter->nTermDistinct<=nStartingTerm );
+  nStartingTerm = pWriter->nTermDistinct;
+
+  if( pWriter->has_parent ){
+    interiorWriterAppend(&pWriter->parentWriter,
+                         pStartingTerm, nStartingTerm, iBlockid);
   }else{
-    pIter = pDL->aAll;
+    interiorWriterInit(1, pStartingTerm, nStartingTerm, iBlockid,
+                       &pWriter->parentWriter);
+    pWriter->has_parent = 1;
   }
 
-  if( pIter>=pEnd ){
-    /* We have already reached the end of this doclist. EOF. */
-    *pbEof = 1;
+  /* Track the span of this segment's leaf nodes. */
+  if( pWriter->iEndBlockid==0 ){
+    pWriter->iEndBlockid = pWriter->iStartBlockid = iBlockid;
   }else{
-    sqlite3_int64 iDelta;
-    pIter += sqlite3Fts3GetVarint(pIter, &iDelta);
-    if( pTab->bDescIdx==0 || pDL->pNextDocid==0 ){
-      pDL->iDocid += iDelta;
-    }else{
-      pDL->iDocid -= iDelta;
-    }
-    pDL->pList = pIter;
-    fts3PoslistCopy(0, &pIter);
-    pDL->nList = (int)(pIter - pDL->pList);
-
-    /* pIter now points just past the 0x00 that terminates the position-
-    ** list for document pDL->iDocid. However, if this position-list was
-    ** edited in place by fts3EvalNearTrim(), then pIter may not actually
-    ** point to the start of the next docid value. The following line deals
-    ** with this case by advancing pIter past the zero-padding added by
-    ** fts3EvalNearTrim().  */
-    while( pIter<pEnd && *pIter==0 ) pIter++;
-
-    pDL->pNextDocid = pIter;
-    assert( pIter>=&pDL->aAll[pDL->nAll] || *pIter );
-    *pbEof = 0;
+    pWriter->iEndBlockid++;
+    assert( iBlockid==pWriter->iEndBlockid );
   }
+
+  return SQLITE_OK;
 }
+static int leafWriterFlush(fulltext_vtab *v, LeafWriter *pWriter){
+  int rc = leafWriterInternalFlush(v, pWriter, 0, pWriter->data.nData);
+  if( rc!=SQLITE_OK ) return rc;
 
-/*
-** Helper type used by fts3EvalIncrPhraseNext() and incrPhraseTokenNext().
+  /* Re-initialize the output buffer. */
+  dataBufferReset(&pWriter->data);
+
+  return SQLITE_OK;
+}
+
+/* Fetch the root info for the segment.  If the entire leaf fits
+** within ROOT_MAX, then it will be returned directly, otherwise it
+** will be flushed and the root info will be returned from the
+** interior node.  *piEndBlockid is set to the blockid of the last
+** interior or leaf node written to disk (0 if none are written at
+** all).
+*/
+static int leafWriterRootInfo(fulltext_vtab *v, LeafWriter *pWriter,
+                              char **ppRootInfo, int *pnRootInfo,
+                              sqlite_int64 *piEndBlockid){
+  /* we can fit the segment entirely inline */
+  if( !pWriter->has_parent && pWriter->data.nData<ROOT_MAX ){
+    *ppRootInfo = pWriter->data.pData;
+    *pnRootInfo = pWriter->data.nData;
+    *piEndBlockid = 0;
+    return SQLITE_OK;
+  }
+
+  /* Flush remaining leaf data. */
+  if( pWriter->data.nData>0 ){
+    int rc = leafWriterFlush(v, pWriter);
+    if( rc!=SQLITE_OK ) return rc;
+  }
+
+  /* We must have flushed a leaf at some point. */
+  assert( pWriter->has_parent );
+
+  /* Tenatively set the end leaf blockid as the end blockid.  If the
+  ** interior node can be returned inline, this will be the final
+  ** blockid, otherwise it will be overwritten by
+  ** interiorWriterRootInfo().
+  */
+  *piEndBlockid = pWriter->iEndBlockid;
+
+  return interiorWriterRootInfo(v, &pWriter->parentWriter,
+                                ppRootInfo, pnRootInfo, piEndBlockid);
+}
+
+/* Collect the rootInfo data and store it into the segment directory.
+** This has the effect of flushing the segment's leaf data to
+** %_segments, and also flushing any interior nodes to %_segments.
 */
-typedef struct TokenDoclist TokenDoclist;
-struct TokenDoclist {
-  int bIgnore;
-  sqlite3_int64 iDocid;
-  char *pList;
-  int nList;
-};
+static int leafWriterFinalize(fulltext_vtab *v, LeafWriter *pWriter){
+  sqlite_int64 iEndBlockid;
+  char *pRootInfo;
+  int rc, nRootInfo;
 
-/*
-** Token pToken is an incrementally loaded token that is part of a 
-** multi-token phrase. Advance it to the next matching document in the
-** database and populate output variable *p with the details of the new
-** entry. Or, if the iterator has reached EOF, set *pbEof to true.
-**
-** If an error occurs, return an SQLite error code. Otherwise, return 
-** SQLITE_OK.
-*/
-static int incrPhraseTokenNext(
-  Fts3Table *pTab,                /* Virtual table handle */
-  Fts3Phrase *pPhrase,            /* Phrase to advance token of */
-  int iToken,                     /* Specific token to advance */
-  TokenDoclist *p,                /* OUT: Docid and doclist for new entry */
-  u8 *pbEof                       /* OUT: True if iterator is at EOF */
-){
-  int rc = SQLITE_OK;
+  rc = leafWriterRootInfo(v, pWriter, &pRootInfo, &nRootInfo, &iEndBlockid);
+  if( rc!=SQLITE_OK ) return rc;
 
-  if( pPhrase->iDoclistToken==iToken ){
-    assert( p->bIgnore==0 );
-    assert( pPhrase->aToken[iToken].pSegcsr==0 );
-    fts3EvalDlPhraseNext(pTab, &pPhrase->doclist, pbEof);
-    p->pList = pPhrase->doclist.pList;
-    p->nList = pPhrase->doclist.nList;
-    p->iDocid = pPhrase->doclist.iDocid;
+  /* Don't bother storing an entirely empty segment. */
+  if( iEndBlockid==0 && nRootInfo==0 ) return SQLITE_OK;
+
+  return segdir_set(v, pWriter->iLevel, pWriter->idx,
+                    pWriter->iStartBlockid, pWriter->iEndBlockid,
+                    iEndBlockid, pRootInfo, nRootInfo);
+}
+
+static void leafWriterDestroy(LeafWriter *pWriter){
+  if( pWriter->has_parent ) interiorWriterDestroy(&pWriter->parentWriter);
+  dataBufferDestroy(&pWriter->term);
+  dataBufferDestroy(&pWriter->data);
+}
+
+/* Encode a term into the leafWriter, delta-encoding as appropriate.
+** Returns the length of the new term which distinguishes it from the
+** previous term, which can be used to set nTermDistinct when a node
+** boundary is crossed.
+*/
+static int leafWriterEncodeTerm(LeafWriter *pWriter,
+                                const char *pTerm, int nTerm){
+  char c[VARINT_MAX+VARINT_MAX];
+  int n, nPrefix = 0;
+
+  assert( nTerm>0 );
+  while( nPrefix<pWriter->term.nData &&
+         pTerm[nPrefix]==pWriter->term.pData[nPrefix] ){
+    nPrefix++;
+    /* Failing this implies that the terms weren't in order. */
+    assert( nPrefix<nTerm );
+  }
+
+  if( pWriter->data.nData==0 ){
+    /* Encode the node header and leading term as:
+    **  varint(0)
+    **  varint(nTerm)
+    **  char pTerm[nTerm]
+    */
+    n = fts3PutVarint(c, '\0');
+    n += fts3PutVarint(c+n, nTerm);
+    dataBufferAppend2(&pWriter->data, c, n, pTerm, nTerm);
   }else{
-    Fts3PhraseToken *pToken = &pPhrase->aToken[iToken];
-    assert( pToken->pDeferred==0 );
-    assert( pToken->pSegcsr || pPhrase->iDoclistToken>=0 );
-    if( pToken->pSegcsr ){
-      assert( p->bIgnore==0 );
-      rc = sqlite3Fts3MsrIncrNext(
-          pTab, pToken->pSegcsr, &p->iDocid, &p->pList, &p->nList
-      );
-      if( p->pList==0 ) *pbEof = 1;
-    }else{
-      p->bIgnore = 1;
+    /* Delta-encode the term as:
+    **  varint(nPrefix)
+    **  varint(nSuffix)
+    **  char pTermSuffix[nSuffix]
+    */
+    n = fts3PutVarint(c, nPrefix);
+    n += fts3PutVarint(c+n, nTerm-nPrefix);
+    dataBufferAppend2(&pWriter->data, c, n, pTerm+nPrefix, nTerm-nPrefix);
+  }
+  dataBufferReplace(&pWriter->term, pTerm, nTerm);
+
+  return nPrefix+1;
+}
+
+/* Used to avoid a memmove when a large amount of doclist data is in
+** the buffer.  This constructs a node and term header before
+** iDoclistData and flushes the resulting complete node using
+** leafWriterInternalFlush().
+*/
+static int leafWriterInlineFlush(fulltext_vtab *v, LeafWriter *pWriter,
+                                 const char *pTerm, int nTerm,
+                                 int iDoclistData){
+  char c[VARINT_MAX+VARINT_MAX];
+  int iData, n = fts3PutVarint(c, 0);
+  n += fts3PutVarint(c+n, nTerm);
+
+  /* There should always be room for the header.  Even if pTerm shared
+  ** a substantial prefix with the previous term, the entire prefix
+  ** could be constructed from earlier data in the doclist, so there
+  ** should be room.
+  */
+  assert( iDoclistData>=n+nTerm );
+
+  iData = iDoclistData-(n+nTerm);
+  memcpy(pWriter->data.pData+iData, c, n);
+  memcpy(pWriter->data.pData+iData+n, pTerm, nTerm);
+
+  return leafWriterInternalFlush(v, pWriter, iData, pWriter->data.nData-iData);
+}
+
+/* Push pTerm[nTerm] along with the doclist data to the leaf layer of
+** %_segments.
+*/
+static int leafWriterStepMerge(fulltext_vtab *v, LeafWriter *pWriter,
+                               const char *pTerm, int nTerm,
+                               DLReader *pReaders, int nReaders){
+  char c[VARINT_MAX+VARINT_MAX];
+  int iTermData = pWriter->data.nData, iDoclistData;
+  int i, nData, n, nActualData, nActual, rc, nTermDistinct;
+
+  ASSERT_VALID_LEAF_NODE(pWriter->data.pData, pWriter->data.nData);
+  nTermDistinct = leafWriterEncodeTerm(pWriter, pTerm, nTerm);
+
+  /* Remember nTermDistinct if opening a new node. */
+  if( iTermData==0 ) pWriter->nTermDistinct = nTermDistinct;
+
+  iDoclistData = pWriter->data.nData;
+
+  /* Estimate the length of the merged doclist so we can leave space
+  ** to encode it.
+  */
+  for(i=0, nData=0; i<nReaders; i++){
+    nData += dlrAllDataBytes(&pReaders[i]);
+  }
+  n = fts3PutVarint(c, nData);
+  dataBufferAppend(&pWriter->data, c, n);
+
+  docListMerge(&pWriter->data, pReaders, nReaders);
+  ASSERT_VALID_DOCLIST(DL_DEFAULT,
+                       pWriter->data.pData+iDoclistData+n,
+                       pWriter->data.nData-iDoclistData-n, NULL);
+
+  /* The actual amount of doclist data at this point could be smaller
+  ** than the length we encoded.  Additionally, the space required to
+  ** encode this length could be smaller.  For small doclists, this is
+  ** not a big deal, we can just use memmove() to adjust things.
+  */
+  nActualData = pWriter->data.nData-(iDoclistData+n);
+  nActual = fts3PutVarint(c, nActualData);
+  assert( nActualData<=nData );
+  assert( nActual<=n );
+
+  /* If the new doclist is big enough for force a standalone leaf
+  ** node, we can immediately flush it inline without doing the
+  ** memmove().
+  */
+  /* TODO(shess) This test matches leafWriterStep(), which does this
+  ** test before it knows the cost to varint-encode the term and
+  ** doclist lengths.  At some point, change to
+  ** pWriter->data.nData-iTermData>STANDALONE_MIN.
+  */
+  if( nTerm+nActualData>STANDALONE_MIN ){
+    /* Push leaf node from before this term. */
+    if( iTermData>0 ){
+      rc = leafWriterInternalFlush(v, pWriter, 0, iTermData);
+      if( rc!=SQLITE_OK ) return rc;
+
+      pWriter->nTermDistinct = nTermDistinct;
     }
+
+    /* Fix the encoded doclist length. */
+    iDoclistData += n - nActual;
+    memcpy(pWriter->data.pData+iDoclistData, c, nActual);
+
+    /* Push the standalone leaf node. */
+    rc = leafWriterInlineFlush(v, pWriter, pTerm, nTerm, iDoclistData);
+    if( rc!=SQLITE_OK ) return rc;
+
+    /* Leave the node empty. */
+    dataBufferReset(&pWriter->data);
+
+    return rc;
+  }
+
+  /* At this point, we know that the doclist was small, so do the
+  ** memmove if indicated.
+  */
+  if( nActual<n ){
+    memmove(pWriter->data.pData+iDoclistData+nActual,
+            pWriter->data.pData+iDoclistData+n,
+            pWriter->data.nData-(iDoclistData+n));
+    pWriter->data.nData -= n-nActual;
+  }
+
+  /* Replace written length with actual length. */
+  memcpy(pWriter->data.pData+iDoclistData, c, nActual);
+
+  /* If the node is too large, break things up. */
+  /* TODO(shess) This test matches leafWriterStep(), which does this
+  ** test before it knows the cost to varint-encode the term and
+  ** doclist lengths.  At some point, change to
+  ** pWriter->data.nData>LEAF_MAX.
+  */
+  if( iTermData+nTerm+nActualData>LEAF_MAX ){
+    /* Flush out the leading data as a node */
+    rc = leafWriterInternalFlush(v, pWriter, 0, iTermData);
+    if( rc!=SQLITE_OK ) return rc;
+
+    pWriter->nTermDistinct = nTermDistinct;
+
+    /* Rebuild header using the current term */
+    n = fts3PutVarint(pWriter->data.pData, 0);
+    n += fts3PutVarint(pWriter->data.pData+n, nTerm);
+    memcpy(pWriter->data.pData+n, pTerm, nTerm);
+    n += nTerm;
+
+    /* There should always be room, because the previous encoding
+    ** included all data necessary to construct the term.
+    */
+    assert( n<iDoclistData );
+    /* So long as STANDALONE_MIN is half or less of LEAF_MAX, the
+    ** following memcpy() is safe (as opposed to needing a memmove).
+    */
+    assert( 2*STANDALONE_MIN<=LEAF_MAX );
+    assert( n+pWriter->data.nData-iDoclistData<iDoclistData );
+    memcpy(pWriter->data.pData+n,
+           pWriter->data.pData+iDoclistData,
+           pWriter->data.nData-iDoclistData);
+    pWriter->data.nData -= iDoclistData-n;
   }
+  ASSERT_VALID_LEAF_NODE(pWriter->data.pData, pWriter->data.nData);
+
+  return SQLITE_OK;
+}
+
+/* Push pTerm[nTerm] along with the doclist data to the leaf layer of
+** %_segments.
+*/
+/* TODO(shess) Revise writeZeroSegment() so that doclists are
+** constructed directly in pWriter->data.
+*/
+static int leafWriterStep(fulltext_vtab *v, LeafWriter *pWriter,
+                          const char *pTerm, int nTerm,
+                          const char *pData, int nData){
+  int rc;
+  DLReader reader;
+
+  dlrInit(&reader, DL_DEFAULT, pData, nData);
+  rc = leafWriterStepMerge(v, pWriter, pTerm, nTerm, &reader, 1);
+  dlrDestroy(&reader);
 
   return rc;
 }
 
 
-/*
-** The phrase iterator passed as the second argument:
-**
-**   * features at least one token that uses an incremental doclist, and 
-**
-**   * does not contain any deferred tokens.
-**
-** Advance it to the next matching documnent in the database and populate
-** the Fts3Doclist.pList and nList fields. 
-**
-** If there is no "next" entry and no error occurs, then *pbEof is set to
-** 1 before returning. Otherwise, if no error occurs and the iterator is
-** successfully advanced, *pbEof is set to 0.
+/****************************************************************/
+/* LeafReader is used to iterate over an individual leaf node. */
+typedef struct LeafReader {
+  DataBuffer term;          /* copy of current term. */
+
+  const char *pData;        /* data for current term. */
+  int nData;
+} LeafReader;
+
+static void leafReaderDestroy(LeafReader *pReader){
+  dataBufferDestroy(&pReader->term);
+  SCRAMBLE(pReader);
+}
+
+static int leafReaderAtEnd(LeafReader *pReader){
+  return pReader->nData<=0;
+}
+
+/* Access the current term. */
+static int leafReaderTermBytes(LeafReader *pReader){
+  return pReader->term.nData;
+}
+static const char *leafReaderTerm(LeafReader *pReader){
+  assert( pReader->term.nData>0 );
+  return pReader->term.pData;
+}
+
+/* Access the doclist data for the current term. */
+static int leafReaderDataBytes(LeafReader *pReader){
+  int nData;
+  assert( pReader->term.nData>0 );
+  fts3GetVarint32(pReader->pData, &nData);
+  return nData;
+}
+static const char *leafReaderData(LeafReader *pReader){
+  int n, nData;
+  assert( pReader->term.nData>0 );
+  n = fts3GetVarint32(pReader->pData, &nData);
+  return pReader->pData+n;
+}
+
+static void leafReaderInit(const char *pData, int nData,
+                           LeafReader *pReader){
+  int nTerm, n;
+
+  assert( nData>0 );
+  assert( pData[0]=='\0' );
+
+  CLEAR(pReader);
+
+  /* Read the first term, skipping the header byte. */
+  n = fts3GetVarint32(pData+1, &nTerm);
+  dataBufferInit(&pReader->term, nTerm);
+  dataBufferReplace(&pReader->term, pData+1+n, nTerm);
+
+  /* Position after the first term. */
+  assert( 1+n+nTerm<nData );
+  pReader->pData = pData+1+n+nTerm;
+  pReader->nData = nData-1-n-nTerm;
+}
+
+/* Step the reader forward to the next term. */
+static void leafReaderStep(LeafReader *pReader){
+  int n, nData, nPrefix, nSuffix;
+  assert( !leafReaderAtEnd(pReader) );
+
+  /* Skip previous entry's data block. */
+  n = fts3GetVarint32(pReader->pData, &nData);
+  assert( n+nData<=pReader->nData );
+  pReader->pData += n+nData;
+  pReader->nData -= n+nData;
+
+  if( !leafReaderAtEnd(pReader) ){
+    /* Construct the new term using a prefix from the old term plus a
+    ** suffix from the leaf data.
+    */
+    n = fts3GetVarint32(pReader->pData, &nPrefix);
+    n += fts3GetVarint32(pReader->pData+n, &nSuffix);
+    assert( n+nSuffix<pReader->nData );
+    pReader->term.nData = nPrefix;
+    dataBufferAppend(&pReader->term, pReader->pData+n, nSuffix);
+
+    pReader->pData += n+nSuffix;
+    pReader->nData -= n+nSuffix;
+  }
+}
+
+/* strcmp-style comparison of pReader's current term against pTerm.
+** If isPrefix, equality means equal through nTerm bytes.
+*/
+static int leafReaderTermCmp(LeafReader *pReader,
+                             const char *pTerm, int nTerm, int isPrefix){
+  int c, n = pReader->term.nData<nTerm ? pReader->term.nData : nTerm;
+  if( n==0 ){
+    if( pReader->term.nData>0 ) return -1;
+    if(nTerm>0 ) return 1;
+    return 0;
+  }
+
+  c = memcmp(pReader->term.pData, pTerm, n);
+  if( c!=0 ) return c;
+  if( isPrefix && n==nTerm ) return 0;
+  return pReader->term.nData - nTerm;
+}
+
+
+/****************************************************************/
+/* LeavesReader wraps LeafReader to allow iterating over the entire
+** leaf layer of the tree.
+*/
+typedef struct LeavesReader {
+  int idx;                  /* Index within the segment. */
+
+  sqlite3_stmt *pStmt;      /* Statement we're streaming leaves from. */
+  int eof;                  /* we've seen SQLITE_DONE from pStmt. */
+
+  LeafReader leafReader;    /* reader for the current leaf. */
+  DataBuffer rootData;      /* root data for inline. */
+} LeavesReader;
+
+/* Access the current term. */
+static int leavesReaderTermBytes(LeavesReader *pReader){
+  assert( !pReader->eof );
+  return leafReaderTermBytes(&pReader->leafReader);
+}
+static const char *leavesReaderTerm(LeavesReader *pReader){
+  assert( !pReader->eof );
+  return leafReaderTerm(&pReader->leafReader);
+}
+
+/* Access the doclist data for the current term. */
+static int leavesReaderDataBytes(LeavesReader *pReader){
+  assert( !pReader->eof );
+  return leafReaderDataBytes(&pReader->leafReader);
+}
+static const char *leavesReaderData(LeavesReader *pReader){
+  assert( !pReader->eof );
+  return leafReaderData(&pReader->leafReader);
+}
+
+static int leavesReaderAtEnd(LeavesReader *pReader){
+  return pReader->eof;
+}
+
+/* loadSegmentLeaves() may not read all the way to SQLITE_DONE, thus
+** leaving the statement handle open, which locks the table.
+*/
+/* TODO(shess) This "solution" is not satisfactory.  Really, there
+** should be check-in function for all statement handles which
+** arranges to call sqlite3_reset().  This most likely will require
+** modification to control flow all over the place, though, so for now
+** just punt.
 **
-** If an error occurs, return an SQLite error code. Otherwise, return 
-** SQLITE_OK.
+** Note the the current system assumes that segment merges will run to
+** completion, which is why this particular probably hasn't arisen in
+** this case.  Probably a brittle assumption.
 */
-static int fts3EvalIncrPhraseNext(
-  Fts3Cursor *pCsr,               /* FTS Cursor handle */
-  Fts3Phrase *p,                  /* Phrase object to advance to next docid */
-  u8 *pbEof                       /* OUT: Set to 1 if EOF */
-){
-  int rc = SQLITE_OK;
-  Fts3Doclist *pDL = &p->doclist;
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-  u8 bEof = 0;
-
-  /* This is only called if it is guaranteed that the phrase has at least
-  ** one incremental token. In which case the bIncr flag is set. */
-  assert( p->bIncr==1 );
-
-  if( p->nToken==1 ){
-    rc = sqlite3Fts3MsrIncrNext(pTab, p->aToken[0].pSegcsr, 
-        &pDL->iDocid, &pDL->pList, &pDL->nList
-    );
-    if( pDL->pList==0 ) bEof = 1;
+static int leavesReaderReset(LeavesReader *pReader){
+  return sqlite3_reset(pReader->pStmt);
+}
+
+static void leavesReaderDestroy(LeavesReader *pReader){
+  /* If idx is -1, that means we're using a non-cached statement
+  ** handle in the optimize() case, so we need to release it.
+  */
+  if( pReader->pStmt!=NULL && pReader->idx==-1 ){
+    sqlite3_finalize(pReader->pStmt);
+  }
+  leafReaderDestroy(&pReader->leafReader);
+  dataBufferDestroy(&pReader->rootData);
+  SCRAMBLE(pReader);
+}
+
+/* Initialize pReader with the given root data (if iStartBlockid==0
+** the leaf data was entirely contained in the root), or from the
+** stream of blocks between iStartBlockid and iEndBlockid, inclusive.
+*/
+static int leavesReaderInit(fulltext_vtab *v,
+                            int idx,
+                            sqlite_int64 iStartBlockid,
+                            sqlite_int64 iEndBlockid,
+                            const char *pRootData, int nRootData,
+                            LeavesReader *pReader){
+  CLEAR(pReader);
+  pReader->idx = idx;
+
+  dataBufferInit(&pReader->rootData, 0);
+  if( iStartBlockid==0 ){
+    /* Entire leaf level fit in root data. */
+    dataBufferReplace(&pReader->rootData, pRootData, nRootData);
+    leafReaderInit(pReader->rootData.pData, pReader->rootData.nData,
+                   &pReader->leafReader);
   }else{
-    int bDescDoclist = pCsr->bDesc;
-    struct TokenDoclist a[MAX_INCR_PHRASE_TOKENS];
+    sqlite3_stmt *s;
+    int rc = sql_get_leaf_statement(v, idx, &s);
+    if( rc!=SQLITE_OK ) return rc;
 
-    memset(a, 0, sizeof(a));
-    assert( p->nToken<=MAX_INCR_PHRASE_TOKENS );
-    assert( p->iDoclistToken<MAX_INCR_PHRASE_TOKENS );
-
-    while( bEof==0 ){
-      int bMaxSet = 0;
-      sqlite3_int64 iMax = 0;     /* Largest docid for all iterators */
-      int i;                      /* Used to iterate through tokens */
-
-      /* Advance the iterator for each token in the phrase once. */
-      for(i=0; rc==SQLITE_OK && i<p->nToken && bEof==0; i++){
-        rc = incrPhraseTokenNext(pTab, p, i, &a[i], &bEof);
-        if( a[i].bIgnore==0 && (bMaxSet==0 || DOCID_CMP(iMax, a[i].iDocid)<0) ){
-          iMax = a[i].iDocid;
-          bMaxSet = 1;
-        }
-      }
-      assert( rc!=SQLITE_OK || (p->nToken>=1 && a[p->nToken-1].bIgnore==0) );
-      assert( rc!=SQLITE_OK || bMaxSet );
+    rc = sqlite3_bind_int64(s, 1, iStartBlockid);
+    if( rc!=SQLITE_OK ) return rc;
+
+    rc = sqlite3_bind_int64(s, 2, iEndBlockid);
+    if( rc!=SQLITE_OK ) return rc;
+
+    rc = sqlite3_step(s);
+    if( rc==SQLITE_DONE ){
+      pReader->eof = 1;
+      return SQLITE_OK;
+    }
+    if( rc!=SQLITE_ROW ) return rc;
+
+    pReader->pStmt = s;
+    leafReaderInit(sqlite3_column_blob(pReader->pStmt, 0),
+                   sqlite3_column_bytes(pReader->pStmt, 0),
+                   &pReader->leafReader);
+  }
+  return SQLITE_OK;
+}
+
+/* Step the current leaf forward to the next term.  If we reach the
+** end of the current leaf, step forward to the next leaf block.
+*/
+static int leavesReaderStep(fulltext_vtab *v, LeavesReader *pReader){
+  assert( !leavesReaderAtEnd(pReader) );
+  leafReaderStep(&pReader->leafReader);
+
+  if( leafReaderAtEnd(&pReader->leafReader) ){
+    int rc;
+    if( pReader->rootData.pData ){
+      pReader->eof = 1;
+      return SQLITE_OK;
+    }
+    rc = sqlite3_step(pReader->pStmt);
+    if( rc!=SQLITE_ROW ){
+      pReader->eof = 1;
+      return rc==SQLITE_DONE ? SQLITE_OK : rc;
+    }
+    leafReaderDestroy(&pReader->leafReader);
+    leafReaderInit(sqlite3_column_blob(pReader->pStmt, 0),
+                   sqlite3_column_bytes(pReader->pStmt, 0),
+                   &pReader->leafReader);
+  }
+  return SQLITE_OK;
+}
+
+/* Order LeavesReaders by their term, ignoring idx.  Readers at eof
+** always sort to the end.
+*/
+static int leavesReaderTermCmp(LeavesReader *lr1, LeavesReader *lr2){
+  if( leavesReaderAtEnd(lr1) ){
+    if( leavesReaderAtEnd(lr2) ) return 0;
+    return 1;
+  }
+  if( leavesReaderAtEnd(lr2) ) return -1;
+
+  return leafReaderTermCmp(&lr1->leafReader,
+                           leavesReaderTerm(lr2), leavesReaderTermBytes(lr2),
+                           0);
+}
+
+/* Similar to leavesReaderTermCmp(), with additional ordering by idx
+** so that older segments sort before newer segments.
+*/
+static int leavesReaderCmp(LeavesReader *lr1, LeavesReader *lr2){
+  int c = leavesReaderTermCmp(lr1, lr2);
+  if( c!=0 ) return c;
+  return lr1->idx-lr2->idx;
+}
+
+/* Assume that pLr[1]..pLr[nLr] are sorted.  Bubble pLr[0] into its
+** sorted position.
+*/
+static void leavesReaderReorder(LeavesReader *pLr, int nLr){
+  while( nLr>1 && leavesReaderCmp(pLr, pLr+1)>0 ){
+    LeavesReader tmp = pLr[0];
+    pLr[0] = pLr[1];
+    pLr[1] = tmp;
+    nLr--;
+    pLr++;
+  }
+}
+
+/* Initializes pReaders with the segments from level iLevel, returning
+** the number of segments in *piReaders.  Leaves pReaders in sorted
+** order.
+*/
+static int leavesReadersInit(fulltext_vtab *v, int iLevel,
+                             LeavesReader *pReaders, int *piReaders){
+  sqlite3_stmt *s;
+  int i, rc = sql_get_statement(v, SEGDIR_SELECT_LEVEL_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_bind_int(s, 1, iLevel);
+  if( rc!=SQLITE_OK ) return rc;
+
+  i = 0;
+  while( (rc = sqlite3_step(s))==SQLITE_ROW ){
+    sqlite_int64 iStart = sqlite3_column_int64(s, 0);
+    sqlite_int64 iEnd = sqlite3_column_int64(s, 1);
+    const char *pRootData = sqlite3_column_blob(s, 2);
+    int nRootData = sqlite3_column_bytes(s, 2);
+
+    assert( i<MERGE_COUNT );
+    rc = leavesReaderInit(v, i, iStart, iEnd, pRootData, nRootData,
+                          &pReaders[i]);
+    if( rc!=SQLITE_OK ) break;
+
+    i++;
+  }
+  if( rc!=SQLITE_DONE ){
+    while( i-->0 ){
+      leavesReaderDestroy(&pReaders[i]);
+    }
+    return rc;
+  }
+
+  *piReaders = i;
+
+  /* Leave our results sorted by term, then age. */
+  while( i-- ){
+    leavesReaderReorder(pReaders+i, *piReaders-i);
+  }
+  return SQLITE_OK;
+}
+
+/* Merge doclists from pReaders[nReaders] into a single doclist, which
+** is written to pWriter.  Assumes pReaders is ordered oldest to
+** newest.
+*/
+/* TODO(shess) Consider putting this inline in segmentMerge(). */
+static int leavesReadersMerge(fulltext_vtab *v,
+                              LeavesReader *pReaders, int nReaders,
+                              LeafWriter *pWriter){
+  DLReader dlReaders[MERGE_COUNT];
+  const char *pTerm = leavesReaderTerm(pReaders);
+  int i, nTerm = leavesReaderTermBytes(pReaders);
+
+  assert( nReaders<=MERGE_COUNT );
+
+  for(i=0; i<nReaders; i++){
+    dlrInit(&dlReaders[i], DL_DEFAULT,
+            leavesReaderData(pReaders+i),
+            leavesReaderDataBytes(pReaders+i));
+  }
+
+  return leafWriterStepMerge(v, pWriter, pTerm, nTerm, dlReaders, nReaders);
+}
+
+/* Forward ref due to mutual recursion with segdirNextIndex(). */
+static int segmentMerge(fulltext_vtab *v, int iLevel);
+
+/* Put the next available index at iLevel into *pidx.  If iLevel
+** already has MERGE_COUNT segments, they are merged to a higher
+** level to make room.
+*/
+static int segdirNextIndex(fulltext_vtab *v, int iLevel, int *pidx){
+  int rc = segdir_max_index(v, iLevel, pidx);
+  if( rc==SQLITE_DONE ){              /* No segments at iLevel. */
+    *pidx = 0;
+  }else if( rc==SQLITE_ROW ){
+    if( *pidx==(MERGE_COUNT-1) ){
+      rc = segmentMerge(v, iLevel);
+      if( rc!=SQLITE_OK ) return rc;
+      *pidx = 0;
+    }else{
+      (*pidx)++;
+    }
+  }else{
+    return rc;
+  }
+  return SQLITE_OK;
+}
+
+/* Merge MERGE_COUNT segments at iLevel into a new segment at
+** iLevel+1.  If iLevel+1 is already full of segments, those will be
+** merged to make room.
+*/
+static int segmentMerge(fulltext_vtab *v, int iLevel){
+  LeafWriter writer;
+  LeavesReader lrs[MERGE_COUNT];
+  int i, rc, idx = 0;
+
+  /* Determine the next available segment index at the next level,
+  ** merging as necessary.
+  */
+  rc = segdirNextIndex(v, iLevel+1, &idx);
+  if( rc!=SQLITE_OK ) return rc;
+
+  /* TODO(shess) This assumes that we'll always see exactly
+  ** MERGE_COUNT segments to merge at a given level.  That will be
+  ** broken if we allow the developer to request preemptive or
+  ** deferred merging.
+  */
+  memset(&lrs, '\0', sizeof(lrs));
+  rc = leavesReadersInit(v, iLevel, lrs, &i);
+  if( rc!=SQLITE_OK ) return rc;
+  assert( i==MERGE_COUNT );
+
+  leafWriterInit(iLevel+1, idx, &writer);
+
+  /* Since leavesReaderReorder() pushes readers at eof to the end,
+  ** when the first reader is empty, all will be empty.
+  */
+  while( !leavesReaderAtEnd(lrs) ){
+    /* Figure out how many readers share their next term. */
+    for(i=1; i<MERGE_COUNT && !leavesReaderAtEnd(lrs+i); i++){
+      if( 0!=leavesReaderTermCmp(lrs, lrs+i) ) break;
+    }
+
+    rc = leavesReadersMerge(v, lrs, i, &writer);
+    if( rc!=SQLITE_OK ) goto err;
+
+    /* Step forward those that were merged. */
+    while( i-->0 ){
+      rc = leavesReaderStep(v, lrs+i);
+      if( rc!=SQLITE_OK ) goto err;
+
+      /* Reorder by term, then by age. */
+      leavesReaderReorder(lrs+i, MERGE_COUNT-i);
+    }
+  }
+
+  for(i=0; i<MERGE_COUNT; i++){
+    leavesReaderDestroy(&lrs[i]);
+  }
+
+  rc = leafWriterFinalize(v, &writer);
+  leafWriterDestroy(&writer);
+  if( rc!=SQLITE_OK ) return rc;
+
+  /* Delete the merged segment data. */
+  return segdir_delete(v, iLevel);
+
+ err:
+  for(i=0; i<MERGE_COUNT; i++){
+    leavesReaderDestroy(&lrs[i]);
+  }
+  leafWriterDestroy(&writer);
+  return rc;
+}
+
+/* Accumulate the union of *acc and *pData into *acc. */
+static void docListAccumulateUnion(DataBuffer *acc,
+                                   const char *pData, int nData) {
+  DataBuffer tmp = *acc;
+  dataBufferInit(acc, tmp.nData+nData);
+  docListUnion(tmp.pData, tmp.nData, pData, nData, acc);
+  dataBufferDestroy(&tmp);
+}
+
+/* TODO(shess) It might be interesting to explore different merge
+** strategies, here.  For instance, since this is a sorted merge, we
+** could easily merge many doclists in parallel.  With some
+** comprehension of the storage format, we could merge all of the
+** doclists within a leaf node directly from the leaf node's storage.
+** It may be worthwhile to merge smaller doclists before larger
+** doclists, since they can be traversed more quickly - but the
+** results may have less overlap, making them more expensive in a
+** different way.
+*/
+
+/* Scan pReader for pTerm/nTerm, and merge the term's doclist over
+** *out (any doclists with duplicate docids overwrite those in *out).
+** Internal function for loadSegmentLeaf().
+*/
+static int loadSegmentLeavesInt(fulltext_vtab *v, LeavesReader *pReader,
+                                const char *pTerm, int nTerm, int isPrefix,
+                                DataBuffer *out){
+  /* doclist data is accumulated into pBuffers similar to how one does
+  ** increment in binary arithmetic.  If index 0 is empty, the data is
+  ** stored there.  If there is data there, it is merged and the
+  ** results carried into position 1, with further merge-and-carry
+  ** until an empty position is found.
+  */
+  DataBuffer *pBuffers = NULL;
+  int nBuffers = 0, nMaxBuffers = 0, rc;
+
+  assert( nTerm>0 );
+
+  for(rc=SQLITE_OK; rc==SQLITE_OK && !leavesReaderAtEnd(pReader);
+      rc=leavesReaderStep(v, pReader)){
+    /* TODO(shess) Really want leavesReaderTermCmp(), but that name is
+    ** already taken to compare the terms of two LeavesReaders.  Think
+    ** on a better name.  [Meanwhile, break encapsulation rather than
+    ** use a confusing name.]
+    */
+    int c = leafReaderTermCmp(&pReader->leafReader, pTerm, nTerm, isPrefix);
+    if( c>0 ) break;      /* Past any possible matches. */
+    if( c==0 ){
+      const char *pData = leavesReaderData(pReader);
+      int iBuffer, nData = leavesReaderDataBytes(pReader);
+
+      /* Find the first empty buffer. */
+      for(iBuffer=0; iBuffer<nBuffers; ++iBuffer){
+        if( 0==pBuffers[iBuffer].nData ) break;
+      }
+
+      /* Out of buffers, add an empty one. */
+      if( iBuffer==nBuffers ){
+        if( nBuffers==nMaxBuffers ){
+          DataBuffer *p;
+          nMaxBuffers += 20;
+
+          /* Manual realloc so we can handle NULL appropriately. */
+          p = sqlite3_malloc(nMaxBuffers*sizeof(*pBuffers));
+          if( p==NULL ){
+            rc = SQLITE_NOMEM;
+            break;
+          }
 
-      /* Keep advancing iterators until they all point to the same document */
-      for(i=0; i<p->nToken; i++){
-        while( rc==SQLITE_OK && bEof==0 
-            && a[i].bIgnore==0 && DOCID_CMP(a[i].iDocid, iMax)<0 
-        ){
-          rc = incrPhraseTokenNext(pTab, p, i, &a[i], &bEof);
-          if( DOCID_CMP(a[i].iDocid, iMax)>0 ){
-            iMax = a[i].iDocid;
-            i = 0;
+          if( nBuffers>0 ){
+            assert(pBuffers!=NULL);
+            memcpy(p, pBuffers, nBuffers*sizeof(*pBuffers));
+            sqlite3_free(pBuffers);
           }
+          pBuffers = p;
         }
+        dataBufferInit(&(pBuffers[nBuffers]), 0);
+        nBuffers++;
       }
 
-      /* Check if the current entries really are a phrase match */
-      if( bEof==0 ){
-        int nList = 0;
-        int nByte = a[p->nToken-1].nList;
-        char *aDoclist = sqlite3_malloc(nByte+1);
-        if( !aDoclist ) return SQLITE_NOMEM;
-        memcpy(aDoclist, a[p->nToken-1].pList, nByte+1);
-
-        for(i=0; i<(p->nToken-1); i++){
-          if( a[i].bIgnore==0 ){
-            char *pL = a[i].pList;
-            char *pR = aDoclist;
-            char *pOut = aDoclist;
-            int nDist = p->nToken-1-i;
-            int res = fts3PoslistPhraseMerge(&pOut, nDist, 0, 1, &pL, &pR);
-            if( res==0 ) break;
-            nList = (int)(pOut - aDoclist);
+      /* At this point, must have an empty at iBuffer. */
+      assert(iBuffer<nBuffers && pBuffers[iBuffer].nData==0);
+
+      /* If empty was first buffer, no need for merge logic. */
+      if( iBuffer==0 ){
+        dataBufferReplace(&(pBuffers[0]), pData, nData);
+      }else{
+        /* pAcc is the empty buffer the merged data will end up in. */
+        DataBuffer *pAcc = &(pBuffers[iBuffer]);
+        DataBuffer *p = &(pBuffers[0]);
+
+        /* Handle position 0 specially to avoid need to prime pAcc
+        ** with pData/nData.
+        */
+        dataBufferSwap(p, pAcc);
+        docListAccumulateUnion(pAcc, pData, nData);
+
+        /* Accumulate remaining doclists into pAcc. */
+        for(++p; p<pAcc; ++p){
+          docListAccumulateUnion(pAcc, p->pData, p->nData);
+
+          /* dataBufferReset() could allow a large doclist to blow up
+          ** our memory requirements.
+          */
+          if( p->nCapacity<1024 ){
+            dataBufferReset(p);
+          }else{
+            dataBufferDestroy(p);
+            dataBufferInit(p, 0);
           }
         }
-        if( i==(p->nToken-1) ){
-          pDL->iDocid = iMax;
-          pDL->pList = aDoclist;
-          pDL->nList = nList;
-          pDL->bFreeList = 1;
-          break;
+      }
+    }
+  }
+
+  /* Union all the doclists together into *out. */
+  /* TODO(shess) What if *out is big?  Sigh. */
+  if( rc==SQLITE_OK && nBuffers>0 ){
+    int iBuffer;
+    for(iBuffer=0; iBuffer<nBuffers; ++iBuffer){
+      if( pBuffers[iBuffer].nData>0 ){
+        if( out->nData==0 ){
+          dataBufferSwap(out, &(pBuffers[iBuffer]));
+        }else{
+          docListAccumulateUnion(out, pBuffers[iBuffer].pData,
+                                 pBuffers[iBuffer].nData);
         }
-        sqlite3_free(aDoclist);
       }
     }
   }
 
-  *pbEof = bEof;
+  while( nBuffers-- ){
+    dataBufferDestroy(&(pBuffers[nBuffers]));
+  }
+  if( pBuffers!=NULL ) sqlite3_free(pBuffers);
+
   return rc;
 }
 
-/*
-** Attempt to move the phrase iterator to point to the next matching docid. 
-** If an error occurs, return an SQLite error code. Otherwise, return 
-** SQLITE_OK.
-**
-** If there is no "next" entry and no error occurs, then *pbEof is set to
-** 1 before returning. Otherwise, if no error occurs and the iterator is
-** successfully advanced, *pbEof is set to 0.
-*/
-static int fts3EvalPhraseNext(
-  Fts3Cursor *pCsr,               /* FTS Cursor handle */
-  Fts3Phrase *p,                  /* Phrase object to advance to next docid */
-  u8 *pbEof                       /* OUT: Set to 1 if EOF */
-){
-  int rc = SQLITE_OK;
-  Fts3Doclist *pDL = &p->doclist;
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
+/* Call loadSegmentLeavesInt() with pData/nData as input. */
+static int loadSegmentLeaf(fulltext_vtab *v, const char *pData, int nData,
+                           const char *pTerm, int nTerm, int isPrefix,
+                           DataBuffer *out){
+  LeavesReader reader;
+  int rc;
 
-  if( p->bIncr ){
-    rc = fts3EvalIncrPhraseNext(pCsr, p, pbEof);
-  }else if( pCsr->bDesc!=pTab->bDescIdx && pDL->nAll ){
-    sqlite3Fts3DoclistPrev(pTab->bDescIdx, pDL->aAll, pDL->nAll, 
-        &pDL->pNextDocid, &pDL->iDocid, &pDL->nList, pbEof
-    );
-    pDL->pList = pDL->pNextDocid;
-  }else{
-    fts3EvalDlPhraseNext(pTab, pDL, pbEof);
-  }
+  assert( nData>1 );
+  assert( *pData=='\0' );
+  rc = leavesReaderInit(v, 0, 0, 0, pData, nData, &reader);
+  if( rc!=SQLITE_OK ) return rc;
 
+  rc = loadSegmentLeavesInt(v, &reader, pTerm, nTerm, isPrefix, out);
+  leavesReaderReset(&reader);
+  leavesReaderDestroy(&reader);
   return rc;
 }
 
-/*
-**
-** If *pRc is not SQLITE_OK when this function is called, it is a no-op.
-** Otherwise, fts3EvalPhraseStart() is called on all phrases within the
-** expression. Also the Fts3Expr.bDeferred variable is set to true for any
-** expressions for which all descendent tokens are deferred.
-**
-** If parameter bOptOk is zero, then it is guaranteed that the
-** Fts3Phrase.doclist.aAll/nAll variables contain the entire doclist for
-** each phrase in the expression (subject to deferred token processing).
-** Or, if bOptOk is non-zero, then one or more tokens within the expression
-** may be loaded incrementally, meaning doclist.aAll/nAll is not available.
-**
-** If an error occurs within this function, *pRc is set to an SQLite error
-** code before returning.
-*/
-static void fts3EvalStartReaders(
-  Fts3Cursor *pCsr,               /* FTS Cursor handle */
-  Fts3Expr *pExpr,                /* Expression to initialize phrases in */
-  int *pRc                        /* IN/OUT: Error code */
+/* Call loadSegmentLeavesInt() with the leaf nodes from iStartLeaf to
+** iEndLeaf (inclusive) as input, and merge the resulting doclist into
+** out.
+*/
+static int loadSegmentLeaves(fulltext_vtab *v,
+                             sqlite_int64 iStartLeaf, sqlite_int64 iEndLeaf,
+                             const char *pTerm, int nTerm, int isPrefix,
+                             DataBuffer *out){
+  int rc;
+  LeavesReader reader;
+
+  assert( iStartLeaf<=iEndLeaf );
+  rc = leavesReaderInit(v, 0, iStartLeaf, iEndLeaf, NULL, 0, &reader);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = loadSegmentLeavesInt(v, &reader, pTerm, nTerm, isPrefix, out);
+  leavesReaderReset(&reader);
+  leavesReaderDestroy(&reader);
+  return rc;
+}
+
+/* Taking pData/nData as an interior node, find the sequence of child
+** nodes which could include pTerm/nTerm/isPrefix.  Note that the
+** interior node terms logically come between the blocks, so there is
+** one more blockid than there are terms (that block contains terms >=
+** the last interior-node term).
+*/
+/* TODO(shess) The calling code may already know that the end child is
+** not worth calculating, because the end may be in a later sibling
+** node.  Consider whether breaking symmetry is worthwhile.  I suspect
+** it is not worthwhile.
+*/
+static void getChildrenContaining(const char *pData, int nData,
+                                  const char *pTerm, int nTerm, int isPrefix,
+                                  sqlite_int64 *piStartChild,
+                                  sqlite_int64 *piEndChild){
+  InteriorReader reader;
+
+  assert( nData>1 );
+  assert( *pData!='\0' );
+  interiorReaderInit(pData, nData, &reader);
+
+  /* Scan for the first child which could contain pTerm/nTerm. */
+  while( !interiorReaderAtEnd(&reader) ){
+    if( interiorReaderTermCmp(&reader, pTerm, nTerm, 0)>0 ) break;
+    interiorReaderStep(&reader);
+  }
+  *piStartChild = interiorReaderCurrentBlockid(&reader);
+
+  /* Keep scanning to find a term greater than our term, using prefix
+  ** comparison if indicated.  If isPrefix is false, this will be the
+  ** same blockid as the starting block.
+  */
+  while( !interiorReaderAtEnd(&reader) ){
+    if( interiorReaderTermCmp(&reader, pTerm, nTerm, isPrefix)>0 ) break;
+    interiorReaderStep(&reader);
+  }
+  *piEndChild = interiorReaderCurrentBlockid(&reader);
+
+  interiorReaderDestroy(&reader);
+
+  /* Children must ascend, and if !prefix, both must be the same. */
+  assert( *piEndChild>=*piStartChild );
+  assert( isPrefix || *piStartChild==*piEndChild );
+}
+
+/* Read block at iBlockid and pass it with other params to
+** getChildrenContaining().
+*/
+static int loadAndGetChildrenContaining(
+  fulltext_vtab *v,
+  sqlite_int64 iBlockid,
+  const char *pTerm, int nTerm, int isPrefix,
+  sqlite_int64 *piStartChild, sqlite_int64 *piEndChild
 ){
-  if( pExpr && SQLITE_OK==*pRc ){
-    if( pExpr->eType==FTSQUERY_PHRASE ){
-      int nToken = pExpr->pPhrase->nToken;
-      if( nToken ){
-        int i;
-        for(i=0; i<nToken; i++){
-          if( pExpr->pPhrase->aToken[i].pDeferred==0 ) break;
-        }
-        pExpr->bDeferred = (i==nToken);
-      }
-      *pRc = fts3EvalPhraseStart(pCsr, 1, pExpr->pPhrase);
-    }else{
-      fts3EvalStartReaders(pCsr, pExpr->pLeft, pRc);
-      fts3EvalStartReaders(pCsr, pExpr->pRight, pRc);
-      pExpr->bDeferred = (pExpr->pLeft->bDeferred && pExpr->pRight->bDeferred);
-    }
+  sqlite3_stmt *s = NULL;
+  int rc;
+
+  assert( iBlockid!=0 );
+  assert( pTerm!=NULL );
+  assert( nTerm!=0 );        /* TODO(shess) Why not allow this? */
+  assert( piStartChild!=NULL );
+  assert( piEndChild!=NULL );
+
+  rc = sql_get_statement(v, BLOCK_SELECT_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_bind_int64(s, 1, iBlockid);
+  if( rc!=SQLITE_OK ) return rc;
+
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_DONE ) return SQLITE_ERROR;
+  if( rc!=SQLITE_ROW ) return rc;
+
+  getChildrenContaining(sqlite3_column_blob(s, 0), sqlite3_column_bytes(s, 0),
+                        pTerm, nTerm, isPrefix, piStartChild, piEndChild);
+
+  /* We expect only one row.  We must execute another sqlite3_step()
+   * to complete the iteration; otherwise the table will remain
+   * locked. */
+  rc = sqlite3_step(s);
+  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
+  if( rc!=SQLITE_DONE ) return rc;
+
+  return SQLITE_OK;
+}
+
+/* Traverse the tree represented by pData[nData] looking for
+** pTerm[nTerm], placing its doclist into *out.  This is internal to
+** loadSegment() to make error-handling cleaner.
+*/
+static int loadSegmentInt(fulltext_vtab *v, const char *pData, int nData,
+                          sqlite_int64 iLeavesEnd,
+                          const char *pTerm, int nTerm, int isPrefix,
+                          DataBuffer *out){
+  /* Special case where root is a leaf. */
+  if( *pData=='\0' ){
+    return loadSegmentLeaf(v, pData, nData, pTerm, nTerm, isPrefix, out);
+  }else{
+    int rc;
+    sqlite_int64 iStartChild, iEndChild;
+
+    /* Process pData as an interior node, then loop down the tree
+    ** until we find the set of leaf nodes to scan for the term.
+    */
+    getChildrenContaining(pData, nData, pTerm, nTerm, isPrefix,
+                          &iStartChild, &iEndChild);
+    while( iStartChild>iLeavesEnd ){
+      sqlite_int64 iNextStart, iNextEnd;
+      rc = loadAndGetChildrenContaining(v, iStartChild, pTerm, nTerm, isPrefix,
+                                        &iNextStart, &iNextEnd);
+      if( rc!=SQLITE_OK ) return rc;
+
+      /* If we've branched, follow the end branch, too. */
+      if( iStartChild!=iEndChild ){
+        sqlite_int64 iDummy;
+        rc = loadAndGetChildrenContaining(v, iEndChild, pTerm, nTerm, isPrefix,
+                                          &iDummy, &iNextEnd);
+        if( rc!=SQLITE_OK ) return rc;
+      }
+
+      assert( iNextStart<=iNextEnd );
+      iStartChild = iNextStart;
+      iEndChild = iNextEnd;
+    }
+    assert( iStartChild<=iLeavesEnd );
+    assert( iEndChild<=iLeavesEnd );
+
+    /* Scan through the leaf segments for doclists. */
+    return loadSegmentLeaves(v, iStartChild, iEndChild,
+                             pTerm, nTerm, isPrefix, out);
   }
 }
 
-/*
-** An array of the following structures is assembled as part of the process
-** of selecting tokens to defer before the query starts executing (as part
-** of the xFilter() method). There is one element in the array for each
-** token in the FTS expression.
-**
-** Tokens are divided into AND/NEAR clusters. All tokens in a cluster belong
-** to phrases that are connected only by AND and NEAR operators (not OR or
-** NOT). When determining tokens to defer, each AND/NEAR cluster is considered
-** separately. The root of a tokens AND/NEAR cluster is stored in 
-** Fts3TokenAndCost.pRoot.
-*/
-typedef struct Fts3TokenAndCost Fts3TokenAndCost;
-struct Fts3TokenAndCost {
-  Fts3Phrase *pPhrase;            /* The phrase the token belongs to */
-  int iToken;                     /* Position of token in phrase */
-  Fts3PhraseToken *pToken;        /* The token itself */
-  Fts3Expr *pRoot;                /* Root of NEAR/AND cluster */
-  int nOvfl;                      /* Number of overflow pages to load doclist */
-  int iCol;                       /* The column the token must match */
-};
+/* Call loadSegmentInt() to collect the doclist for pTerm/nTerm, then
+** merge its doclist over *out (any duplicate doclists read from the
+** segment rooted at pData will overwrite those in *out).
+*/
+/* TODO(shess) Consider changing this to determine the depth of the
+** leaves using either the first characters of interior nodes (when
+** ==1, we're one level above the leaves), or the first character of
+** the root (which will describe the height of the tree directly).
+** Either feels somewhat tricky to me.
+*/
+/* TODO(shess) The current merge is likely to be slow for large
+** doclists (though it should process from newest/smallest to
+** oldest/largest, so it may not be that bad).  It might be useful to
+** modify things to allow for N-way merging.  This could either be
+** within a segment, with pairwise merges across segments, or across
+** all segments at once.
+*/
+static int loadSegment(fulltext_vtab *v, const char *pData, int nData,
+                       sqlite_int64 iLeavesEnd,
+                       const char *pTerm, int nTerm, int isPrefix,
+                       DataBuffer *out){
+  DataBuffer result;
+  int rc;
 
-/*
-** This function is used to populate an allocated Fts3TokenAndCost array.
-**
-** If *pRc is not SQLITE_OK when this function is called, it is a no-op.
-** Otherwise, if an error occurs during execution, *pRc is set to an
-** SQLite error code.
-*/
-static void fts3EvalTokenCosts(
-  Fts3Cursor *pCsr,               /* FTS Cursor handle */
-  Fts3Expr *pRoot,                /* Root of current AND/NEAR cluster */
-  Fts3Expr *pExpr,                /* Expression to consider */
-  Fts3TokenAndCost **ppTC,        /* Write new entries to *(*ppTC)++ */
-  Fts3Expr ***ppOr,               /* Write new OR root to *(*ppOr)++ */
-  int *pRc                        /* IN/OUT: Error code */
-){
-  if( *pRc==SQLITE_OK ){
-    if( pExpr->eType==FTSQUERY_PHRASE ){
-      Fts3Phrase *pPhrase = pExpr->pPhrase;
-      int i;
-      for(i=0; *pRc==SQLITE_OK && i<pPhrase->nToken; i++){
-        Fts3TokenAndCost *pTC = (*ppTC)++;
-        pTC->pPhrase = pPhrase;
-        pTC->iToken = i;
-        pTC->pRoot = pRoot;
-        pTC->pToken = &pPhrase->aToken[i];
-        pTC->iCol = pPhrase->iColumn;
-        *pRc = sqlite3Fts3MsrOvfl(pCsr, pTC->pToken->pSegcsr, &pTC->nOvfl);
-      }
-    }else if( pExpr->eType!=FTSQUERY_NOT ){
-      assert( pExpr->eType==FTSQUERY_OR
-           || pExpr->eType==FTSQUERY_AND
-           || pExpr->eType==FTSQUERY_NEAR
-      );
-      assert( pExpr->pLeft && pExpr->pRight );
-      if( pExpr->eType==FTSQUERY_OR ){
-        pRoot = pExpr->pLeft;
-        **ppOr = pRoot;
-        (*ppOr)++;
-      }
-      fts3EvalTokenCosts(pCsr, pRoot, pExpr->pLeft, ppTC, ppOr, pRc);
-      if( pExpr->eType==FTSQUERY_OR ){
-        pRoot = pExpr->pRight;
-        **ppOr = pRoot;
-        (*ppOr)++;
-      }
-      fts3EvalTokenCosts(pCsr, pRoot, pExpr->pRight, ppTC, ppOr, pRc);
+  assert( nData>1 );
+
+  /* This code should never be called with buffered updates. */
+  assert( v->nPendingData<0 );
+
+  dataBufferInit(&result, 0);
+  rc = loadSegmentInt(v, pData, nData, iLeavesEnd,
+                      pTerm, nTerm, isPrefix, &result);
+  if( rc==SQLITE_OK && result.nData>0 ){
+    if( out->nData==0 ){
+      DataBuffer tmp = *out;
+      *out = result;
+      result = tmp;
+    }else{
+      DataBuffer merged;
+      DLReader readers[2];
+
+      dlrInit(&readers[0], DL_DEFAULT, out->pData, out->nData);
+      dlrInit(&readers[1], DL_DEFAULT, result.pData, result.nData);
+      dataBufferInit(&merged, out->nData+result.nData);
+      docListMerge(&merged, readers, 2);
+      dataBufferDestroy(out);
+      *out = merged;
+      dlrDestroy(&readers[0]);
+      dlrDestroy(&readers[1]);
     }
   }
+  dataBufferDestroy(&result);
+  return rc;
 }
 
-/*
-** Determine the average document (row) size in pages. If successful,
-** write this value to *pnPage and return SQLITE_OK. Otherwise, return
-** an SQLite error code.
-**
-** The average document size in pages is calculated by first calculating 
-** determining the average size in bytes, B. If B is less than the amount
-** of data that will fit on a single leaf page of an intkey table in
-** this database, then the average docsize is 1. Otherwise, it is 1 plus
-** the number of overflow pages consumed by a record B bytes in size.
+/* Scan the database and merge together the posting lists for the term
+** into *out.
 */
-static int fts3EvalAverageDocsize(Fts3Cursor *pCsr, int *pnPage){
-  int rc = SQLITE_OK;
-  if( pCsr->nRowAvg==0 ){
-    /* The average document size, which is required to calculate the cost
-    ** of each doclist, has not yet been determined. Read the required 
-    ** data from the %_stat table to calculate it.
-    **
-    ** Entry 0 of the %_stat table is a blob containing (nCol+1) FTS3 
-    ** varints, where nCol is the number of columns in the FTS3 table.
-    ** The first varint is the number of documents currently stored in
-    ** the table. The following nCol varints contain the total amount of
-    ** data stored in all rows of each column of the table, from left
-    ** to right.
-    */
-    Fts3Table *p = (Fts3Table*)pCsr->base.pVtab;
-    sqlite3_stmt *pStmt;
-    sqlite3_int64 nDoc = 0;
-    sqlite3_int64 nByte = 0;
-    const char *pEnd;
-    const char *a;
+static int termSelect(
+  fulltext_vtab *v, 
+  int iColumn,
+  const char *pTerm, int nTerm,             /* Term to query for */
+  int isPrefix,                             /* True for a prefix search */
+  DocListType iType, 
+  DataBuffer *out                           /* Write results here */
+){
+  DataBuffer doclist;
+  sqlite3_stmt *s;
+  int rc = sql_get_statement(v, SEGDIR_SELECT_ALL_STMT, &s);
+  if( rc!=SQLITE_OK ) return rc;
 
-    rc = sqlite3Fts3SelectDoctotal(p, &pStmt);
-    if( rc!=SQLITE_OK ) return rc;
-    a = sqlite3_column_blob(pStmt, 0);
-    assert( a );
+  /* This code should never be called with buffered updates. */
+  assert( v->nPendingData<0 );
 
-    pEnd = &a[sqlite3_column_bytes(pStmt, 0)];
-    a += sqlite3Fts3GetVarint(a, &nDoc);
-    while( a<pEnd ){
-      a += sqlite3Fts3GetVarint(a, &nByte);
-    }
-    if( nDoc==0 || nByte==0 ){
-      sqlite3_reset(pStmt);
-      return FTS_CORRUPT_VTAB;
-    }
+  dataBufferInit(&doclist, 0);
+  dataBufferInit(out, 0);
 
-    pCsr->nDoc = nDoc;
-    pCsr->nRowAvg = (int)(((nByte / nDoc) + p->nPgsz) / p->nPgsz);
-    assert( pCsr->nRowAvg>0 ); 
-    rc = sqlite3_reset(pStmt);
+  /* Traverse the segments from oldest to newest so that newer doclist
+  ** elements for given docids overwrite older elements.
+  */
+  while( (rc = sqlite3_step(s))==SQLITE_ROW ){
+    const char *pData = sqlite3_column_blob(s, 2);
+    const int nData = sqlite3_column_bytes(s, 2);
+    const sqlite_int64 iLeavesEnd = sqlite3_column_int64(s, 1);
+    rc = loadSegment(v, pData, nData, iLeavesEnd, pTerm, nTerm, isPrefix,
+                     &doclist);
+    if( rc!=SQLITE_OK ) goto err;
+  }
+  if( rc==SQLITE_DONE ){
+    if( doclist.nData!=0 ){
+      /* TODO(shess) The old term_select_all() code applied the column
+      ** restrict as we merged segments, leading to smaller buffers.
+      ** This is probably worthwhile to bring back, once the new storage
+      ** system is checked in.
+      */
+      if( iColumn==v->nColumn) iColumn = -1;
+      docListTrim(DL_DEFAULT, doclist.pData, doclist.nData,
+                  iColumn, iType, out);
+    }
+    rc = SQLITE_OK;
   }
 
-  *pnPage = pCsr->nRowAvg;
+ err:
+  dataBufferDestroy(&doclist);
   return rc;
 }
 
-/*
-** This function is called to select the tokens (if any) that will be 
-** deferred. The array aTC[] has already been populated when this is
-** called.
-**
-** This function is called once for each AND/NEAR cluster in the 
-** expression. Each invocation determines which tokens to defer within
-** the cluster with root node pRoot. See comments above the definition
-** of struct Fts3TokenAndCost for more details.
-**
-** If no error occurs, SQLITE_OK is returned and sqlite3Fts3DeferToken()
-** called on each token to defer. Otherwise, an SQLite error code is
-** returned.
-*/
-static int fts3EvalSelectDeferred(
-  Fts3Cursor *pCsr,               /* FTS Cursor handle */
-  Fts3Expr *pRoot,                /* Consider tokens with this root node */
-  Fts3TokenAndCost *aTC,          /* Array of expression tokens and costs */
-  int nTC                         /* Number of entries in aTC[] */
-){
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-  int nDocSize = 0;               /* Number of pages per doc loaded */
-  int rc = SQLITE_OK;             /* Return code */
-  int ii;                         /* Iterator variable for various purposes */
-  int nOvfl = 0;                  /* Total overflow pages used by doclists */
-  int nToken = 0;                 /* Total number of tokens in cluster */
-
-  int nMinEst = 0;                /* The minimum count for any phrase so far. */
-  int nLoad4 = 1;                 /* (Phrases that will be loaded)^4. */
-
-  /* Tokens are never deferred for FTS tables created using the content=xxx
-  ** option. The reason being that it is not guaranteed that the content
-  ** table actually contains the same data as the index. To prevent this from
-  ** causing any problems, the deferred token optimization is completely
-  ** disabled for content=xxx tables. */
-  if( pTab->zContentTbl ){
-    return SQLITE_OK;
+/****************************************************************/
+/* Used to hold hashtable data for sorting. */
+typedef struct TermData {
+  const char *pTerm;
+  int nTerm;
+  DLCollector *pCollector;
+} TermData;
+
+/* Orders TermData elements in strcmp fashion ( <0 for less-than, 0
+** for equal, >0 for greater-than).
+*/
+static int termDataCmp(const void *av, const void *bv){
+  const TermData *a = (const TermData *)av;
+  const TermData *b = (const TermData *)bv;
+  int n = a->nTerm<b->nTerm ? a->nTerm : b->nTerm;
+  int c = memcmp(a->pTerm, b->pTerm, n);
+  if( c!=0 ) return c;
+  return a->nTerm-b->nTerm;
+}
+
+/* Order pTerms data by term, then write a new level 0 segment using
+** LeafWriter.
+*/
+static int writeZeroSegment(fulltext_vtab *v, fts3Hash *pTerms){
+  fts3HashElem *e;
+  int idx, rc, i, n;
+  TermData *pData;
+  LeafWriter writer;
+  DataBuffer dl;
+
+  /* Determine the next index at level 0, merging as necessary. */
+  rc = segdirNextIndex(v, 0, &idx);
+  if( rc!=SQLITE_OK ) return rc;
+
+  n = fts3HashCount(pTerms);
+  pData = sqlite3_malloc(n*sizeof(TermData));
+
+  for(i = 0, e = fts3HashFirst(pTerms); e; i++, e = fts3HashNext(e)){
+    assert( i<n );
+    pData[i].pTerm = fts3HashKey(e);
+    pData[i].nTerm = fts3HashKeysize(e);
+    pData[i].pCollector = fts3HashData(e);
   }
+  assert( i==n );
 
-  /* Count the tokens in this AND/NEAR cluster. If none of the doclists
-  ** associated with the tokens spill onto overflow pages, or if there is
-  ** only 1 token, exit early. No tokens to defer in this case. */
-  for(ii=0; ii<nTC; ii++){
-    if( aTC[ii].pRoot==pRoot ){
-      nOvfl += aTC[ii].nOvfl;
-      nToken++;
+  /* TODO(shess) Should we allow user-defined collation sequences,
+  ** here?  I think we only need that once we support prefix searches.
+  */
+  if( n>1 ) qsort(pData, n, sizeof(*pData), termDataCmp);
+
+  /* TODO(shess) Refactor so that we can write directly to the segment
+  ** DataBuffer, as happens for segment merges.
+  */
+  leafWriterInit(0, idx, &writer);
+  dataBufferInit(&dl, 0);
+  for(i=0; i<n; i++){
+    dataBufferReset(&dl);
+    dlcAddDoclist(pData[i].pCollector, &dl);
+    rc = leafWriterStep(v, &writer,
+                        pData[i].pTerm, pData[i].nTerm, dl.pData, dl.nData);
+    if( rc!=SQLITE_OK ) goto err;
+  }
+  rc = leafWriterFinalize(v, &writer);
+
+ err:
+  dataBufferDestroy(&dl);
+  sqlite3_free(pData);
+  leafWriterDestroy(&writer);
+  return rc;
+}
+
+/* If pendingTerms has data, free it. */
+static int clearPendingTerms(fulltext_vtab *v){
+  if( v->nPendingData>=0 ){
+    fts3HashElem *e;
+    for(e=fts3HashFirst(&v->pendingTerms); e; e=fts3HashNext(e)){
+      dlcDelete(fts3HashData(e));
     }
+    fts3HashClear(&v->pendingTerms);
+    v->nPendingData = -1;
   }
-  if( nOvfl==0 || nToken<2 ) return SQLITE_OK;
-
-  /* Obtain the average docsize (in pages). */
-  rc = fts3EvalAverageDocsize(pCsr, &nDocSize);
-  assert( rc!=SQLITE_OK || nDocSize>0 );
+  return SQLITE_OK;
+}
 
+/* If pendingTerms has data, flush it to a level-zero segment, and
+** free it.
+*/
+static int flushPendingTerms(fulltext_vtab *v){
+  if( v->nPendingData>=0 ){
+    int rc = writeZeroSegment(v, &v->pendingTerms);
+    if( rc==SQLITE_OK ) clearPendingTerms(v);
+    return rc;
+  }
+  return SQLITE_OK;
+}
 
-  /* Iterate through all tokens in this AND/NEAR cluster, in ascending order 
-  ** of the number of overflow pages that will be loaded by the pager layer 
-  ** to retrieve the entire doclist for the token from the full-text index.
-  ** Load the doclists for tokens that are either:
-  **
-  **   a. The cheapest token in the entire query (i.e. the one visited by the
-  **      first iteration of this loop), or
-  **
-  **   b. Part of a multi-token phrase.
-  **
-  ** After each token doclist is loaded, merge it with the others from the
-  ** same phrase and count the number of documents that the merged doclist
-  ** contains. Set variable "nMinEst" to the smallest number of documents in 
-  ** any phrase doclist for which 1 or more token doclists have been loaded.
-  ** Let nOther be the number of other phrases for which it is certain that
-  ** one or more tokens will not be deferred.
-  **
-  ** Then, for each token, defer it if loading the doclist would result in
-  ** loading N or more overflow pages into memory, where N is computed as:
-  **
-  **    (nMinEst + 4^nOther - 1) / (4^nOther)
+/* If pendingTerms is "too big", or docid is out of order, flush it.
+** Regardless, be certain that pendingTerms is initialized for use.
+*/
+static int initPendingTerms(fulltext_vtab *v, sqlite_int64 iDocid){
+  /* TODO(shess) Explore whether partially flushing the buffer on
+  ** forced-flush would provide better performance.  I suspect that if
+  ** we ordered the doclists by size and flushed the largest until the
+  ** buffer was half empty, that would let the less frequent terms
+  ** generate longer doclists.
   */
-  for(ii=0; ii<nToken && rc==SQLITE_OK; ii++){
-    int iTC;                      /* Used to iterate through aTC[] array. */
-    Fts3TokenAndCost *pTC = 0;    /* Set to cheapest remaining token. */
-
-    /* Set pTC to point to the cheapest remaining token. */
-    for(iTC=0; iTC<nTC; iTC++){
-      if( aTC[iTC].pToken && aTC[iTC].pRoot==pRoot 
-       && (!pTC || aTC[iTC].nOvfl<pTC->nOvfl) 
-      ){
-        pTC = &aTC[iTC];
-      }
-    }
-    assert( pTC );
+  if( iDocid<=v->iPrevDocid || v->nPendingData>kPendingThreshold ){
+    int rc = flushPendingTerms(v);
+    if( rc!=SQLITE_OK ) return rc;
+  }
+  if( v->nPendingData<0 ){
+    fts3HashInit(&v->pendingTerms, FTS3_HASH_STRING, 1);
+    v->nPendingData = 0;
+  }
+  v->iPrevDocid = iDocid;
+  return SQLITE_OK;
+}
+
+/* This function implements the xUpdate callback; it is the top-level entry
+ * point for inserting, deleting or updating a row in a full-text table. */
+static int fulltextUpdate(sqlite3_vtab *pVtab, int nArg, sqlite3_value **ppArg,
+                          sqlite_int64 *pRowid){
+  fulltext_vtab *v = (fulltext_vtab *) pVtab;
+  int rc;
+
+  FTSTRACE(("FTS3 Update %p\n", pVtab));
 
-    if( ii && pTC->nOvfl>=((nMinEst+(nLoad4/4)-1)/(nLoad4/4))*nDocSize ){
-      /* The number of overflow pages to load for this (and therefore all
-      ** subsequent) tokens is greater than the estimated number of pages 
-      ** that will be loaded if all subsequent tokens are deferred.
+  if( nArg<2 ){
+    rc = index_delete(v, sqlite3_value_int64(ppArg[0]));
+    if( rc==SQLITE_OK ){
+      /* If we just deleted the last row in the table, clear out the
+      ** index data.
       */
-      Fts3PhraseToken *pToken = pTC->pToken;
-      rc = sqlite3Fts3DeferToken(pCsr, pToken, pTC->iCol);
-      fts3SegReaderCursorFree(pToken->pSegcsr);
-      pToken->pSegcsr = 0;
-    }else{
-      /* Set nLoad4 to the value of (4^nOther) for the next iteration of the
-      ** for-loop. Except, limit the value to 2^24 to prevent it from 
-      ** overflowing the 32-bit integer it is stored in. */
-      if( ii<12 ) nLoad4 = nLoad4*4;
-
-      if( ii==0 || (pTC->pPhrase->nToken>1 && ii!=nToken-1) ){
-        /* Either this is the cheapest token in the entire query, or it is
-        ** part of a multi-token phrase. Either way, the entire doclist will
-        ** (eventually) be loaded into memory. It may as well be now. */
-        Fts3PhraseToken *pToken = pTC->pToken;
-        int nList = 0;
-        char *pList = 0;
-        rc = fts3TermSelect(pTab, pToken, pTC->iCol, &nList, &pList);
-        assert( rc==SQLITE_OK || pList==0 );
-        if( rc==SQLITE_OK ){
-          rc = fts3EvalPhraseMergeToken(
-              pTab, pTC->pPhrase, pTC->iToken,pList,nList
-          );
-        }
+      rc = content_exists(v);
+      if( rc==SQLITE_ROW ){
+        rc = SQLITE_OK;
+      }else if( rc==SQLITE_DONE ){
+        /* Clear the pending terms so we don't flush a useless level-0
+        ** segment when the transaction closes.
+        */
+        rc = clearPendingTerms(v);
         if( rc==SQLITE_OK ){
-          int nCount;
-          nCount = fts3DoclistCountDocids(
-              pTC->pPhrase->doclist.aAll, pTC->pPhrase->doclist.nAll
-          );
-          if( ii==0 || nCount<nMinEst ) nMinEst = nCount;
+          rc = segdir_delete_all(v);
         }
       }
     }
-    pTC->pToken = 0;
+  } else if( sqlite3_value_type(ppArg[0]) != SQLITE_NULL ){
+    /* An update:
+     * ppArg[0] = old rowid
+     * ppArg[1] = new rowid
+     * ppArg[2..2+v->nColumn-1] = values
+     * ppArg[2+v->nColumn] = value for magic column (we ignore this)
+     * ppArg[2+v->nColumn+1] = value for docid
+     */
+    sqlite_int64 rowid = sqlite3_value_int64(ppArg[0]);
+    if( sqlite3_value_type(ppArg[1]) != SQLITE_INTEGER ||
+        sqlite3_value_int64(ppArg[1]) != rowid ){
+      rc = SQLITE_ERROR;  /* we don't allow changing the rowid */
+    }else if( sqlite3_value_type(ppArg[2+v->nColumn+1]) != SQLITE_INTEGER ||
+              sqlite3_value_int64(ppArg[2+v->nColumn+1]) != rowid ){
+      rc = SQLITE_ERROR;  /* we don't allow changing the docid */
+    }else{
+      assert( nArg==2+v->nColumn+2);
+      rc = index_update(v, rowid, &ppArg[2]);
+    }
+  } else {
+    /* An insert:
+     * ppArg[1] = requested rowid
+     * ppArg[2..2+v->nColumn-1] = values
+     * ppArg[2+v->nColumn] = value for magic column (we ignore this)
+     * ppArg[2+v->nColumn+1] = value for docid
+     */
+    sqlite3_value *pRequestDocid = ppArg[2+v->nColumn+1];
+    assert( nArg==2+v->nColumn+2);
+    if( SQLITE_NULL != sqlite3_value_type(pRequestDocid) &&
+        SQLITE_NULL != sqlite3_value_type(ppArg[1]) ){
+      /* TODO(shess) Consider allowing this to work if the values are
+      ** identical.  I'm inclined to discourage that usage, though,
+      ** given that both rowid and docid are special columns.  Better
+      ** would be to define one or the other as the default winner,
+      ** but should it be fts3-centric (docid) or SQLite-centric
+      ** (rowid)?
+      */
+      rc = SQLITE_ERROR;
+    }else{
+      if( SQLITE_NULL == sqlite3_value_type(pRequestDocid) ){
+        pRequestDocid = ppArg[1];
+      }
+      rc = index_insert(v, pRequestDocid, &ppArg[2], pRowid);
+    }
   }
 
   return rc;
 }
 
-/*
-** This function is called from within the xFilter method. It initializes
-** the full-text query currently stored in pCsr->pExpr. To iterate through
-** the results of a query, the caller does:
-**
-**    fts3EvalStart(pCsr);
-**    while( 1 ){
-**      fts3EvalNext(pCsr);
-**      if( pCsr->bEof ) break;
-**      ... return row pCsr->iPrevId to the caller ...
-**    }
-*/
-static int fts3EvalStart(Fts3Cursor *pCsr){
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-  int rc = SQLITE_OK;
-  int nToken = 0;
-  int nOr = 0;
+static int fulltextSync(sqlite3_vtab *pVtab){
+  FTSTRACE(("FTS3 xSync()\n"));
+  return flushPendingTerms((fulltext_vtab *)pVtab);
+}
 
-  /* Allocate a MultiSegReader for each token in the expression. */
-  fts3EvalAllocateReaders(pCsr, pCsr->pExpr, &nToken, &nOr, &rc);
+static int fulltextBegin(sqlite3_vtab *pVtab){
+  fulltext_vtab *v = (fulltext_vtab *) pVtab;
+  FTSTRACE(("FTS3 xBegin()\n"));
 
-  /* Determine which, if any, tokens in the expression should be deferred. */
-#ifndef SQLITE_DISABLE_FTS4_DEFERRED
-  if( rc==SQLITE_OK && nToken>1 && pTab->bFts4 ){
-    Fts3TokenAndCost *aTC;
-    Fts3Expr **apOr;
-    aTC = (Fts3TokenAndCost *)sqlite3_malloc(
-        sizeof(Fts3TokenAndCost) * nToken
-      + sizeof(Fts3Expr *) * nOr * 2
-    );
-    apOr = (Fts3Expr **)&aTC[nToken];
+  /* Any buffered updates should have been cleared by the previous
+  ** transaction.
+  */
+  assert( v->nPendingData<0 );
+  return clearPendingTerms(v);
+}
 
-    if( !aTC ){
-      rc = SQLITE_NOMEM;
-    }else{
-      int ii;
-      Fts3TokenAndCost *pTC = aTC;
-      Fts3Expr **ppOr = apOr;
-
-      fts3EvalTokenCosts(pCsr, 0, pCsr->pExpr, &pTC, &ppOr, &rc);
-      nToken = (int)(pTC-aTC);
-      nOr = (int)(ppOr-apOr);
+static int fulltextCommit(sqlite3_vtab *pVtab){
+  fulltext_vtab *v = (fulltext_vtab *) pVtab;
+  FTSTRACE(("FTS3 xCommit()\n"));
 
-      if( rc==SQLITE_OK ){
-        rc = fts3EvalSelectDeferred(pCsr, 0, aTC, nToken);
-        for(ii=0; rc==SQLITE_OK && ii<nOr; ii++){
-          rc = fts3EvalSelectDeferred(pCsr, apOr[ii], aTC, nToken);
+  /* Buffered updates should have been cleared by fulltextSync(). */
+  assert( v->nPendingData<0 );
+  return clearPendingTerms(v);
+}
+
+static int fulltextRollback(sqlite3_vtab *pVtab){
+  FTSTRACE(("FTS3 xRollback()\n"));
+  return clearPendingTerms((fulltext_vtab *)pVtab);
+}
+
+/*
+** Implementation of the snippet() function for FTS3
+*/
+static void snippetFunc(
+  sqlite3_context *pContext,
+  int argc,
+  sqlite3_value **argv
+){
+  fulltext_cursor *pCursor;
+  if( argc<1 ) return;
+  if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
+      sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
+    sqlite3_result_error(pContext, "illegal first argument to html_snippet",-1);
+  }else{
+    const char *zStart = "<b>";
+    const char *zEnd = "</b>";
+    const char *zEllipsis = "<b>...</b>";
+    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
+    if( argc>=2 ){
+      zStart = (const char*)sqlite3_value_text(argv[1]);
+      if( argc>=3 ){
+        zEnd = (const char*)sqlite3_value_text(argv[2]);
+        if( argc>=4 ){
+          zEllipsis = (const char*)sqlite3_value_text(argv[3]);
         }
       }
-
-      sqlite3_free(aTC);
     }
+    snippetAllOffsets(pCursor);
+    snippetText(pCursor, zStart, zEnd, zEllipsis);
+    sqlite3_result_text(pContext, pCursor->snippet.zSnippet,
+                        pCursor->snippet.nSnippet, SQLITE_STATIC);
   }
-#endif
-
-  fts3EvalStartReaders(pCsr, pCsr->pExpr, &rc);
-  return rc;
 }
 
 /*
-** Invalidate the current position list for phrase pPhrase.
+** Implementation of the offsets() function for FTS3
 */
-static void fts3EvalInvalidatePoslist(Fts3Phrase *pPhrase){
-  if( pPhrase->doclist.bFreeList ){
-    sqlite3_free(pPhrase->doclist.pList);
-  }
-  pPhrase->doclist.pList = 0;
-  pPhrase->doclist.nList = 0;
-  pPhrase->doclist.bFreeList = 0;
+static void snippetOffsetsFunc(
+  sqlite3_context *pContext,
+  int argc,
+  sqlite3_value **argv
+){
+  fulltext_cursor *pCursor;
+  if( argc<1 ) return;
+  if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
+      sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
+    sqlite3_result_error(pContext, "illegal first argument to offsets",-1);
+  }else{
+    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
+    snippetAllOffsets(pCursor);
+    snippetOffsetText(&pCursor->snippet);
+    sqlite3_result_text(pContext,
+                        pCursor->snippet.zOffset, pCursor->snippet.nOffset,
+                        SQLITE_STATIC);
+  }
 }
 
-/*
-** This function is called to edit the position list associated with
-** the phrase object passed as the fifth argument according to a NEAR
-** condition. For example:
-**
-**     abc NEAR/5 "def ghi"
-**
-** Parameter nNear is passed the NEAR distance of the expression (5 in
-** the example above). When this function is called, *paPoslist points to
-** the position list, and *pnToken is the number of phrase tokens in, the
-** phrase on the other side of the NEAR operator to pPhrase. For example,
-** if pPhrase refers to the "def ghi" phrase, then *paPoslist points to
-** the position list associated with phrase "abc".
-**
-** All positions in the pPhrase position list that are not sufficiently
-** close to a position in the *paPoslist position list are removed. If this
-** leaves 0 positions, zero is returned. Otherwise, non-zero.
-**
-** Before returning, *paPoslist is set to point to the position lsit 
-** associated with pPhrase. And *pnToken is set to the number of tokens in
-** pPhrase.
-*/
-static int fts3EvalNearTrim(
-  int nNear,                      /* NEAR distance. As in "NEAR/nNear". */
-  char *aTmp,                     /* Temporary space to use */
-  char **paPoslist,               /* IN/OUT: Position list */
-  int *pnToken,                   /* IN/OUT: Tokens in phrase of *paPoslist */
-  Fts3Phrase *pPhrase             /* The phrase object to trim the doclist of */
-){
-  int nParam1 = nNear + pPhrase->nToken;
-  int nParam2 = nNear + *pnToken;
-  int nNew;
-  char *p2; 
-  char *pOut; 
-  int res;
-
-  assert( pPhrase->doclist.pList );
-
-  p2 = pOut = pPhrase->doclist.pList;
-  res = fts3PoslistNearMerge(
-    &pOut, aTmp, nParam1, nParam2, paPoslist, &p2
-  );
-  if( res ){
-    nNew = (int)(pOut - pPhrase->doclist.pList) - 1;
-    assert( pPhrase->doclist.pList[nNew]=='\0' );
-    assert( nNew<=pPhrase->doclist.nList && nNew>0 );
-    memset(&pPhrase->doclist.pList[nNew], 0, pPhrase->doclist.nList - nNew);
-    pPhrase->doclist.nList = nNew;
-    *paPoslist = pPhrase->doclist.pList;
-    *pnToken = pPhrase->nToken;
-  }
+/* OptLeavesReader is nearly identical to LeavesReader, except that
+** where LeavesReader is geared towards the merging of complete
+** segment levels (with exactly MERGE_COUNT segments), OptLeavesReader
+** is geared towards implementation of the optimize() function, and
+** can merge all segments simultaneously.  This version may be
+** somewhat less efficient than LeavesReader because it merges into an
+** accumulator rather than doing an N-way merge, but since segment
+** size grows exponentially (so segment count logrithmically) this is
+** probably not an immediate problem.
+*/
+/* TODO(shess): Prove that assertion, or extend the merge code to
+** merge tree fashion (like the prefix-searching code does).
+*/
+/* TODO(shess): OptLeavesReader and LeavesReader could probably be
+** merged with little or no loss of performance for LeavesReader.  The
+** merged code would need to handle >MERGE_COUNT segments, and would
+** also need to be able to optionally optimize away deletes.
+*/
+typedef struct OptLeavesReader {
+  /* Segment number, to order readers by age. */
+  int segment;
+  LeavesReader reader;
+} OptLeavesReader;
 
-  return res;
+static int optLeavesReaderAtEnd(OptLeavesReader *pReader){
+  return leavesReaderAtEnd(&pReader->reader);
+}
+static int optLeavesReaderTermBytes(OptLeavesReader *pReader){
+  return leavesReaderTermBytes(&pReader->reader);
+}
+static const char *optLeavesReaderData(OptLeavesReader *pReader){
+  return leavesReaderData(&pReader->reader);
+}
+static int optLeavesReaderDataBytes(OptLeavesReader *pReader){
+  return leavesReaderDataBytes(&pReader->reader);
+}
+static const char *optLeavesReaderTerm(OptLeavesReader *pReader){
+  return leavesReaderTerm(&pReader->reader);
+}
+static int optLeavesReaderStep(fulltext_vtab *v, OptLeavesReader *pReader){
+  return leavesReaderStep(v, &pReader->reader);
+}
+static int optLeavesReaderTermCmp(OptLeavesReader *lr1, OptLeavesReader *lr2){
+  return leavesReaderTermCmp(&lr1->reader, &lr2->reader);
+}
+/* Order by term ascending, segment ascending (oldest to newest), with
+** exhausted readers to the end.
+*/
+static int optLeavesReaderCmp(OptLeavesReader *lr1, OptLeavesReader *lr2){
+  int c = optLeavesReaderTermCmp(lr1, lr2);
+  if( c!=0 ) return c;
+  return lr1->segment-lr2->segment;
+}
+/* Bubble pLr[0] to appropriate place in pLr[1..nLr-1].  Assumes that
+** pLr[1..nLr-1] is already sorted.
+*/
+static void optLeavesReaderReorder(OptLeavesReader *pLr, int nLr){
+  while( nLr>1 && optLeavesReaderCmp(pLr, pLr+1)>0 ){
+    OptLeavesReader tmp = pLr[0];
+    pLr[0] = pLr[1];
+    pLr[1] = tmp;
+    nLr--;
+    pLr++;
+  }
 }
 
-/*
-** This function is a no-op if *pRc is other than SQLITE_OK when it is called.
-** Otherwise, it advances the expression passed as the second argument to
-** point to the next matching row in the database. Expressions iterate through
-** matching rows in docid order. Ascending order if Fts3Cursor.bDesc is zero,
-** or descending if it is non-zero.
-**
-** If an error occurs, *pRc is set to an SQLite error code. Otherwise, if
-** successful, the following variables in pExpr are set:
-**
-**   Fts3Expr.bEof                (non-zero if EOF - there is no next row)
-**   Fts3Expr.iDocid              (valid if bEof==0. The docid of the next row)
-**
-** If the expression is of type FTSQUERY_PHRASE, and the expression is not
-** at EOF, then the following variables are populated with the position list
-** for the phrase for the visited row:
-**
-**   FTs3Expr.pPhrase->doclist.nList        (length of pList in bytes)
-**   FTs3Expr.pPhrase->doclist.pList        (pointer to position list)
-**
-** It says above that this function advances the expression to the next
-** matching row. This is usually true, but there are the following exceptions:
-**
-**   1. Deferred tokens are not taken into account. If a phrase consists
-**      entirely of deferred tokens, it is assumed to match every row in
-**      the db. In this case the position-list is not populated at all. 
-**
-**      Or, if a phrase contains one or more deferred tokens and one or
-**      more non-deferred tokens, then the expression is advanced to the 
-**      next possible match, considering only non-deferred tokens. In other
-**      words, if the phrase is "A B C", and "B" is deferred, the expression
-**      is advanced to the next row that contains an instance of "A * C", 
-**      where "*" may match any single token. The position list in this case
-**      is populated as for "A * C" before returning.
-**
-**   2. NEAR is treated as AND. If the expression is "x NEAR y", it is 
-**      advanced to point to the next row that matches "x AND y".
-** 
-** See sqlite3Fts3EvalTestDeferred() for details on testing if a row is
-** really a match, taking into account deferred tokens and NEAR operators.
+/* optimize() helper function.  Put the readers in order and iterate
+** through them, merging doclists for matching terms into pWriter.
+** Returns SQLITE_OK on success, or the SQLite error code which
+** prevented success.
 */
-static void fts3EvalNextRow(
-  Fts3Cursor *pCsr,               /* FTS Cursor handle */
-  Fts3Expr *pExpr,                /* Expr. to advance to next matching row */
-  int *pRc                        /* IN/OUT: Error code */
-){
-  if( *pRc==SQLITE_OK ){
-    int bDescDoclist = pCsr->bDesc;         /* Used by DOCID_CMP() macro */
-    assert( pExpr->bEof==0 );
-    pExpr->bStart = 1;
+static int optimizeInternal(fulltext_vtab *v,
+                            OptLeavesReader *readers, int nReaders,
+                            LeafWriter *pWriter){
+  int i, rc = SQLITE_OK;
+  DataBuffer doclist, merged, tmp;
 
-    switch( pExpr->eType ){
-      case FTSQUERY_NEAR:
-      case FTSQUERY_AND: {
-        Fts3Expr *pLeft = pExpr->pLeft;
-        Fts3Expr *pRight = pExpr->pRight;
-        assert( !pLeft->bDeferred || !pRight->bDeferred );
+  /* Order the readers. */
+  i = nReaders;
+  while( i-- > 0 ){
+    optLeavesReaderReorder(&readers[i], nReaders-i);
+  }
 
-        if( pLeft->bDeferred ){
-          /* LHS is entirely deferred. So we assume it matches every row.
-          ** Advance the RHS iterator to find the next row visited. */
-          fts3EvalNextRow(pCsr, pRight, pRc);
-          pExpr->iDocid = pRight->iDocid;
-          pExpr->bEof = pRight->bEof;
-        }else if( pRight->bDeferred ){
-          /* RHS is entirely deferred. So we assume it matches every row.
-          ** Advance the LHS iterator to find the next row visited. */
-          fts3EvalNextRow(pCsr, pLeft, pRc);
-          pExpr->iDocid = pLeft->iDocid;
-          pExpr->bEof = pLeft->bEof;
-        }else{
-          /* Neither the RHS or LHS are deferred. */
-          fts3EvalNextRow(pCsr, pLeft, pRc);
-          fts3EvalNextRow(pCsr, pRight, pRc);
-          while( !pLeft->bEof && !pRight->bEof && *pRc==SQLITE_OK ){
-            sqlite3_int64 iDiff = DOCID_CMP(pLeft->iDocid, pRight->iDocid);
-            if( iDiff==0 ) break;
-            if( iDiff<0 ){
-              fts3EvalNextRow(pCsr, pLeft, pRc);
-            }else{
-              fts3EvalNextRow(pCsr, pRight, pRc);
-            }
-          }
-          pExpr->iDocid = pLeft->iDocid;
-          pExpr->bEof = (pLeft->bEof || pRight->bEof);
-          if( pExpr->eType==FTSQUERY_NEAR && pExpr->bEof ){
-            assert( pRight->eType==FTSQUERY_PHRASE );
-            if( pRight->pPhrase->doclist.aAll ){
-              Fts3Doclist *pDl = &pRight->pPhrase->doclist;
-              while( *pRc==SQLITE_OK && pRight->bEof==0 ){
-                memset(pDl->pList, 0, pDl->nList);
-                fts3EvalNextRow(pCsr, pRight, pRc);
-              }
-            }
-            if( pLeft->pPhrase && pLeft->pPhrase->doclist.aAll ){
-              Fts3Doclist *pDl = &pLeft->pPhrase->doclist;
-              while( *pRc==SQLITE_OK && pLeft->bEof==0 ){
-                memset(pDl->pList, 0, pDl->nList);
-                fts3EvalNextRow(pCsr, pLeft, pRc);
-              }
-            }
-          }
-        }
-        break;
-      }
-  
-      case FTSQUERY_OR: {
-        Fts3Expr *pLeft = pExpr->pLeft;
-        Fts3Expr *pRight = pExpr->pRight;
-        sqlite3_int64 iCmp = DOCID_CMP(pLeft->iDocid, pRight->iDocid);
+  dataBufferInit(&doclist, LEAF_MAX);
+  dataBufferInit(&merged, LEAF_MAX);
 
-        assert( pLeft->bStart || pLeft->iDocid==pRight->iDocid );
-        assert( pRight->bStart || pLeft->iDocid==pRight->iDocid );
+  /* Exhausted readers bubble to the end, so when the first reader is
+  ** at eof, all are at eof.
+  */
+  while( !optLeavesReaderAtEnd(&readers[0]) ){
 
-        if( pRight->bEof || (pLeft->bEof==0 && iCmp<0) ){
-          fts3EvalNextRow(pCsr, pLeft, pRc);
-        }else if( pLeft->bEof || iCmp>0 ){
-          fts3EvalNextRow(pCsr, pRight, pRc);
-        }else{
-          fts3EvalNextRow(pCsr, pLeft, pRc);
-          fts3EvalNextRow(pCsr, pRight, pRc);
+    /* Figure out how many readers share the next term. */
+    for(i=1; i<nReaders && !optLeavesReaderAtEnd(&readers[i]); i++){
+      if( 0!=optLeavesReaderTermCmp(&readers[0], &readers[i]) ) break;
+    }
+
+    /* Special-case for no merge. */
+    if( i==1 ){
+      /* Trim deletions from the doclist. */
+      dataBufferReset(&merged);
+      docListTrim(DL_DEFAULT,
+                  optLeavesReaderData(&readers[0]),
+                  optLeavesReaderDataBytes(&readers[0]),
+                  -1, DL_DEFAULT, &merged);
+    }else{
+      DLReader dlReaders[MERGE_COUNT];
+      int iReader, nReaders;
+
+      /* Prime the pipeline with the first reader's doclist.  After
+      ** one pass index 0 will reference the accumulated doclist.
+      */
+      dlrInit(&dlReaders[0], DL_DEFAULT,
+              optLeavesReaderData(&readers[0]),
+              optLeavesReaderDataBytes(&readers[0]));
+      iReader = 1;
+
+      assert( iReader<i );  /* Must execute the loop at least once. */
+      while( iReader<i ){
+        /* Merge 16 inputs per pass. */
+        for( nReaders=1; iReader<i && nReaders<MERGE_COUNT;
+             iReader++, nReaders++ ){
+          dlrInit(&dlReaders[nReaders], DL_DEFAULT,
+                  optLeavesReaderData(&readers[iReader]),
+                  optLeavesReaderDataBytes(&readers[iReader]));
         }
 
-        pExpr->bEof = (pLeft->bEof && pRight->bEof);
-        iCmp = DOCID_CMP(pLeft->iDocid, pRight->iDocid);
-        if( pRight->bEof || (pLeft->bEof==0 &&  iCmp<0) ){
-          pExpr->iDocid = pLeft->iDocid;
-        }else{
-          pExpr->iDocid = pRight->iDocid;
+        /* Merge doclists and swap result into accumulator. */
+        dataBufferReset(&merged);
+        docListMerge(&merged, dlReaders, nReaders);
+        tmp = merged;
+        merged = doclist;
+        doclist = tmp;
+
+        while( nReaders-- > 0 ){
+          dlrDestroy(&dlReaders[nReaders]);
         }
 
-        break;
+        /* Accumulated doclist to reader 0 for next pass. */
+        dlrInit(&dlReaders[0], DL_DEFAULT, doclist.pData, doclist.nData);
       }
 
-      case FTSQUERY_NOT: {
-        Fts3Expr *pLeft = pExpr->pLeft;
-        Fts3Expr *pRight = pExpr->pRight;
+      /* Destroy reader that was left in the pipeline. */
+      dlrDestroy(&dlReaders[0]);
 
-        if( pRight->bStart==0 ){
-          fts3EvalNextRow(pCsr, pRight, pRc);
-          assert( *pRc!=SQLITE_OK || pRight->bStart );
-        }
+      /* Trim deletions from the doclist. */
+      dataBufferReset(&merged);
+      docListTrim(DL_DEFAULT, doclist.pData, doclist.nData,
+                  -1, DL_DEFAULT, &merged);
+    }
 
-        fts3EvalNextRow(pCsr, pLeft, pRc);
-        if( pLeft->bEof==0 ){
-          while( !*pRc 
-              && !pRight->bEof 
-              && DOCID_CMP(pLeft->iDocid, pRight->iDocid)>0 
-          ){
-            fts3EvalNextRow(pCsr, pRight, pRc);
-          }
-        }
-        pExpr->iDocid = pLeft->iDocid;
-        pExpr->bEof = pLeft->bEof;
-        break;
-      }
+    /* Only pass doclists with hits (skip if all hits deleted). */
+    if( merged.nData>0 ){
+      rc = leafWriterStep(v, pWriter,
+                          optLeavesReaderTerm(&readers[0]),
+                          optLeavesReaderTermBytes(&readers[0]),
+                          merged.pData, merged.nData);
+      if( rc!=SQLITE_OK ) goto err;
+    }
 
-      default: {
-        Fts3Phrase *pPhrase = pExpr->pPhrase;
-        fts3EvalInvalidatePoslist(pPhrase);
-        *pRc = fts3EvalPhraseNext(pCsr, pPhrase, &pExpr->bEof);
-        pExpr->iDocid = pPhrase->doclist.iDocid;
-        break;
-      }
+    /* Step merged readers to next term and reorder. */
+    while( i-- > 0 ){
+      rc = optLeavesReaderStep(v, &readers[i]);
+      if( rc!=SQLITE_OK ) goto err;
+
+      optLeavesReaderReorder(&readers[i], nReaders-i);
     }
   }
+
+ err:
+  dataBufferDestroy(&doclist);
+  dataBufferDestroy(&merged);
+  return rc;
 }
 
-/*
-** If *pRc is not SQLITE_OK, or if pExpr is not the root node of a NEAR
-** cluster, then this function returns 1 immediately.
-**
-** Otherwise, it checks if the current row really does match the NEAR 
-** expression, using the data currently stored in the position lists 
-** (Fts3Expr->pPhrase.doclist.pList/nList) for each phrase in the expression. 
-**
-** If the current row is a match, the position list associated with each
-** phrase in the NEAR expression is edited in place to contain only those
-** phrase instances sufficiently close to their peers to satisfy all NEAR
-** constraints. In this case it returns 1. If the NEAR expression does not 
-** match the current row, 0 is returned. The position lists may or may not
-** be edited if 0 is returned.
-*/
-static int fts3EvalNearTest(Fts3Expr *pExpr, int *pRc){
-  int res = 1;
+/* Implement optimize() function for FTS3.  optimize(t) merges all
+** segments in the fts index into a single segment.  't' is the magic
+** table-named column.
+*/
+static void optimizeFunc(sqlite3_context *pContext,
+                         int argc, sqlite3_value **argv){
+  fulltext_cursor *pCursor;
+  if( argc>1 ){
+    sqlite3_result_error(pContext, "excess arguments to optimize()",-1);
+  }else if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
+            sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
+    sqlite3_result_error(pContext, "illegal first argument to optimize",-1);
+  }else{
+    fulltext_vtab *v;
+    int i, rc, iMaxLevel;
+    OptLeavesReader *readers;
+    int nReaders;
+    LeafWriter writer;
+    sqlite3_stmt *s;
+
+    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
+    v = cursor_vtab(pCursor);
+
+    /* Flush any buffered updates before optimizing. */
+    rc = flushPendingTerms(v);
+    if( rc!=SQLITE_OK ) goto err;
+
+    rc = segdir_count(v, &nReaders, &iMaxLevel);
+    if( rc!=SQLITE_OK ) goto err;
+    if( nReaders==0 || nReaders==1 ){
+      sqlite3_result_text(pContext, "Index already optimal", -1,
+                          SQLITE_STATIC);
+      return;
+    }
+
+    rc = sql_get_statement(v, SEGDIR_SELECT_ALL_STMT, &s);
+    if( rc!=SQLITE_OK ) goto err;
+
+    readers = sqlite3_malloc(nReaders*sizeof(readers[0]));
+    if( readers==NULL ) goto err;
+
+    /* Note that there will already be a segment at this position
+    ** until we call segdir_delete() on iMaxLevel.
+    */
+    leafWriterInit(iMaxLevel, 0, &writer);
 
-  /* The following block runs if pExpr is the root of a NEAR query.
-  ** For example, the query:
-  **
-  **         "w" NEAR "x" NEAR "y" NEAR "z"
-  **
-  ** which is represented in tree form as:
-  **
-  **                               |
-  **                          +--NEAR--+      <-- root of NEAR query
-  **                          |        |
-  **                     +--NEAR--+   "z"
-  **                     |        |
-  **                +--NEAR--+   "y"
-  **                |        |
-  **               "w"      "x"
-  **
-  ** The right-hand child of a NEAR node is always a phrase. The 
-  ** left-hand child may be either a phrase or a NEAR node. There are
-  ** no exceptions to this - it's the way the parser in fts3_expr.c works.
-  */
-  if( *pRc==SQLITE_OK 
-   && pExpr->eType==FTSQUERY_NEAR 
-   && (pExpr->pParent==0 || pExpr->pParent->eType!=FTSQUERY_NEAR)
-  ){
-    Fts3Expr *p; 
-    int nTmp = 0;                 /* Bytes of temp space */
-    char *aTmp;                   /* Temp space for PoslistNearMerge() */
-
-    /* Allocate temporary working space. */
-    for(p=pExpr; p->pLeft; p=p->pLeft){
-      assert( p->pRight->pPhrase->doclist.nList>0 );
-      nTmp += p->pRight->pPhrase->doclist.nList;
-    }
-    nTmp += p->pPhrase->doclist.nList;
-    aTmp = sqlite3_malloc(nTmp*2);
-    if( !aTmp ){
-      *pRc = SQLITE_NOMEM;
-      res = 0;
-    }else{
-      char *aPoslist = p->pPhrase->doclist.pList;
-      int nToken = p->pPhrase->nToken;
+    i = 0;
+    while( (rc = sqlite3_step(s))==SQLITE_ROW ){
+      sqlite_int64 iStart = sqlite3_column_int64(s, 0);
+      sqlite_int64 iEnd = sqlite3_column_int64(s, 1);
+      const char *pRootData = sqlite3_column_blob(s, 2);
+      int nRootData = sqlite3_column_bytes(s, 2);
 
-      for(p=p->pParent;res && p && p->eType==FTSQUERY_NEAR; p=p->pParent){
-        Fts3Phrase *pPhrase = p->pRight->pPhrase;
-        int nNear = p->nNear;
-        res = fts3EvalNearTrim(nNear, aTmp, &aPoslist, &nToken, pPhrase);
-      }
+      assert( i<nReaders );
+      rc = leavesReaderInit(v, -1, iStart, iEnd, pRootData, nRootData,
+                            &readers[i].reader);
+      if( rc!=SQLITE_OK ) break;
 
-      aPoslist = pExpr->pRight->pPhrase->doclist.pList;
-      nToken = pExpr->pRight->pPhrase->nToken;
-      for(p=pExpr->pLeft; p && res; p=p->pLeft){
-        int nNear;
-        Fts3Phrase *pPhrase;
-        assert( p->pParent && p->pParent->pLeft==p );
-        nNear = p->pParent->nNear;
-        pPhrase = (
-            p->eType==FTSQUERY_NEAR ? p->pRight->pPhrase : p->pPhrase
-        );
-        res = fts3EvalNearTrim(nNear, aTmp, &aPoslist, &nToken, pPhrase);
-      }
+      readers[i].segment = i;
+      i++;
     }
 
-    sqlite3_free(aTmp);
-  }
+    /* If we managed to successfully read them all, optimize them. */
+    if( rc==SQLITE_DONE ){
+      assert( i==nReaders );
+      rc = optimizeInternal(v, readers, nReaders, &writer);
+    }
 
-  return res;
-}
+    while( i-- > 0 ){
+      leavesReaderDestroy(&readers[i].reader);
+    }
+    sqlite3_free(readers);
 
-/*
-** This function is a helper function for sqlite3Fts3EvalTestDeferred().
-** Assuming no error occurs or has occurred, It returns non-zero if the
-** expression passed as the second argument matches the row that pCsr 
-** currently points to, or zero if it does not.
-**
-** If *pRc is not SQLITE_OK when this function is called, it is a no-op.
-** If an error occurs during execution of this function, *pRc is set to 
-** the appropriate SQLite error code. In this case the returned value is 
-** undefined.
-*/
-static int fts3EvalTestExpr(
-  Fts3Cursor *pCsr,               /* FTS cursor handle */
-  Fts3Expr *pExpr,                /* Expr to test. May or may not be root. */
-  int *pRc                        /* IN/OUT: Error code */
-){
-  int bHit = 1;                   /* Return value */
-  if( *pRc==SQLITE_OK ){
-    switch( pExpr->eType ){
-      case FTSQUERY_NEAR:
-      case FTSQUERY_AND:
-        bHit = (
-            fts3EvalTestExpr(pCsr, pExpr->pLeft, pRc)
-         && fts3EvalTestExpr(pCsr, pExpr->pRight, pRc)
-         && fts3EvalNearTest(pExpr, pRc)
-        );
+    /* If we've successfully gotten to here, delete the old segments
+    ** and flush the interior structure of the new segment.
+    */
+    if( rc==SQLITE_OK ){
+      for( i=0; i<=iMaxLevel; i++ ){
+        rc = segdir_delete(v, i);
+        if( rc!=SQLITE_OK ) break;
+      }
 
-        /* If the NEAR expression does not match any rows, zero the doclist for 
-        ** all phrases involved in the NEAR. This is because the snippet(),
-        ** offsets() and matchinfo() functions are not supposed to recognize 
-        ** any instances of phrases that are part of unmatched NEAR queries. 
-        ** For example if this expression:
-        **
-        **    ... MATCH 'a OR (b NEAR c)'
-        **
-        ** is matched against a row containing:
-        **
-        **        'a b d e'
-        **
-        ** then any snippet() should ony highlight the "a" term, not the "b"
-        ** (as "b" is part of a non-matching NEAR clause).
-        */
-        if( bHit==0 
-         && pExpr->eType==FTSQUERY_NEAR 
-         && (pExpr->pParent==0 || pExpr->pParent->eType!=FTSQUERY_NEAR)
-        ){
-          Fts3Expr *p;
-          for(p=pExpr; p->pPhrase==0; p=p->pLeft){
-            if( p->pRight->iDocid==pCsr->iPrevId ){
-              fts3EvalInvalidatePoslist(p->pRight->pPhrase);
-            }
-          }
-          if( p->iDocid==pCsr->iPrevId ){
-            fts3EvalInvalidatePoslist(p->pPhrase);
-          }
-        }
+      if( rc==SQLITE_OK ) rc = leafWriterFinalize(v, &writer);
+    }
 
-        break;
+    leafWriterDestroy(&writer);
 
-      case FTSQUERY_OR: {
-        int bHit1 = fts3EvalTestExpr(pCsr, pExpr->pLeft, pRc);
-        int bHit2 = fts3EvalTestExpr(pCsr, pExpr->pRight, pRc);
-        bHit = bHit1 || bHit2;
-        break;
-      }
+    if( rc!=SQLITE_OK ) goto err;
 
-      case FTSQUERY_NOT:
-        bHit = (
-            fts3EvalTestExpr(pCsr, pExpr->pLeft, pRc)
-         && !fts3EvalTestExpr(pCsr, pExpr->pRight, pRc)
-        );
-        break;
+    sqlite3_result_text(pContext, "Index optimized", -1, SQLITE_STATIC);
+    return;
 
-      default: {
-#ifndef SQLITE_DISABLE_FTS4_DEFERRED
-        if( pCsr->pDeferred 
-         && (pExpr->iDocid==pCsr->iPrevId || pExpr->bDeferred)
-        ){
-          Fts3Phrase *pPhrase = pExpr->pPhrase;
-          assert( pExpr->bDeferred || pPhrase->doclist.bFreeList==0 );
-          if( pExpr->bDeferred ){
-            fts3EvalInvalidatePoslist(pPhrase);
-          }
-          *pRc = fts3EvalDeferredPhrase(pCsr, pPhrase);
-          bHit = (pPhrase->doclist.pList!=0);
-          pExpr->iDocid = pCsr->iPrevId;
-        }else
-#endif
-        {
-          bHit = (pExpr->bEof==0 && pExpr->iDocid==pCsr->iPrevId);
-        }
-        break;
-      }
+    /* TODO(shess): Error-handling needs to be improved along the
+    ** lines of the dump_ functions.
+    */
+ err:
+    {
+      char buf[512];
+      sqlite3_snprintf(sizeof(buf), buf, "Error in optimize: %s",
+                       sqlite3_errmsg(sqlite3_context_db_handle(pContext)));
+      sqlite3_result_error(pContext, buf, -1);
     }
   }
-  return bHit;
 }
 
-/*
-** This function is called as the second part of each xNext operation when
-** iterating through the results of a full-text query. At this point the
-** cursor points to a row that matches the query expression, with the
-** following caveats:
-**
-**   * Up until this point, "NEAR" operators in the expression have been
-**     treated as "AND".
-**
-**   * Deferred tokens have not yet been considered.
-**
-** If *pRc is not SQLITE_OK when this function is called, it immediately
-** returns 0. Otherwise, it tests whether or not after considering NEAR
-** operators and deferred tokens the current row is still a match for the
-** expression. It returns 1 if both of the following are true:
-**
-**   1. *pRc is SQLITE_OK when this function returns, and
-**
-**   2. After scanning the current FTS table row for the deferred tokens,
-**      it is determined that the row does *not* match the query.
-**
-** Or, if no error occurs and it seems the current row does match the FTS
-** query, return 0.
+#ifdef SQLITE_TEST
+/* Generate an error of the form "<prefix>: <msg>".  If msg is NULL,
+** pull the error from the context's db handle.
 */
-int sqlite3Fts3EvalTestDeferred(Fts3Cursor *pCsr, int *pRc){
-  int rc = *pRc;
-  int bMiss = 0;
-  if( rc==SQLITE_OK ){
+static void generateError(sqlite3_context *pContext,
+                          const char *prefix, const char *msg){
+  char buf[512];
+  if( msg==NULL ) msg = sqlite3_errmsg(sqlite3_context_db_handle(pContext));
+  sqlite3_snprintf(sizeof(buf), buf, "%s: %s", prefix, msg);
+  sqlite3_result_error(pContext, buf, -1);
+}
+
+/* Helper function to collect the set of terms in the segment into
+** pTerms.  The segment is defined by the leaf nodes between
+** iStartBlockid and iEndBlockid, inclusive, or by the contents of
+** pRootData if iStartBlockid is 0 (in which case the entire segment
+** fit in a leaf).
+*/
+static int collectSegmentTerms(fulltext_vtab *v, sqlite3_stmt *s,
+                               fts3Hash *pTerms){
+  const sqlite_int64 iStartBlockid = sqlite3_column_int64(s, 0);
+  const sqlite_int64 iEndBlockid = sqlite3_column_int64(s, 1);
+  const char *pRootData = sqlite3_column_blob(s, 2);
+  const int nRootData = sqlite3_column_bytes(s, 2);
+  LeavesReader reader;
+  int rc = leavesReaderInit(v, 0, iStartBlockid, iEndBlockid,
+                            pRootData, nRootData, &reader);
+  if( rc!=SQLITE_OK ) return rc;
+
+  while( rc==SQLITE_OK && !leavesReaderAtEnd(&reader) ){
+    const char *pTerm = leavesReaderTerm(&reader);
+    const int nTerm = leavesReaderTermBytes(&reader);
+    void *oldValue = sqlite3Fts3HashFind(pTerms, pTerm, nTerm);
+    void *newValue = (void *)((char *)oldValue+1);
 
-    /* If there are one or more deferred tokens, load the current row into
-    ** memory and scan it to determine the position list for each deferred
-    ** token. Then, see if this row is really a match, considering deferred
-    ** tokens and NEAR operators (neither of which were taken into account
-    ** earlier, by fts3EvalNextRow()). 
+    /* From the comment before sqlite3Fts3HashInsert in fts3_hash.c,
+    ** the data value passed is returned in case of malloc failure.
     */
-    if( pCsr->pDeferred ){
-      rc = fts3CursorSeek(0, pCsr);
-      if( rc==SQLITE_OK ){
-        rc = sqlite3Fts3CacheDeferredDoclists(pCsr);
-      }
+    if( newValue==sqlite3Fts3HashInsert(pTerms, pTerm, nTerm, newValue) ){
+      rc = SQLITE_NOMEM;
+    }else{
+      rc = leavesReaderStep(v, &reader);
     }
-    bMiss = (0==fts3EvalTestExpr(pCsr, pCsr->pExpr, &rc));
-
-    /* Free the position-lists accumulated for each deferred token above. */
-    sqlite3Fts3FreeDeferredDoclists(pCsr);
-    *pRc = rc;
   }
-  return (rc==SQLITE_OK && bMiss);
+
+  leavesReaderDestroy(&reader);
+  return rc;
 }
 
-/*
-** Advance to the next document that matches the FTS expression in
-** Fts3Cursor.pExpr.
-*/
-static int fts3EvalNext(Fts3Cursor *pCsr){
-  int rc = SQLITE_OK;             /* Return Code */
-  Fts3Expr *pExpr = pCsr->pExpr;
-  assert( pCsr->isEof==0 );
-  if( pExpr==0 ){
-    pCsr->isEof = 1;
-  }else{
-    do {
-      if( pCsr->isRequireSeek==0 ){
-        sqlite3_reset(pCsr->pStmt);
-      }
-      assert( sqlite3_data_count(pCsr->pStmt)==0 );
-      fts3EvalNextRow(pCsr, pExpr, &rc);
-      pCsr->isEof = pExpr->bEof;
-      pCsr->isRequireSeek = 1;
-      pCsr->isMatchinfoNeeded = 1;
-      pCsr->iPrevId = pExpr->iDocid;
-    }while( pCsr->isEof==0 && sqlite3Fts3EvalTestDeferred(pCsr, &rc) );
-  }
-
-  /* Check if the cursor is past the end of the docid range specified
-  ** by Fts3Cursor.iMinDocid/iMaxDocid. If so, set the EOF flag.  */
-  if( rc==SQLITE_OK && (
-        (pCsr->bDesc==0 && pCsr->iPrevId>pCsr->iMaxDocid)
-     || (pCsr->bDesc!=0 && pCsr->iPrevId<pCsr->iMinDocid)
-  )){
-    pCsr->isEof = 1;
+/* Helper function to build the result string for dump_terms(). */
+static int generateTermsResult(sqlite3_context *pContext, fts3Hash *pTerms){
+  int iTerm, nTerms, nResultBytes, iByte;
+  char *result;
+  TermData *pData;
+  fts3HashElem *e;
+
+  /* Iterate pTerms to generate an array of terms in pData for
+  ** sorting.
+  */
+  nTerms = fts3HashCount(pTerms);
+  assert( nTerms>0 );
+  pData = sqlite3_malloc(nTerms*sizeof(TermData));
+  if( pData==NULL ) return SQLITE_NOMEM;
+
+  nResultBytes = 0;
+  for(iTerm = 0, e = fts3HashFirst(pTerms); e; iTerm++, e = fts3HashNext(e)){
+    nResultBytes += fts3HashKeysize(e)+1;   /* Term plus trailing space */
+    assert( iTerm<nTerms );
+    pData[iTerm].pTerm = fts3HashKey(e);
+    pData[iTerm].nTerm = fts3HashKeysize(e);
+    pData[iTerm].pCollector = fts3HashData(e);  /* unused */
+  }
+  assert( iTerm==nTerms );
+
+  assert( nResultBytes>0 );   /* nTerms>0, nResultsBytes must be, too. */
+  result = sqlite3_malloc(nResultBytes);
+  if( result==NULL ){
+    sqlite3_free(pData);
+    return SQLITE_NOMEM;
   }
 
-  return rc;
+  if( nTerms>1 ) qsort(pData, nTerms, sizeof(*pData), termDataCmp);
+
+  /* Read the terms in order to build the result. */
+  iByte = 0;
+  for(iTerm=0; iTerm<nTerms; ++iTerm){
+    memcpy(result+iByte, pData[iTerm].pTerm, pData[iTerm].nTerm);
+    iByte += pData[iTerm].nTerm;
+    result[iByte++] = ' ';
+  }
+  assert( iByte==nResultBytes );
+  assert( result[nResultBytes-1]==' ' );
+  result[nResultBytes-1] = '\0';
+
+  /* Passes away ownership of result. */
+  sqlite3_result_text(pContext, result, nResultBytes-1, sqlite3_free);
+  sqlite3_free(pData);
+  return SQLITE_OK;
 }
 
-/*
-** Restart interation for expression pExpr so that the next call to
-** fts3EvalNext() visits the first row. Do not allow incremental 
-** loading or merging of phrase doclists for this iteration.
-**
-** If *pRc is other than SQLITE_OK when this function is called, it is
-** a no-op. If an error occurs within this function, *pRc is set to an
-** SQLite error code before returning.
-*/
-static void fts3EvalRestart(
-  Fts3Cursor *pCsr,
-  Fts3Expr *pExpr,
-  int *pRc
-){
-  if( pExpr && *pRc==SQLITE_OK ){
-    Fts3Phrase *pPhrase = pExpr->pPhrase;
+/* Implements dump_terms() for use in inspecting the fts3 index from
+** tests.  TEXT result containing the ordered list of terms joined by
+** spaces.  dump_terms(t, level, idx) dumps the terms for the segment
+** specified by level, idx (in %_segdir), while dump_terms(t) dumps
+** all terms in the index.  In both cases t is the fts table's magic
+** table-named column.
+*/
+static void dumpTermsFunc(
+  sqlite3_context *pContext,
+  int argc, sqlite3_value **argv
+){
+  fulltext_cursor *pCursor;
+  if( argc!=3 && argc!=1 ){
+    generateError(pContext, "dump_terms", "incorrect arguments");
+  }else if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
+            sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
+    generateError(pContext, "dump_terms", "illegal first argument");
+  }else{
+    fulltext_vtab *v;
+    fts3Hash terms;
+    sqlite3_stmt *s = NULL;
+    int rc;
 
-    if( pPhrase ){
-      fts3EvalInvalidatePoslist(pPhrase);
-      if( pPhrase->bIncr ){
-        int i;
-        for(i=0; i<pPhrase->nToken; i++){
-          Fts3PhraseToken *pToken = &pPhrase->aToken[i];
-          assert( pToken->pDeferred==0 );
-          if( pToken->pSegcsr ){
-            sqlite3Fts3MsrIncrRestart(pToken->pSegcsr);
-          }
+    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
+    v = cursor_vtab(pCursor);
+
+    /* If passed only the cursor column, get all segments.  Otherwise
+    ** get the segment described by the following two arguments.
+    */
+    if( argc==1 ){
+      rc = sql_get_statement(v, SEGDIR_SELECT_ALL_STMT, &s);
+    }else{
+      rc = sql_get_statement(v, SEGDIR_SELECT_SEGMENT_STMT, &s);
+      if( rc==SQLITE_OK ){
+        rc = sqlite3_bind_int(s, 1, sqlite3_value_int(argv[1]));
+        if( rc==SQLITE_OK ){
+          rc = sqlite3_bind_int(s, 2, sqlite3_value_int(argv[2]));
         }
-        *pRc = fts3EvalPhraseStart(pCsr, 0, pPhrase);
       }
-      pPhrase->doclist.pNextDocid = 0;
-      pPhrase->doclist.iDocid = 0;
-      pPhrase->pOrPoslist = 0;
     }
 
-    pExpr->iDocid = 0;
-    pExpr->bEof = 0;
-    pExpr->bStart = 0;
-
-    fts3EvalRestart(pCsr, pExpr->pLeft, pRc);
-    fts3EvalRestart(pCsr, pExpr->pRight, pRc);
-  }
-}
+    if( rc!=SQLITE_OK ){
+      generateError(pContext, "dump_terms", NULL);
+      return;
+    }
 
-/*
-** After allocating the Fts3Expr.aMI[] array for each phrase in the 
-** expression rooted at pExpr, the cursor iterates through all rows matched
-** by pExpr, calling this function for each row. This function increments
-** the values in Fts3Expr.aMI[] according to the position-list currently
-** found in Fts3Expr.pPhrase->doclist.pList for each of the phrase 
-** expression nodes.
-*/
-static void fts3EvalUpdateCounts(Fts3Expr *pExpr){
-  if( pExpr ){
-    Fts3Phrase *pPhrase = pExpr->pPhrase;
-    if( pPhrase && pPhrase->doclist.pList ){
-      int iCol = 0;
-      char *p = pPhrase->doclist.pList;
+    /* Collect the terms for each segment. */
+    sqlite3Fts3HashInit(&terms, FTS3_HASH_STRING, 1);
+    while( (rc = sqlite3_step(s))==SQLITE_ROW ){
+      rc = collectSegmentTerms(v, s, &terms);
+      if( rc!=SQLITE_OK ) break;
+    }
 
-      assert( *p );
-      while( 1 ){
-        u8 c = 0;
-        int iCnt = 0;
-        while( 0xFE & (*p | c) ){
-          if( (c&0x80)==0 ) iCnt++;
-          c = *p++ & 0x80;
+    if( rc!=SQLITE_DONE ){
+      sqlite3_reset(s);
+      generateError(pContext, "dump_terms", NULL);
+    }else{
+      const int nTerms = fts3HashCount(&terms);
+      if( nTerms>0 ){
+        rc = generateTermsResult(pContext, &terms);
+        if( rc==SQLITE_NOMEM ){
+          generateError(pContext, "dump_terms", "out of memory");
+        }else{
+          assert( rc==SQLITE_OK );
         }
-
-        /* aMI[iCol*3 + 1] = Number of occurrences
-        ** aMI[iCol*3 + 2] = Number of rows containing at least one instance
+      }else if( argc==3 ){
+        /* The specific segment asked for could not be found. */
+        generateError(pContext, "dump_terms", "segment not found");
+      }else{
+        /* No segments found. */
+        /* TODO(shess): It should be impossible to reach this.  This
+        ** case can only happen for an empty table, in which case
+        ** SQLite has no rows to call this function on.
         */
-        pExpr->aMI[iCol*3 + 1] += iCnt;
-        pExpr->aMI[iCol*3 + 2] += (iCnt>0);
-        if( *p==0x00 ) break;
-        p++;
-        p += fts3GetVarint32(p, &iCol);
+        sqlite3_result_null(pContext);
       }
     }
-
-    fts3EvalUpdateCounts(pExpr->pLeft);
-    fts3EvalUpdateCounts(pExpr->pRight);
+    sqlite3Fts3HashClear(&terms);
   }
 }
 
-/*
-** Expression pExpr must be of type FTSQUERY_PHRASE.
-**
-** If it is not already allocated and populated, this function allocates and
-** populates the Fts3Expr.aMI[] array for expression pExpr. If pExpr is part
-** of a NEAR expression, then it also allocates and populates the same array
-** for all other phrases that are part of the NEAR expression.
-**
-** SQLITE_OK is returned if the aMI[] array is successfully allocated and
-** populated. Otherwise, if an error occurs, an SQLite error code is returned.
-*/
-static int fts3EvalGatherStats(
-  Fts3Cursor *pCsr,               /* Cursor object */
-  Fts3Expr *pExpr                 /* FTSQUERY_PHRASE expression */
-){
-  int rc = SQLITE_OK;             /* Return code */
-
-  assert( pExpr->eType==FTSQUERY_PHRASE );
-  if( pExpr->aMI==0 ){
-    Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-    Fts3Expr *pRoot;                /* Root of NEAR expression */
-    Fts3Expr *p;                    /* Iterator used for several purposes */
-
-    sqlite3_int64 iPrevId = pCsr->iPrevId;
-    sqlite3_int64 iDocid;
-    u8 bEof;
-
-    /* Find the root of the NEAR expression */
-    pRoot = pExpr;
-    while( pRoot->pParent && pRoot->pParent->eType==FTSQUERY_NEAR ){
-      pRoot = pRoot->pParent;
-    }
-    iDocid = pRoot->iDocid;
-    bEof = pRoot->bEof;
-    assert( pRoot->bStart );
-
-    /* Allocate space for the aMSI[] array of each FTSQUERY_PHRASE node */
-    for(p=pRoot; p; p=p->pLeft){
-      Fts3Expr *pE = (p->eType==FTSQUERY_PHRASE?p:p->pRight);
-      assert( pE->aMI==0 );
-      pE->aMI = (u32 *)sqlite3_malloc(pTab->nColumn * 3 * sizeof(u32));
-      if( !pE->aMI ) return SQLITE_NOMEM;
-      memset(pE->aMI, 0, pTab->nColumn * 3 * sizeof(u32));
-    }
-
-    fts3EvalRestart(pCsr, pRoot, &rc);
-
-    while( pCsr->isEof==0 && rc==SQLITE_OK ){
-
-      do {
-        /* Ensure the %_content statement is reset. */
-        if( pCsr->isRequireSeek==0 ) sqlite3_reset(pCsr->pStmt);
-        assert( sqlite3_data_count(pCsr->pStmt)==0 );
-
-        /* Advance to the next document */
-        fts3EvalNextRow(pCsr, pRoot, &rc);
-        pCsr->isEof = pRoot->bEof;
-        pCsr->isRequireSeek = 1;
-        pCsr->isMatchinfoNeeded = 1;
-        pCsr->iPrevId = pRoot->iDocid;
-      }while( pCsr->isEof==0 
-           && pRoot->eType==FTSQUERY_NEAR 
-           && sqlite3Fts3EvalTestDeferred(pCsr, &rc) 
-      );
+/* Expand the DL_DEFAULT doclist in pData into a text result in
+** pContext.
+*/
+static void createDoclistResult(sqlite3_context *pContext,
+                                const char *pData, int nData){
+  DataBuffer dump;
+  DLReader dlReader;
 
-      if( rc==SQLITE_OK && pCsr->isEof==0 ){
-        fts3EvalUpdateCounts(pRoot);
-      }
-    }
+  assert( pData!=NULL && nData>0 );
 
-    pCsr->isEof = 0;
-    pCsr->iPrevId = iPrevId;
+  dataBufferInit(&dump, 0);
+  dlrInit(&dlReader, DL_DEFAULT, pData, nData);
+  for( ; !dlrAtEnd(&dlReader); dlrStep(&dlReader) ){
+    char buf[256];
+    PLReader plReader;
 
-    if( bEof ){
-      pRoot->bEof = bEof;
+    plrInit(&plReader, &dlReader);
+    if( DL_DEFAULT==DL_DOCIDS || plrAtEnd(&plReader) ){
+      sqlite3_snprintf(sizeof(buf), buf, "[%lld] ", dlrDocid(&dlReader));
+      dataBufferAppend(&dump, buf, strlen(buf));
     }else{
-      /* Caution: pRoot may iterate through docids in ascending or descending
-      ** order. For this reason, even though it seems more defensive, the 
-      ** do loop can not be written:
-      **
-      **   do {...} while( pRoot->iDocid<iDocid && rc==SQLITE_OK );
-      */
-      fts3EvalRestart(pCsr, pRoot, &rc);
-      do {
-        fts3EvalNextRow(pCsr, pRoot, &rc);
-        assert( pRoot->bEof==0 );
-      }while( pRoot->iDocid!=iDocid && rc==SQLITE_OK );
-    }
-  }
-  return rc;
-}
+      int iColumn = plrColumn(&plReader);
 
-/*
-** This function is used by the matchinfo() module to query a phrase 
-** expression node for the following information:
-**
-**   1. The total number of occurrences of the phrase in each column of 
-**      the FTS table (considering all rows), and
-**
-**   2. For each column, the number of rows in the table for which the
-**      column contains at least one instance of the phrase.
-**
-** If no error occurs, SQLITE_OK is returned and the values for each column
-** written into the array aiOut as follows:
-**
-**   aiOut[iCol*3 + 1] = Number of occurrences
-**   aiOut[iCol*3 + 2] = Number of rows containing at least one instance
-**
-** Caveats:
-**
-**   * If a phrase consists entirely of deferred tokens, then all output 
-**     values are set to the number of documents in the table. In other
-**     words we assume that very common tokens occur exactly once in each 
-**     column of each row of the table.
-**
-**   * If a phrase contains some deferred tokens (and some non-deferred 
-**     tokens), count the potential occurrence identified by considering
-**     the non-deferred tokens instead of actual phrase occurrences.
-**
-**   * If the phrase is part of a NEAR expression, then only phrase instances
-**     that meet the NEAR constraint are included in the counts.
-*/
-int sqlite3Fts3EvalPhraseStats(
-  Fts3Cursor *pCsr,               /* FTS cursor handle */
-  Fts3Expr *pExpr,                /* Phrase expression */
-  u32 *aiOut                      /* Array to write results into (see above) */
-){
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-  int rc = SQLITE_OK;
-  int iCol;
+      sqlite3_snprintf(sizeof(buf), buf, "[%lld %d[",
+                       dlrDocid(&dlReader), iColumn);
+      dataBufferAppend(&dump, buf, strlen(buf));
+
+      for( ; !plrAtEnd(&plReader); plrStep(&plReader) ){
+        if( plrColumn(&plReader)!=iColumn ){
+          iColumn = plrColumn(&plReader);
+          sqlite3_snprintf(sizeof(buf), buf, "] %d[", iColumn);
+          assert( dump.nData>0 );
+          dump.nData--;                     /* Overwrite trailing space. */
+          assert( dump.pData[dump.nData]==' ');
+          dataBufferAppend(&dump, buf, strlen(buf));
+        }
+        if( DL_DEFAULT==DL_POSITIONS_OFFSETS ){
+          sqlite3_snprintf(sizeof(buf), buf, "%d,%d,%d ",
+                           plrPosition(&plReader),
+                           plrStartOffset(&plReader), plrEndOffset(&plReader));
+        }else if( DL_DEFAULT==DL_POSITIONS ){
+          sqlite3_snprintf(sizeof(buf), buf, "%d ", plrPosition(&plReader));
+        }else{
+          assert( NULL=="Unhandled DL_DEFAULT value");
+        }
+        dataBufferAppend(&dump, buf, strlen(buf));
+      }
+      plrDestroy(&plReader);
 
-  if( pExpr->bDeferred && pExpr->pParent->eType!=FTSQUERY_NEAR ){
-    assert( pCsr->nDoc>0 );
-    for(iCol=0; iCol<pTab->nColumn; iCol++){
-      aiOut[iCol*3 + 1] = (u32)pCsr->nDoc;
-      aiOut[iCol*3 + 2] = (u32)pCsr->nDoc;
-    }
+      assert( dump.nData>0 );
+      dump.nData--;                     /* Overwrite trailing space. */
+      assert( dump.pData[dump.nData]==' ');
+      dataBufferAppend(&dump, "]] ", 3);
+    }
+  }
+  dlrDestroy(&dlReader);
+
+  assert( dump.nData>0 );
+  dump.nData--;                     /* Overwrite trailing space. */
+  assert( dump.pData[dump.nData]==' ');
+  dump.pData[dump.nData] = '\0';
+  assert( dump.nData>0 );
+
+  /* Passes ownership of dump's buffer to pContext. */
+  sqlite3_result_text(pContext, dump.pData, dump.nData, sqlite3_free);
+  dump.pData = NULL;
+  dump.nData = dump.nCapacity = 0;
+}
+
+/* Implements dump_doclist() for use in inspecting the fts3 index from
+** tests.  TEXT result containing a string representation of the
+** doclist for the indicated term.  dump_doclist(t, term, level, idx)
+** dumps the doclist for term from the segment specified by level, idx
+** (in %_segdir), while dump_doclist(t, term) dumps the logical
+** doclist for the term across all segments.  The per-segment doclist
+** can contain deletions, while the full-index doclist will not
+** (deletions are omitted).
+**
+** Result formats differ with the setting of DL_DEFAULTS.  Examples:
+**
+** DL_DOCIDS: [1] [3] [7]
+** DL_POSITIONS: [1 0[0 4] 1[17]] [3 1[5]]
+** DL_POSITIONS_OFFSETS: [1 0[0,0,3 4,23,26] 1[17,102,105]] [3 1[5,20,23]]
+**
+** In each case the number after the outer '[' is the docid.  In the
+** latter two cases, the number before the inner '[' is the column
+** associated with the values within.  For DL_POSITIONS the numbers
+** within are the positions, for DL_POSITIONS_OFFSETS they are the
+** position, the start offset, and the end offset.
+*/
+static void dumpDoclistFunc(
+  sqlite3_context *pContext,
+  int argc, sqlite3_value **argv
+){
+  fulltext_cursor *pCursor;
+  if( argc!=2 && argc!=4 ){
+    generateError(pContext, "dump_doclist", "incorrect arguments");
+  }else if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
+            sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
+    generateError(pContext, "dump_doclist", "illegal first argument");
+  }else if( sqlite3_value_text(argv[1])==NULL ||
+            sqlite3_value_text(argv[1])[0]=='\0' ){
+    generateError(pContext, "dump_doclist", "empty second argument");
   }else{
-    rc = fts3EvalGatherStats(pCsr, pExpr);
-    if( rc==SQLITE_OK ){
-      assert( pExpr->aMI );
-      for(iCol=0; iCol<pTab->nColumn; iCol++){
-        aiOut[iCol*3 + 1] = pExpr->aMI[iCol*3 + 1];
-        aiOut[iCol*3 + 2] = pExpr->aMI[iCol*3 + 2];
-      }
-    }
-  }
+    const char *pTerm = (const char *)sqlite3_value_text(argv[1]);
+    const int nTerm = strlen(pTerm);
+    fulltext_vtab *v;
+    int rc;
+    DataBuffer doclist;
 
-  return rc;
-}
+    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
+    v = cursor_vtab(pCursor);
 
-/*
-** The expression pExpr passed as the second argument to this function
-** must be of type FTSQUERY_PHRASE. 
-**
-** The returned value is either NULL or a pointer to a buffer containing
-** a position-list indicating the occurrences of the phrase in column iCol
-** of the current row. 
-**
-** More specifically, the returned buffer contains 1 varint for each 
-** occurrence of the phrase in the column, stored using the normal (delta+2) 
-** compression and is terminated by either an 0x01 or 0x00 byte. For example,
-** if the requested column contains "a b X c d X X" and the position-list
-** for 'X' is requested, the buffer returned may contain:
-**
-**     0x04 0x05 0x03 0x01   or   0x04 0x05 0x03 0x00
-**
-** This function works regardless of whether or not the phrase is deferred,
-** incremental, or neither.
-*/
-int sqlite3Fts3EvalPhrasePoslist(
-  Fts3Cursor *pCsr,               /* FTS3 cursor object */
-  Fts3Expr *pExpr,                /* Phrase to return doclist for */
-  int iCol,                       /* Column to return position list for */
-  char **ppOut                    /* OUT: Pointer to position list */
-){
-  Fts3Phrase *pPhrase = pExpr->pPhrase;
-  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
-  char *pIter;
-  int iThis;
-  sqlite3_int64 iDocid;
-
-  /* If this phrase is applies specifically to some column other than 
-  ** column iCol, return a NULL pointer.  */
-  *ppOut = 0;
-  assert( iCol>=0 && iCol<pTab->nColumn );
-  if( (pPhrase->iColumn<pTab->nColumn && pPhrase->iColumn!=iCol) ){
-    return SQLITE_OK;
-  }
+    dataBufferInit(&doclist, 0);
 
-  iDocid = pExpr->iDocid;
-  pIter = pPhrase->doclist.pList;
-  if( iDocid!=pCsr->iPrevId || pExpr->bEof ){
-    int rc = SQLITE_OK;
-    int bDescDoclist = pTab->bDescIdx;      /* For DOCID_CMP macro */
-    int bOr = 0;
-    u8 bTreeEof = 0;
-    Fts3Expr *p;                  /* Used to iterate from pExpr to root */
-    Fts3Expr *pNear;              /* Most senior NEAR ancestor (or pExpr) */
-    int bMatch;
-
-    /* Check if this phrase descends from an OR expression node. If not, 
-    ** return NULL. Otherwise, the entry that corresponds to docid 
-    ** pCsr->iPrevId may lie earlier in the doclist buffer. Or, if the
-    ** tree that the node is part of has been marked as EOF, but the node
-    ** itself is not EOF, then it may point to an earlier entry. */
-    pNear = pExpr;
-    for(p=pExpr->pParent; p; p=p->pParent){
-      if( p->eType==FTSQUERY_OR ) bOr = 1;
-      if( p->eType==FTSQUERY_NEAR ) pNear = p;
-      if( p->bEof ) bTreeEof = 1;
-    }
-    if( bOr==0 ) return SQLITE_OK;
-
-    /* This is the descendent of an OR node. In this case we cannot use
-    ** an incremental phrase. Load the entire doclist for the phrase
-    ** into memory in this case.  */
-    if( pPhrase->bIncr ){
-      int bEofSave = pNear->bEof;
-      fts3EvalRestart(pCsr, pNear, &rc);
-      while( rc==SQLITE_OK && !pNear->bEof ){
-        fts3EvalNextRow(pCsr, pNear, &rc);
-        if( bEofSave==0 && pNear->iDocid==iDocid ) break;
-      }
-      assert( rc!=SQLITE_OK || pPhrase->bIncr==0 );
-    }
-    if( bTreeEof ){
-      while( rc==SQLITE_OK && !pNear->bEof ){
-        fts3EvalNextRow(pCsr, pNear, &rc);
+    /* termSelect() yields the same logical doclist that queries are
+    ** run against.
+    */
+    if( argc==2 ){
+      rc = termSelect(v, v->nColumn, pTerm, nTerm, 0, DL_DEFAULT, &doclist);
+    }else{
+      sqlite3_stmt *s = NULL;
+
+      /* Get our specific segment's information. */
+      rc = sql_get_statement(v, SEGDIR_SELECT_SEGMENT_STMT, &s);
+      if( rc==SQLITE_OK ){
+        rc = sqlite3_bind_int(s, 1, sqlite3_value_int(argv[2]));
+        if( rc==SQLITE_OK ){
+          rc = sqlite3_bind_int(s, 2, sqlite3_value_int(argv[3]));
+        }
       }
-    }
-    if( rc!=SQLITE_OK ) return rc;
 
-    bMatch = 1;
-    for(p=pNear; p; p=p->pLeft){
-      u8 bEof = 0;
-      Fts3Expr *pTest = p;
-      Fts3Phrase *pPh;
-      assert( pTest->eType==FTSQUERY_NEAR || pTest->eType==FTSQUERY_PHRASE );
-      if( pTest->eType==FTSQUERY_NEAR ) pTest = pTest->pRight;
-      assert( pTest->eType==FTSQUERY_PHRASE );
-      pPh = pTest->pPhrase;
-
-      pIter = pPh->pOrPoslist;
-      iDocid = pPh->iOrDocid;
-      if( pCsr->bDesc==bDescDoclist ){
-        bEof = !pPh->doclist.nAll ||
-          (pIter >= (pPh->doclist.aAll + pPh->doclist.nAll));
-        while( (pIter==0 || DOCID_CMP(iDocid, pCsr->iPrevId)<0 ) && bEof==0 ){
-          sqlite3Fts3DoclistNext(
-              bDescDoclist, pPh->doclist.aAll, pPh->doclist.nAll, 
-              &pIter, &iDocid, &bEof
-          );
+      if( rc==SQLITE_OK ){
+        rc = sqlite3_step(s);
+
+        if( rc==SQLITE_DONE ){
+          dataBufferDestroy(&doclist);
+          generateError(pContext, "dump_doclist", "segment not found");
+          return;
         }
-      }else{
-        bEof = !pPh->doclist.nAll || (pIter && pIter<=pPh->doclist.aAll);
-        while( (pIter==0 || DOCID_CMP(iDocid, pCsr->iPrevId)>0 ) && bEof==0 ){
-          int dummy;
-          sqlite3Fts3DoclistPrev(
-              bDescDoclist, pPh->doclist.aAll, pPh->doclist.nAll, 
-              &pIter, &iDocid, &dummy, &bEof
-              );
+
+        /* Found a segment, load it into doclist. */
+        if( rc==SQLITE_ROW ){
+          const sqlite_int64 iLeavesEnd = sqlite3_column_int64(s, 1);
+          const char *pData = sqlite3_column_blob(s, 2);
+          const int nData = sqlite3_column_bytes(s, 2);
+
+          /* loadSegment() is used by termSelect() to load each
+          ** segment's data.
+          */
+          rc = loadSegment(v, pData, nData, iLeavesEnd, pTerm, nTerm, 0,
+                           &doclist);
+          if( rc==SQLITE_OK ){
+            rc = sqlite3_step(s);
+
+            /* Should not have more than one matching segment. */
+            if( rc!=SQLITE_DONE ){
+              sqlite3_reset(s);
+              dataBufferDestroy(&doclist);
+              generateError(pContext, "dump_doclist", "invalid segdir");
+              return;
+            }
+            rc = SQLITE_OK;
+          }
         }
       }
-      pPh->pOrPoslist = pIter;
-      pPh->iOrDocid = iDocid;
-      if( bEof || iDocid!=pCsr->iPrevId ) bMatch = 0;
+
+      sqlite3_reset(s);
     }
 
-    if( bMatch ){
-      pIter = pPhrase->pOrPoslist;
+    if( rc==SQLITE_OK ){
+      if( doclist.nData>0 ){
+        createDoclistResult(pContext, doclist.pData, doclist.nData);
+      }else{
+        /* TODO(shess): This can happen if the term is not present, or
+        ** if all instances of the term have been deleted and this is
+        ** an all-index dump.  It may be interesting to distinguish
+        ** these cases.
+        */
+        sqlite3_result_text(pContext, "", 0, SQLITE_STATIC);
+      }
+    }else if( rc==SQLITE_NOMEM ){
+      /* Handle out-of-memory cases specially because if they are
+      ** generated in fts3 code they may not be reflected in the db
+      ** handle.
+      */
+      /* TODO(shess): Handle this more comprehensively.
+      ** sqlite3ErrStr() has what I need, but is internal.
+      */
+      generateError(pContext, "dump_doclist", "out of memory");
     }else{
-      pIter = 0;
+      generateError(pContext, "dump_doclist", NULL);
     }
-  }
-  if( pIter==0 ) return SQLITE_OK;
 
-  if( *pIter==0x01 ){
-    pIter++;
-    pIter += fts3GetVarint32(pIter, &iThis);
-  }else{
-    iThis = 0;
-  }
-  while( iThis<iCol ){
-    fts3ColumnlistCopy(0, &pIter);
-    if( *pIter==0x00 ) return SQLITE_OK;
-    pIter++;
-    pIter += fts3GetVarint32(pIter, &iThis);
-  }
-  if( *pIter==0x00 ){
-    pIter = 0;
+    dataBufferDestroy(&doclist);
   }
+}
+#endif
 
-  *ppOut = ((iCol==iThis)?pIter:0);
-  return SQLITE_OK;
+/*
+** This routine implements the xFindFunction method for the FTS3
+** virtual table.
+*/
+static int fulltextFindFunction(
+  sqlite3_vtab *pVtab,
+  int nArg,
+  const char *zName,
+  void (**pxFunc)(sqlite3_context*,int,sqlite3_value**),
+  void **ppArg
+){
+  if( strcmp(zName,"snippet")==0 ){
+    *pxFunc = snippetFunc;
+    return 1;
+  }else if( strcmp(zName,"offsets")==0 ){
+    *pxFunc = snippetOffsetsFunc;
+    return 1;
+  }else if( strcmp(zName,"optimize")==0 ){
+    *pxFunc = optimizeFunc;
+    return 1;
+#ifdef SQLITE_TEST
+    /* NOTE(shess): These functions are present only for testing
+    ** purposes.  No particular effort is made to optimize their
+    ** execution or how they build their results.
+    */
+  }else if( strcmp(zName,"dump_terms")==0 ){
+    /* fprintf(stderr, "Found dump_terms\n"); */
+    *pxFunc = dumpTermsFunc;
+    return 1;
+  }else if( strcmp(zName,"dump_doclist")==0 ){
+    /* fprintf(stderr, "Found dump_doclist\n"); */
+    *pxFunc = dumpDoclistFunc;
+    return 1;
+#endif
+  }
+  return 0;
 }
 
 /*
-** Free all components of the Fts3Phrase structure that were allocated by
-** the eval module. Specifically, this means to free:
-**
-**   * the contents of pPhrase->doclist, and
-**   * any Fts3MultiSegReader objects held by phrase tokens.
+** Rename an fts3 table.
 */
-void sqlite3Fts3EvalPhraseCleanup(Fts3Phrase *pPhrase){
-  if( pPhrase ){
-    int i;
-    sqlite3_free(pPhrase->doclist.aAll);
-    fts3EvalInvalidatePoslist(pPhrase);
-    memset(&pPhrase->doclist, 0, sizeof(Fts3Doclist));
-    for(i=0; i<pPhrase->nToken; i++){
-      fts3SegReaderCursorFree(pPhrase->aToken[i].pSegcsr);
-      pPhrase->aToken[i].pSegcsr = 0;
-    }
+static int fulltextRename(
+  sqlite3_vtab *pVtab,
+  const char *zName
+){
+  fulltext_vtab *p = (fulltext_vtab *)pVtab;
+  int rc = SQLITE_NOMEM;
+  char *zSql = sqlite3_mprintf(
+    "ALTER TABLE %Q.'%q_content'  RENAME TO '%q_content';"
+    "ALTER TABLE %Q.'%q_segments' RENAME TO '%q_segments';"
+    "ALTER TABLE %Q.'%q_segdir'   RENAME TO '%q_segdir';"
+    , p->zDb, p->zName, zName 
+    , p->zDb, p->zName, zName 
+    , p->zDb, p->zName, zName
+  );
+  if( zSql ){
+    rc = sqlite3_exec(p->db, zSql, 0, 0, 0);
+    sqlite3_free(zSql);
   }
+  return rc;
 }
 
+static const sqlite3_module fts3Module = {
+  /* iVersion      */ 0,
+  /* xCreate       */ fulltextCreate,
+  /* xConnect      */ fulltextConnect,
+  /* xBestIndex    */ fulltextBestIndex,
+  /* xDisconnect   */ fulltextDisconnect,
+  /* xDestroy      */ fulltextDestroy,
+  /* xOpen         */ fulltextOpen,
+  /* xClose        */ fulltextClose,
+  /* xFilter       */ fulltextFilter,
+  /* xNext         */ fulltextNext,
+  /* xEof          */ fulltextEof,
+  /* xColumn       */ fulltextColumn,
+  /* xRowid        */ fulltextRowid,
+  /* xUpdate       */ fulltextUpdate,
+  /* xBegin        */ fulltextBegin,
+  /* xSync         */ fulltextSync,
+  /* xCommit       */ fulltextCommit,
+  /* xRollback     */ fulltextRollback,
+  /* xFindFunction */ fulltextFindFunction,
+  /* xRename */       fulltextRename,
+};
+
+static void hashDestroy(void *p){
+  fts3Hash *pHash = (fts3Hash *)p;
+  sqlite3Fts3HashClear(pHash);
+  sqlite3_free(pHash);
+}
 
 /*
-** Return SQLITE_CORRUPT_VTAB.
+** The fts3 built-in tokenizers - "simple" and "porter" - are implemented
+** in files fts3_tokenizer1.c and fts3_porter.c respectively. The following
+** two forward declarations are for functions declared in these files
+** used to retrieve the respective implementations.
+**
+** Calling sqlite3Fts3SimpleTokenizerModule() sets the value pointed
+** to by the argument to point a the "simple" tokenizer implementation.
+** Function ...PorterTokenizerModule() sets *pModule to point to the
+** porter tokenizer/stemmer implementation.
 */
-#ifdef SQLITE_DEBUG
-int sqlite3Fts3Corrupt(){
-  return SQLITE_CORRUPT_VTAB;
-}
-#endif
+void sqlite3Fts3SimpleTokenizerModule(sqlite3_tokenizer_module const**ppModule);
+void sqlite3Fts3PorterTokenizerModule(sqlite3_tokenizer_module const**ppModule);
+void sqlite3Fts3IcuTokenizerModule(sqlite3_tokenizer_module const**ppModule);
+
+int sqlite3Fts3InitHashTable(sqlite3 *, fts3Hash *, const char *);
 
-#if !SQLITE_CORE
 /*
-** Initialize API pointer table, if required.
+** Initialise the fts3 extension. If this extension is built as part
+** of the sqlite library, then this function is called directly by
+** SQLite. If fts3 is built as a dynamically loadable extension, this
+** function is called by the sqlite3_extension_init() entry point.
 */
-#ifdef _WIN32
-__declspec(dllexport)
+int sqlite3Fts3Init(sqlite3 *db){
+  int rc = SQLITE_OK;
+  fts3Hash *pHash = 0;
+  const sqlite3_tokenizer_module *pSimple = 0;
+  const sqlite3_tokenizer_module *pPorter = 0;
+  const sqlite3_tokenizer_module *pIcu = 0;
+
+  sqlite3Fts3SimpleTokenizerModule(&pSimple);
+  sqlite3Fts3PorterTokenizerModule(&pPorter);
+#ifdef SQLITE_ENABLE_ICU
+  sqlite3Fts3IcuTokenizerModule(&pIcu);
+#endif
+
+  /* Allocate and initialise the hash-table used to store tokenizers. */
+  pHash = sqlite3_malloc(sizeof(fts3Hash));
+  if( !pHash ){
+    rc = SQLITE_NOMEM;
+  }else{
+    sqlite3Fts3HashInit(pHash, FTS3_HASH_STRING, 1);
+  }
+
+  /* Load the built-in tokenizers into the hash table */
+  if( rc==SQLITE_OK ){
+    if( sqlite3Fts3HashInsert(pHash, "simple", 7, (void *)pSimple)
+     || sqlite3Fts3HashInsert(pHash, "porter", 7, (void *)pPorter) 
+     || (pIcu && sqlite3Fts3HashInsert(pHash, "icu", 4, (void *)pIcu))
+    ){
+      rc = SQLITE_NOMEM;
+    }
+  }
+
+#ifdef SQLITE_TEST
+  sqlite3Fts3ExprInitTestInterface(db);
+#endif
+
+  /* Create the virtual table wrapper around the hash-table and overload 
+  ** the two scalar functions. If this is successful, register the
+  ** module with sqlite.
+  */
+  if( SQLITE_OK==rc 
+   && SQLITE_OK==(rc = sqlite3Fts3InitHashTable(db, pHash, "fts3_tokenizer"))
+   && SQLITE_OK==(rc = sqlite3_overload_function(db, "snippet", -1))
+   && SQLITE_OK==(rc = sqlite3_overload_function(db, "offsets", -1))
+   && SQLITE_OK==(rc = sqlite3_overload_function(db, "optimize", -1))
+#ifdef SQLITE_TEST
+   && SQLITE_OK==(rc = sqlite3_overload_function(db, "dump_terms", -1))
+   && SQLITE_OK==(rc = sqlite3_overload_function(db, "dump_doclist", -1))
 #endif
-int sqlite3_fts3_init(
+  ){
+    return sqlite3_create_module_v2(
+        db, "fts3", &fts3Module, (void *)pHash, hashDestroy
+    );
+  }
+
+  /* An error has occurred. Delete the hash table and return the error code. */
+  assert( rc!=SQLITE_OK );
+  if( pHash ){
+    sqlite3Fts3HashClear(pHash);
+    sqlite3_free(pHash);
+  }
+  return rc;
+}
+
+#if !SQLITE_CORE
+int sqlite3_extension_init(
   sqlite3 *db, 
   char **pzErrMsg,
   const sqlite3_api_routines *pApi
 ){
   SQLITE_EXTENSION_INIT2(pApi)
   return sqlite3Fts3Init(db);
 }
 #endif
 
-#endif
+#endif /* !defined(SQLITE_CORE) || defined(SQLITE_ENABLE_FTS3) */
