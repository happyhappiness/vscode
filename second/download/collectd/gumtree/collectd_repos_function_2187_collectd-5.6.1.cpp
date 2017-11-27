static void lu_destroy_user_obj (lookup_t *obj, /* {{{ */
    user_obj_t *user_obj)
{
  while (user_obj != NULL)
  {
    user_obj_t *next = user_obj->next;

    if (obj->cb_free_obj != NULL)
      obj->cb_free_obj (user_obj->user_obj);
    user_obj->user_obj = NULL;

    sfree (user_obj);
    user_obj = next;
  }
}