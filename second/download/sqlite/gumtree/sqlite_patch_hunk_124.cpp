   signed char p2;     /* Second parameter (often the jump destination) */
   signed char p3;     /* Third parameter */
 };
 typedef struct VdbeOpList VdbeOpList;
 
 /*
-** Allowed values of VdbeOp.p4type
+** Allowed values of VdbeOp.p3type
 */
-#define P4_NOTUSED      0   /* The P4 parameter is not used */
-#define P4_TRANSIENT    0   /* P4 is a pointer to a transient string */
-#define P4_STATIC     (-1)  /* Pointer to a static string */
-#define P4_COLLSEQ    (-2)  /* P4 is a pointer to a CollSeq structure */
-#define P4_INT32      (-3)  /* P4 is a 32-bit signed integer */
-#define P4_SUBPROGRAM (-4)  /* P4 is a pointer to a SubProgram structure */
-#define P4_ADVANCE    (-5)  /* P4 is a pointer to BtreeNext() or BtreePrev() */
-#define P4_TABLE      (-6)  /* P4 is a pointer to a Table structure */
-/* Above do not own any resources.  Must free those below */
-#define P4_FREE_IF_LE (-7)
-#define P4_DYNAMIC    (-7)  /* Pointer to memory from sqliteMalloc() */
-#define P4_FUNCDEF    (-8)  /* P4 is a pointer to a FuncDef structure */
-#define P4_KEYINFO    (-9)  /* P4 is a pointer to a KeyInfo structure */
-#define P4_EXPR       (-10) /* P4 is a pointer to an Expr tree */
-#define P4_MEM        (-11) /* P4 is a pointer to a Mem*    structure */
-#define P4_VTAB       (-12) /* P4 is a pointer to an sqlite3_vtab structure */
-#define P4_REAL       (-13) /* P4 is a 64-bit floating point value */
-#define P4_INT64      (-14) /* P4 is a 64-bit signed integer */
-#define P4_INTARRAY   (-15) /* P4 is a vector of 32-bit integers */
-#define P4_FUNCCTX    (-16) /* P4 is a pointer to an sqlite3_context object */
-
-/* Error message codes for OP_Halt */
-#define P5_ConstraintNotNull 1
-#define P5_ConstraintUnique  2
-#define P5_ConstraintCheck   3
-#define P5_ConstraintFK      4
+#define P4_NOTUSED    0   /* The P4 parameter is not used */
+#define P4_DYNAMIC  (-1)  /* Pointer to a string obtained from sqliteMalloc() */
+#define P4_STATIC   (-2)  /* Pointer to a static string */
+#define P4_COLLSEQ  (-4)  /* P4 is a pointer to a CollSeq structure */
+#define P4_FUNCDEF  (-5)  /* P4 is a pointer to a FuncDef structure */
+#define P4_KEYINFO  (-6)  /* P4 is a pointer to a KeyInfo structure */
+#define P4_VDBEFUNC (-7)  /* P4 is a pointer to a VdbeFunc structure */
+#define P4_MEM      (-8)  /* P4 is a pointer to a Mem*    structure */
+#define P4_TRANSIENT (-9) /* P4 is a pointer to a transient string */
+#define P4_VTAB     (-10) /* P4 is a pointer to an sqlite3_vtab structure */
+#define P4_MPRINTF  (-11) /* P4 is a string obtained from sqlite3_mprintf() */
+#define P4_REAL     (-12) /* P4 is a 64-bit floating point value */
+#define P4_INT64    (-13) /* P4 is a 64-bit signed integer */
+#define P4_INT32    (-14) /* P4 is a 32-bit signed integer */
+#define P4_INTARRAY (-15) /* P4 is a vector of 32-bit integers */
+
+/* When adding a P4 argument using P4_KEYINFO, a copy of the KeyInfo structure
+** is made.  That copy is freed when the Vdbe is finalized.  But if the
+** argument is P4_KEYINFO_HANDOFF, the passed in pointer is used.  It still
+** gets freed when the Vdbe is finalized so it still should be obtained
+** from a single sqliteMalloc().  But no copy is made and the calling
+** function should *not* try to free the KeyInfo.
+*/
+#define P4_KEYINFO_HANDOFF (-16)
+#define P4_KEYINFO_STATIC  (-17)
 
 /*
 ** The Vdbe.aColName array contains 5n Mem structures, where n is the 
 ** number of columns of data returned by the statement.
 */
 #define COLNAME_NAME     0
