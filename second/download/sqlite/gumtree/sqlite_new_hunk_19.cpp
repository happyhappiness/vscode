      }
    } while( dist!=2 || (token!=TK_WHEN && token!=TK_FOR && token!=TK_BEGIN) );

    /* Variable tname now contains the token that is the old table-name
    ** in the CREATE TRIGGER statement.
    */
    zRet = sqlite3MPrintf(db, "%.*s\"%w\"%s", ((u8*)tname.z) - zSql, zSql, 
       zTableName, tname.z+tname.n);
    sqlite3_result_text(context, zRet, -1, SQLITE_DYNAMIC);
  }
}
#endif   /* !SQLITE_OMIT_TRIGGER */

/*
** Register built-in functions used to help implement ALTER TABLE
*/
void sqlite3AlterFunctions(sqlite3 *db){
  sqlite3CreateFunc(db, "sqlite_rename_table", 2, SQLITE_UTF8, 0,
                         renameTableFunc, 0, 0);
#ifndef SQLITE_OMIT_TRIGGER
  sqlite3CreateFunc(db, "sqlite_rename_trigger", 2, SQLITE_UTF8, 0,
                         renameTriggerFunc, 0, 0);
#endif
}

/*
** Generate the text of a WHERE expression which can be used to select all
** temporary triggers on table pTab from the sqlite_temp_master table. If
** table pTab has no temporary triggers, or is itself stored in the 
** temporary database, NULL is returned.
*/
static char *whereTempTriggers(Parse *pParse, Table *pTab){
  Trigger *pTrig;
  char *zWhere = 0;
  char *tmp = 0;
  const Schema *pTempSchema = pParse->db->aDb[1].pSchema; /* Temp db schema */

  /* If the table is not located in the temp-db (in which case NULL is 
  ** returned, loop through the tables list of triggers. For each trigger
  ** that is not part of the temp-db schema, add a clause to the WHERE 
  ** expression being built up in zWhere.
  */
  if( pTab->pSchema!=pTempSchema ){
    sqlite3 *db = pParse->db;
    for(pTrig=sqlite3TriggerList(pParse, pTab); pTrig; pTrig=pTrig->pNext){
      if( pTrig->pSchema==pTempSchema ){
        if( !zWhere ){
          zWhere = sqlite3MPrintf(db, "name=%Q", pTrig->name);
        }else{
          tmp = zWhere;
          zWhere = sqlite3MPrintf(db, "%s OR name=%Q", zWhere, pTrig->name);
          sqlite3DbFree(db, tmp);
        }
      }
    }
  }
  return zWhere;
}

/*
** Generate code to drop and reload the internal representation of table
** pTab from the database, including triggers and temporary triggers.
