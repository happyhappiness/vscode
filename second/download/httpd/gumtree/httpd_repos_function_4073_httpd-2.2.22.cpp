static BOOL
get_othercase_range(int *cptr, int d, int *ocptr, int *odptr)
{
int c, chartype, othercase, next;

for (c = *cptr; c <= d; c++)
  {
  if (ucp_findchar(c, &chartype, &othercase) == ucp_L && othercase != 0) break;
  }

if (c > d) return FALSE;

*ocptr = othercase;
next = othercase + 1;

for (++c; c <= d; c++)
  {
  if (ucp_findchar(c, &chartype, &othercase) != ucp_L || othercase != next)
    break;
  next++;
  }

*odptr = next - 1;
*cptr = c;

return TRUE;
}