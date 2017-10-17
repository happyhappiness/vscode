  int iErr = (argc<6) ? 2 : argc>(RTREE_MAX_DIMENSIONS*2+4) ? 3 : argc%2;
  if( aErrMsg[iErr] ){
    *pzErr = sqlite3_mprintf("%s", aErrMsg[iErr]);
    return SQLITE_ERROR;
  }

  rc = getPageSize(db, argv[1], &iPageSize);
  if( rc!=SQLITE_OK ){
    return rc;
  }

  /* Allocate the sqlite3_vtab structure */
  nDb = strlen(argv[1]);
  nName = strlen(argv[2]);
  pRtree = (Rtree *)sqlite3_malloc(sizeof(Rtree)+nDb+nName+2);
  if( !pRtree ){
    return SQLITE_NOMEM;
  }
  memset(pRtree, 0, sizeof(Rtree)+nDb+nName+2);
  pRtree->nBusy = 1;
  pRtree->base.pModule = &rtreeModule;
  pRtree->zDb = (char *)&pRtree[1];
  pRtree->zName = &pRtree->zDb[nDb+1];
  pRtree->nDim = (argc-4)/2;
  pRtree->nBytesPerCell = 8 + pRtree->nDim*4*2;
  pRtree->eCoordType = eCoordType;
  memcpy(pRtree->zDb, argv[1], nDb);
  memcpy(pRtree->zName, argv[2], nName);

  /* Figure out the node size to use. By default, use 64 bytes less than
  ** the database page-size. This ensures that each node is stored on
  ** a single database page.
  **
  ** If the databasd page-size is so large that more than RTREE_MAXCELLS
  ** entries would fit in a single node, use a smaller node-size.
  */
  pRtree->iNodeSize = iPageSize-64;
  if( (4+pRtree->nBytesPerCell*RTREE_MAXCELLS)<pRtree->iNodeSize ){
    pRtree->iNodeSize = 4+pRtree->nBytesPerCell*RTREE_MAXCELLS;
  }

  /* Create/Connect to the underlying relational database schema. If
  ** that is successful, call sqlite3_declare_vtab() to configure
  ** the r-tree table schema.
  */
  if( (rc = rtreeSqlInit(pRtree, db, argv[1], argv[2], isCreate)) ){
    *pzErr = sqlite3_mprintf("%s", sqlite3_errmsg(db));
  }else{
    char *zSql = sqlite3_mprintf("CREATE TABLE x(%s", argv[3]);
    char *zTmp;
    int ii;
    for(ii=4; zSql && ii<argc; ii++){
      zTmp = zSql;
      zSql = sqlite3_mprintf("%s, %s", zTmp, argv[ii]);
      sqlite3_free(zTmp);
    }
    if( zSql ){
      zTmp = zSql;
      zSql = sqlite3_mprintf("%s);", zTmp);
      sqlite3_free(zTmp);
    }
    if( !zSql || sqlite3_declare_vtab(db, zSql) ){
      rc = SQLITE_NOMEM;
    }
    sqlite3_free(zSql);
  }

  if( rc==SQLITE_OK ){
    *ppVtab = (sqlite3_vtab *)pRtree;
  }else{
    rtreeRelease(pRtree);
  }
  return rc;
}


/*
** Implementation of a scalar function that decodes r-tree nodes to
** human readable strings. This can be used for debugging and analysis.
**
** The scalar function takes two arguments, a blob of data containing
** an r-tree node, and the number of dimensions the r-tree indexes.
** For a two-dimensional r-tree structure called "rt", to deserialize
** all nodes, a statement like:
**
**   SELECT rtreenode(2, data) FROM rt_node;
**
** The human readable string takes the form of a Tcl list with one
** entry for each cell in the r-tree node. Each entry is itself a
** list, containing the 8-byte rowid/pageno followed by the 
