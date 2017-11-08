local voidpf falloc(q, n, s)
voidpf q;        /* opaque pointer (not used) */
uInt n;         /* number of items */
uInt s;         /* size of item */
{
  Assert(s == sizeof(inflate_huft) && n <= fixed_left,
         "inflate_trees falloc overflow");
  if (q) s++; /* to make some compilers happy */
  fixed_left -= n;
  return (voidpf)(fixed_mem + fixed_left);
}