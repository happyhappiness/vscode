{
    // Emit x* as (x&|), where & means "self".
    reginsert(BRANCH, ret);         // Either x
    regoptail(ret, regnode(BACK));  // and loop
    regoptail(ret, ret);            // back
    regtail(ret, regnode(BRANCH));  // or
    regtail(ret, regnode(NOTHING)); // null.
  }