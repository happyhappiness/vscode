static void destroy_read_heap(void) /* {{{ */
{
  if (read_heap == NULL)
    return;

  while (42) {
    read_func_t *rf;

    rf = c_heap_get_root(read_heap);
    if (rf == NULL)
      break;
    sfree(rf->rf_name);
    destroy_callback((callback_func_t *)rf);
  }

  c_heap_destroy(read_heap);
  read_heap = NULL;
}