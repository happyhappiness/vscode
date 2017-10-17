  signed char p2;     /* Second parameter (often the jump destination) */
  signed char p3;     /* Third parameter */
};
typedef struct VdbeOpList VdbeOpList;

/*
** Allowed values of VdbeOp.p4type
*/
#define P4_NOTUSED      0   /* The P4 parameter is not used */
#define P4_TRANSIENT    0   /* P4 is a pointer to a transient string */
#define P4_STATIC     (-1)  /* Pointer to a static string */
#define P4_COLLSEQ    (-2)  /* P4 is a pointer to a CollSeq structure */
#define P4_INT32      (-3)  /* P4 is a 32-bit signed integer */
#define P4_SUBPROGRAM (-4)  /* P4 is a pointer to a SubProgram structure */
#define P4_ADVANCE    (-5)  /* P4 is a pointer to BtreeNext() or BtreePrev() */
#define P4_TABLE      (-6)  /* P4 is a pointer to a Table structure */
/* Above do not own any resources.  Must free those below */
#define P4_FREE_IF_LE (-7)
#define P4_DYNAMIC    (-7)  /* Pointer to memory from sqliteMalloc() */
#define P4_FUNCDEF    (-8)  /* P4 is a pointer to a FuncDef structure */
#define P4_KEYINFO    (-9)  /* P4 is a pointer to a KeyInfo structure */
#define P4_EXPR       (-10) /* P4 is a pointer to an Expr tree */
#define P4_MEM        (-11) /* P4 is a pointer to a Mem*    structure */
#define P4_VTAB       (-12) /* P4 is a pointer to an sqlite3_vtab structure */
#define P4_REAL       (-13) /* P4 is a 64-bit floating point value */
#define P4_INT64      (-14) /* P4 is a 64-bit signed integer */
#define P4_INTARRAY   (-15) /* P4 is a vector of 32-bit integers */
#define P4_FUNCCTX    (-16) /* P4 is a pointer to an sqlite3_context object */

/* Error message codes for OP_Halt */
#define P5_ConstraintNotNull 1
#define P5_ConstraintUnique  2
#define P5_ConstraintCheck   3
#define P5_ConstraintFK      4

/*
** The Vdbe.aColName array contains 5n Mem structures, where n is the 
** number of columns of data returned by the statement.
*/
#define COLNAME_NAME     0
