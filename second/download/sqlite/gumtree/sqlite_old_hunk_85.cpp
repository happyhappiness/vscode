        }
        a[k].pExpr = 0;
      }else{
        /* This expression is a "*" or a "TABLE.*" and needs to be
        ** expanded. */
        int tableSeen = 0;      /* Set to 1 when TABLE matches */
        char *zTName = 0;       /* text of name of TABLE */
        if( pE->op==TK_DOT ){
          assert( pE->pLeft!=0 );
          assert( !ExprHasProperty(pE->pLeft, EP_IntValue) );
          zTName = pE->pLeft->u.zToken;
        }
        for(i=0, pFrom=pTabList->a; i<pTabList->nSrc; i++, pFrom++){
          Table *pTab = pFrom->pTab;
          Select *pSub = pFrom->pSelect;
          char *zTabName = pFrom->zAlias;
          const char *zSchemaName = 0;
          int iDb;
          if( zTabName==0 ){
            zTabName = pTab->zName;
          }
          if( db->mallocFailed ) break;
          if( pSub==0 || (pSub->selFlags & SF_NestedFrom)==0 ){
            pSub = 0;
            if( zTName && sqlite3StrICmp(zTName, zTabName)!=0 ){
              continue;
            }
            iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
            zSchemaName = iDb>=0 ? db->aDb[iDb].zDbSName : "*";
          }
          for(j=0; j<pTab->nCol; j++){
            char *zName = pTab->aCol[j].zName;
            char *zColname;  /* The computed column name */
            char *zToFree;   /* Malloced string that needs to be freed */
            Token sColname;  /* Computed column name as a token */

            assert( zName );
            if( zTName && pSub
             && sqlite3MatchSpanName(pSub->pEList->a[j].zSpan, 0, zTName, 0)==0
            ){
              continue;
            }

            /* If a column is marked as 'hidden', omit it from the expanded
            ** result-set list unless the SELECT has the SF_IncludeHidden
            ** bit set.
            */
            if( (p->selFlags & SF_IncludeHidden)==0
             && IsHiddenColumn(&pTab->aCol[j]) 
            ){
              continue;
            }
            tableSeen = 1;

            if( i>0 && zTName==0 ){
              if( (pFrom->fg.jointype & JT_NATURAL)!=0
                && tableAndColumnIndex(pTabList, i, zName, 0, 0)
              ){
                /* In a NATURAL join, omit the join columns from the 
                ** table to the right of the join */
                continue;
              }
              if( sqlite3IdListIndex(pFrom->pUsing, zName)>=0 ){
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
              pExpr = sqlite3PExpr(pParse, TK_DOT, pLeft, pRight);
              if( zSchemaName ){
                pLeft = sqlite3Expr(db, TK_ID, zSchemaName);
                pExpr = sqlite3PExpr(pParse, TK_DOT, pLeft, pExpr);
              }
              if( longNames ){
                zColname = sqlite3MPrintf(db, "%s.%s", zTabName, zName);
                zToFree = zColname;
              }
            }else{
              pExpr = pRight;
            }
            pNew = sqlite3ExprListAppend(pParse, pNew, pExpr);
            sqlite3TokenInit(&sColname, zColname);
            sqlite3ExprListSetName(pParse, pNew, &sColname, 0);
            if( pNew && (p->selFlags & SF_NestedFrom)!=0 ){
              struct ExprList_item *pX = &pNew->a[pNew->nExpr-1];
              if( pSub ){
                pX->zSpan = sqlite3DbStrDup(db, pSub->pEList->a[j].zSpan);
                testcase( pX->zSpan==0 );
              }else{
                pX->zSpan = sqlite3MPrintf(db, "%s.%s.%s",
                                           zSchemaName, zTabName, zColname);
                testcase( pX->zSpan==0 );
              }
              pX->bSpanIsTab = 1;
            }
            sqlite3DbFree(db, zToFree);
          }
        }
        if( !tableSeen ){
          if( zTName ){
            sqlite3ErrorMsg(pParse, "no such table: %s", zTName);
