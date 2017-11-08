static BOOL
compile_regex(int options, int optchanged, int *brackets, uschar **codeptr,
  const uschar **ptrptr, const char **errorptr, BOOL lookbehind, int skipbytes,
  int *reqchar, int *countlits, compile_data *cd)
{
const uschar *ptr = *ptrptr;
uschar *code = *codeptr;
uschar *last_branch = code;
uschar *start_bracket = code;
uschar *reverse_count = NULL;
int oldoptions = options & PCRE_IMS;
int branchreqchar, branchcountlits;

*reqchar = -1;
*countlits = INT_MAX;
code += 3 + skipbytes;

/* Loop for each alternative branch */

for (;;)
  {
  int length;

  /* Handle change of options */

  if (optchanged >= 0)
    {
    *code++ = OP_OPT;
    *code++ = optchanged;
    options = (options & ~PCRE_IMS) | optchanged;
    }

  /* Set up dummy OP_REVERSE if lookbehind assertion */

  if (lookbehind)
    {
    *code++ = OP_REVERSE;
    reverse_count = code;
    *code++ = 0;
    *code++ = 0;
    }

  /* Now compile the branch */

  if (!compile_branch(options, brackets, &code, &ptr, errorptr, &optchanged,
      &branchreqchar, &branchcountlits, cd))
    {
    *ptrptr = ptr;
    return FALSE;
    }

  /* Fill in the length of the last branch */

  length = code - last_branch;
  last_branch[1] = length >> 8;
  last_branch[2] = length & 255;

  /* Save the last required character if all branches have the same; a current
  value of -1 means unset, while -2 means "previous branch had no last required
  char".  */

  if (*reqchar != -2)
    {
    if (branchreqchar >= 0)
      {
      if (*reqchar == -1) *reqchar = branchreqchar;
      else if (*reqchar != branchreqchar) *reqchar = -2;
      }
    else *reqchar = -2;
    }

  /* Keep the shortest literal count */

  if (branchcountlits < *countlits) *countlits = branchcountlits;
  DPRINTF(("literal count = %d min=%d\n", branchcountlits, *countlits));

  /* If lookbehind, check that this branch matches a fixed-length string,
  and put the length into the OP_REVERSE item. Temporarily mark the end of
  the branch with OP_END. */

  if (lookbehind)
    {
    *code = OP_END;
    length = find_fixedlength(last_branch, options);
    DPRINTF(("fixed length = %d\n", length));
    if (length < 0)
      {
      *errorptr = ERR25;
      *ptrptr = ptr;
      return FALSE;
      }
    reverse_count[0] = (length >> 8);
    reverse_count[1] = length & 255;
    }

  /* Reached end of expression, either ')' or end of pattern. Insert a
  terminating ket and the length of the whole bracketed item, and return,
  leaving the pointer at the terminating char. If any of the ims options
  were changed inside the group, compile a resetting op-code following. */

  if (*ptr != '|')
    {
    length = code - start_bracket;
    *code++ = OP_KET;
    *code++ = length >> 8;
    *code++ = length & 255;
    if (optchanged >= 0)
      {
      *code++ = OP_OPT;
      *code++ = oldoptions;
      }
    *codeptr = code;
    *ptrptr = ptr;
    return TRUE;
    }

  /* Another branch follows; insert an "or" node and advance the pointer. */

  *code = OP_ALT;
  last_branch = code;
  code += 3;
  ptr++;
  }
/* Control never reaches here */
}