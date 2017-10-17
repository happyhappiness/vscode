        zCsr += len;
        len = sqlite3GetToken(zCsr, &token);
      } while( token==TK_SPACE );
      assert( len>0 );
    } while( token!=TK_LP && token!=TK_USING );

    zRet = sqlite3MPrintf(db, "%.*s\"%w\"%s", ((u8*)tname.z) - zSql, zSql, 
       zTableName, tname.z+tname.n);
    sqlite3_result_text(context, zRet, -1, SQLITE_DYNAMIC);
  }
}

#ifndef SQLITE_OMIT_TRIGGER
/* This function is used by SQL generated to implement the
** ALTER TABLE command. The first argument is the text of a CREATE TRIGGER 
** statement. The second is a table name. The table name in the CREATE 
** TRIGGER statement is replaced with the third argument and the result 
** returned. This is analagous to renameTableFunc() above, except for CREATE
