int cu_tail_destroy(cu_tail_t *obj) {
  if (obj->fh != NULL)
    fclose(obj->fh);
  free(obj->file);
  free(obj);

  return 0;
}