  sqlite3_step(pRtree->pWriteRowid);
  rc = sqlite3_reset(pRtree->pWriteRowid);
  *piRowid = sqlite3_last_insert_rowid(pRtree->db);
  return rc;
}

#ifndef NDEBUG
static int hashIsEmpty(Rtree *pRtree){
  int ii;
  for(ii=0; ii<HASHSIZE; ii++){
    assert( !pRtree->aHash[ii] );
  }
  return 1;
}
#endif

/*
** The xUpdate method for rtree module virtual tables.
*/
int rtreeUpdate(
  sqlite3_vtab *pVtab, 
  int nData, 
  sqlite3_value **azData, 
  sqlite_int64 *pRowid
){
  Rtree *pRtree = (Rtree *)pVtab;
  int rc = SQLITE_OK;

  rtreeReference(pRtree);

  assert(nData>=1);
  assert(hashIsEmpty(pRtree));

  /* If azData[0] is not an SQL NULL value, it is the rowid of a
  ** record to delete from the r-tree table. The following block does
  ** just that.
  */
  if( sqlite3_value_type(azData[0])!=SQLITE_NULL ){
    i64 iDelete;                /* The rowid to delete */
    RtreeNode *pLeaf;           /* Leaf node containing record iDelete */
    int iCell;                  /* Index of iDelete cell in pLeaf */
    RtreeNode *pRoot;

    /* Obtain a reference to the root node to initialise Rtree.iDepth */
    rc = nodeAcquire(pRtree, 1, 0, &pRoot);

    /* Obtain a reference to the leaf node that contains the entry 
    ** about to be deleted. 
    */
    if( rc==SQLITE_OK ){
      iDelete = sqlite3_value_int64(azData[0]);
      rc = findLeafNode(pRtree, iDelete, &pLeaf);
    }

    /* Delete the cell in question from the leaf node. */
    if( rc==SQLITE_OK ){
      int rc2;
      iCell = nodeRowidIndex(pRtree, pLeaf, iDelete);
      rc = deleteCell(pRtree, pLeaf, iCell, 0);
      rc2 = nodeRelease(pRtree, pLeaf);
      if( rc==SQLITE_OK ){
        rc = rc2;
      }
    }

    /* Delete the corresponding entry in the <rtree>_rowid table. */
    if( rc==SQLITE_OK ){
      sqlite3_bind_int64(pRtree->pDeleteRowid, 1, iDelete);
      sqlite3_step(pRtree->pDeleteRowid);
      rc = sqlite3_reset(pRtree->pDeleteRowid);
    }

    /* Check if the root node now has exactly one child. If so, remove
    ** it, schedule the contents of the child for reinsertion and 
    ** reduce the tree height by one.
    **
    ** This is equivalent to copying the contents of the child into
    ** the root node (the operation that Gutman's paper says to perform 
    ** in this scenario).
    */
    if( rc==SQLITE_OK && pRtree->iDepth>0 ){
      if( rc==SQLITE_OK && NCELL(pRoot)==1 ){
        RtreeNode *pChild;
        i64 iChild = nodeGetRowid(pRtree, pRoot, 0);
        rc = nodeAcquire(pRtree, iChild, pRoot, &pChild);
        if( rc==SQLITE_OK ){
          rc = removeNode(pRtree, pChild, pRtree->iDepth-1);
        }
        if( rc==SQLITE_OK ){
          pRtree->iDepth--;
          writeInt16(pRoot->zData, pRtree->iDepth);
          pRoot->isDirty = 1;
        }
      }
    }

    /* Re-insert the contents of any underfull nodes removed from the tree. */
    for(pLeaf=pRtree->pDeleted; pLeaf; pLeaf=pRtree->pDeleted){
      if( rc==SQLITE_OK ){
        rc = reinsertNodeContent(pRtree, pLeaf);
      }
      pRtree->pDeleted = pLeaf->pNext;
      sqlite3_free(pLeaf);
    }

    /* Release the reference to the root node. */
    if( rc==SQLITE_OK ){
      rc = nodeRelease(pRtree, pRoot);
    }else{
      nodeRelease(pRtree, pRoot);
    }
  }

  /* If the azData[] array contains more than one element, elements
  ** (azData[2]..azData[argc-1]) contain a new record to insert into
  ** the r-tree structure.
  */
  if( rc==SQLITE_OK && nData>1 ){
    /* Insert a new record into the r-tree */
    RtreeCell cell;
    int ii;
    RtreeNode *pLeaf;

    /* Populate the cell.aCoord[] array. The first coordinate is azData[3]. */
    assert( nData==(pRtree->nDim*2 + 3) );
    if( pRtree->eCoordType==RTREE_COORD_REAL32 ){
      for(ii=0; ii<(pRtree->nDim*2); ii+=2){
        cell.aCoord[ii].f = (float)sqlite3_value_double(azData[ii+3]);
        cell.aCoord[ii+1].f = (float)sqlite3_value_double(azData[ii+4]);
        if( cell.aCoord[ii].f>cell.aCoord[ii+1].f ){
          rc = SQLITE_CONSTRAINT;
          goto constraint;
        }
      }
    }else{
      for(ii=0; ii<(pRtree->nDim*2); ii+=2){
        cell.aCoord[ii].i = sqlite3_value_int(azData[ii+3]);
        cell.aCoord[ii+1].i = sqlite3_value_int(azData[ii+4]);
        if( cell.aCoord[ii].i>cell.aCoord[ii+1].i ){
          rc = SQLITE_CONSTRAINT;
          goto constraint;
        }
      }
    }

    /* Figure out the rowid of the new row. */
    if( sqlite3_value_type(azData[2])==SQLITE_NULL ){
      rc = newRowid(pRtree, &cell.iRowid);
    }else{
      cell.iRowid = sqlite3_value_int64(azData[2]);
      sqlite3_bind_int64(pRtree->pReadRowid, 1, cell.iRowid);
      if( SQLITE_ROW==sqlite3_step(pRtree->pReadRowid) ){
        sqlite3_reset(pRtree->pReadRowid);
        rc = SQLITE_CONSTRAINT;
        goto constraint;
      }
      rc = sqlite3_reset(pRtree->pReadRowid);
    }

    if( rc==SQLITE_OK ){
      rc = ChooseLeaf(pRtree, &cell, 0, &pLeaf);
    }
    if( rc==SQLITE_OK ){
      int rc2;
