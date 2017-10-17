static void explainComposite(
  Parse *pParse,                  /* Parse context */
  int op,                         /* One of TK_UNION, TK_EXCEPT etc. */
  int iSub1,                      /* Subquery id 1 */
  int iSub2,                      /* Subquery id 2 */
  int bUseTmp                     /* True if a temp table was used */
){
  assert( op==TK_UNION || op==TK_EXCEPT || op==TK_INTERSECT || op==TK_ALL );
  if( pParse->explain==2 ){
    Vdbe *v = pParse->pVdbe;
    char *zMsg = sqlite3MPrintf(
        pParse->db, "COMPOUND SUBQUERIES %d AND %d %s(%s)", iSub1, iSub2,
        bUseTmp?"USING TEMP B-TREE ":"", selectOpName(op)
    );
    sqlite3VdbeAddOp4(v, OP_Explain, pParse->iSelectId, 0, 0, zMsg, P4_DYNAMIC);
  }
}