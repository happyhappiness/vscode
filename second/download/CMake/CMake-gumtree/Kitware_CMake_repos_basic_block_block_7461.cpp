{
    BINDING *b = bindings;
    bindings = bindings->nextTagBinding;
    b->nextTagBinding = freeBindingList;
    freeBindingList = b;
  }