{
    // Emit x+ as x(&|), where & means "self".
    next = regnode(BRANCH); // Either
    regtail(ret, next);
    regtail(regnode(BACK), ret);    // loop back
    regtail(next, regnode(BRANCH)); // or
    regtail(ret, regnode(NOTHING)); // null.
  }