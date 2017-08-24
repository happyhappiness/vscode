f(insert_wrapped_ptr(&ssl->obj_list, obj) != CURLE_OK) {
    PK11_DestroyGenericObject(obj);
    return CURLE_OUT_OF_MEMORY;
  }