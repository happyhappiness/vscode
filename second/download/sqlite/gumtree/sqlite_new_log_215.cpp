sqlite3MPrintf(db, "cannot open value of type %s",
          type==0?"null": type==7?"real": "integer"
      );