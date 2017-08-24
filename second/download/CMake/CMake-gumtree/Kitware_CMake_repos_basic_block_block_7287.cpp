r(op = OIDtable; op->numoid; op++)
    if(!strcmp(op->numoid, oid) || strcasecompare(op->textoid, oid))
      return op;