f(compare(KEY_NOTUSED, removenode->key) == 0) {
    /* Key set to NOTUSED means it is a subnode within a 'same' linked list
       and thus we can unlink it easily. */
    if(removenode->samen == removenode)
      /* A non-subnode should never be set to KEY_NOTUSED */
      return 3;

    removenode->samep->samen = removenode->samen;
    removenode->samen->samep = removenode->samep;

    /* Ensures that double-remove gets caught. */
    removenode->samen = removenode;

    *newroot = t; /* return the same root */
    return 0;
  }