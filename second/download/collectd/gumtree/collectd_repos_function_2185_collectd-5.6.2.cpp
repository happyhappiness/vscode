static int lu_handle_user_class_list(lookup_t *obj, /* {{{ */
                                     data_set_t const *ds,
                                     value_list_t const *vl,
                                     user_class_list_t *user_class_list) {
  user_class_list_t *ptr;
  int retval = 0;

  for (ptr = user_class_list; ptr != NULL; ptr = ptr->next) {
    int status;

    status = lu_handle_user_class(obj, ds, vl, &ptr->entry);
    if (status < 0)
      return (status);
    else if (status == 0)
      retval++;
  }

  return (retval);
}