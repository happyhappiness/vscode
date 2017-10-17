    ** A shared-cache write-lock is not required to write to the new table,
    ** as a schema-lock must have already been obtained to create it. Since
    ** a schema-lock excludes all other database users, the write-lock would
    ** be redundant.
    */
    if( pSelect ){
      SelectDest dest;
      Table *pSelTab;

      assert(pParse->nTab==1);
      sqlite3VdbeAddOp3(v, OP_OpenWrite, 1, pParse->regRoot, iDb);
      sqlite3VdbeChangeP5(v, 1);
      pParse->nTab = 2;
      sqlite3SelectDestInit(&dest, SRT_Table, 1);
      sqlite3Select(pParse, pSelect, &dest);
      sqlite3VdbeAddOp1(v, OP_Close, 1);
      if( pParse->nErr==0 ){
        pSelTab = sqlite3ResultSetOfSelect(pParse, pSelect);
        if( pSelTab==0 ) return;
        assert( p->aCol==0 );
        p->nCol = pSelTab->nCol;
        p->aCol = pSelTab->aCol;
        pSelTab->nCol = 0;
        pSelTab->aCol = 0;
        sqlite3DeleteTable(pSelTab);
      }
    }

    /* Compute the complete text of the CREATE statement */
    if( pSelect ){
      zStmt = createTableStmt(db, p);
    }else{
      n = (int)(pEnd->z - pParse->sNameToken.z) + 1;
      zStmt = sqlite3MPrintf(db, 
          "CREATE %s %.*s", zType2, n, pParse->sNameToken.z
      );
    }

    /* A slot for the record has already been allocated in the 
