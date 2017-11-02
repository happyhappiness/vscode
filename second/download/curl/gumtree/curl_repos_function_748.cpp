static void zfree_func(voidpf opaque, voidpf ptr)
{
  (void) opaque;
  free(ptr);
}