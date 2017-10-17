    }
    pNode->nRef++;
    *ppNode = pNode;
    return SQLITE_OK;
  }

  pNode = (RtreeNode *)sqlite3_malloc(sizeof(RtreeNode) + pRtree->iNodeSize);
  if( !pNode ){
    *ppNode = 0;
    return SQLITE_NOMEM;
  }
  pNode->pParent = pParent;
  pNode->zData = (u8 *)&pNode[1];
  pNode->nRef = 1;
  pNode->iNode = iNode;
  pNode->isDirty = 0;
  pNode->pNext = 0;

  sqlite3_bind_int64(pRtree->pReadNode, 1, iNode);
  rc = sqlite3_step(pRtree->pReadNode);
  if( rc==SQLITE_ROW ){
    const u8 *zBlob = sqlite3_column_blob(pRtree->pReadNode, 0);
    memcpy(pNode->zData, zBlob, pRtree->iNodeSize);
    nodeReference(pParent);
  }else{
    sqlite3_free(pNode);
    pNode = 0;
  }

  *ppNode = pNode;
  rc = sqlite3_reset(pRtree->pReadNode);

  if( rc==SQLITE_OK && iNode==1 ){
    pRtree->iDepth = readInt16(pNode->zData);
  }

  assert( (rc==SQLITE_OK && pNode) || (pNode==0 && rc!=SQLITE_OK) );
  nodeHashInsert(pRtree, pNode);

  return rc;
}

/*
** Overwrite cell iCell of node pNode with the contents of pCell.
*/
static void nodeOverwriteCell(
  Rtree *pRtree, 
  RtreeNode *pNode,  
  RtreeCell *pCell, 
  int iCell
){
  int ii;
  u8 *p = &pNode->zData[4 + pRtree->nBytesPerCell*iCell];
  p += writeInt64(p, pCell->iRowid);
  for(ii=0; ii<(pRtree->nDim*2); ii++){
    p += writeCoord(p, &pCell->aCoord[ii]);
  }
  pNode->isDirty = 1;
}

/*
** Remove cell the cell with index iCell from node pNode.
*/
static void nodeDeleteCell(Rtree *pRtree, RtreeNode *pNode, int iCell){
  u8 *pDst = &pNode->zData[4 + pRtree->nBytesPerCell*iCell];
  u8 *pSrc = &pDst[pRtree->nBytesPerCell];
  int nByte = (NCELL(pNode) - iCell - 1) * pRtree->nBytesPerCell;
  memmove(pDst, pSrc, nByte);
