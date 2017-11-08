local void ffree(q, p, n)
voidpf q;
voidpf p;
uInt n;
{
  Assert(0, "inflate_trees ffree called!");
  if (q) q = p; /* to make some compilers happy */
}