void glob_cleanup(URLGlob* glob)
{
  size_t i;
  int elem;

  for (i = glob->size - 1; i < glob->size; --i) {
    if (!(i & 1)) {     /* even indexes contain literals */
      free(glob->literal[i/2]);
    }
    else {              /* odd indexes contain sets or ranges */
      if (glob->pattern[i/2].type == UPTSet) {
        for (elem = glob->pattern[i/2].content.Set.size - 1;
             elem >= 0;
             --elem) {
          free(glob->pattern[i/2].content.Set.elements[elem]);
        }
        free(glob->pattern[i/2].content.Set.elements);
      }
    }
  }
  free(glob->glob_buffer);
  free(glob);
}