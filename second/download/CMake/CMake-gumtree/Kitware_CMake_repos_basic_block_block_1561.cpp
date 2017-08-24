{
    // Emit x? as (x|)
    reginsert(BRANCH, ret);        // Either x
    regtail(ret, regnode(BRANCH)); // or
    next = regnode(NOTHING);       // null.
    regtail(ret, next);
    regoptail(ret, next);
  }