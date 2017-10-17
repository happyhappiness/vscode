        }
        a[k].pExpr = 0;
      }else{
        /* This expression is a "*" or a "TABLE.*" and needs to be
        ** expanded. */
        int tableSeen = 0;      /* Set to 1 when TABLE matches */
        char *zTName;            /* text of name of TABLE */
        if( pE->op==TK_DOT ){
          assert( pE->pLeft!=0 );
          assert( !ExprHasProperty(pE->pLeft, EP_IntValue) );
          zTName = pE->pLeft->u.zToken;
        }else{
          zTName = 0;
        }
        for(i=0, pFrom=pTabList->a; i<pTabList->nSrc; i++, pFrom++){
          Table *pTab = pFrom->pTab;
          char *zTabName = pFrom->zAlias;
          if( zTabName==0 ){
            zTabName = pTab->zName;
          }
          if( db->mallocFailed ) break;
          if( zTName && sqlite3StrICmp(zTName, zTabName)!=0 ){
            continue;
          }
          tableSeen = 1;
          for(j=0; j<pTab->nCol; j++){
            Expr *pExpr, *pRight;
            char *zName = pTab->aCol[j].zName;
            char *zColname;  /* The computed column name */
            char *zToFree;   /* Malloced string that needs to be freed */
            Token sColname;  /* Computed column name as a token */

            /* If a column is marked as 'hidden' (currently only possible
            ** for virtual tables), do not include it in the expanded
            ** result-set list.
            */
            if( IsHiddenColumn(&pTab->aCol[j]) ){
              assert(IsVirtual(pTab));
              continue;
            }

            if( i>0 && zTName==0 ){
              struct SrcList_item *pLeft = &pTabList->a[i-1];
              if( (pLeft[1].jointype & JT_NATURAL)!=0 &&
                        columnIndex(pLeft->pTab, zName)>=0 ){
                /* In a NATURAL join, omit the join columns from the 
                ** table on the right */
                continue;
              }
              if( sqlite3IdListIndex(pLeft[1].pUsing, zName)>=0 ){
                /* In a join with a USING clause, omit columns in the
                ** using clause from the table on the right. */
                continue;
              }
            }
            pRight = sqlite3Expr(db, TK_ID, zName);
            zColname = zName;
            zToFree = 0;
            if( longNames || pTabList->nSrc>1 ){
              Expr *pLeft;
              pLeft = sqlite3Expr(db, TK_ID, zTabName);
              pExpr = sqlite3PExpr(pParse, TK_DOT, pLeft, pRight, 0);
              if( longNames ){
                zColname = sqlite3MPrintf(db, "%s.%s", zTabName, zName);
                zToFree = zColname;
              }
            }else{
              pExpr = pRight;
            }
            pNew = sqlite3ExprListAppend(pParse, pNew, pExpr);
            sColname.z = zColname;
            sColname.n = sqlite3Strlen30(zColname);
            sqlite3ExprListSetName(pParse, pNew, &sColname, 0);
            sqlite3DbFree(db, zToFree);
          }
        }
        if( !tableSeen ){
          if( zTName ){
            sqlite3ErrorMsg(pParse, "no such table: %s", zTName);
