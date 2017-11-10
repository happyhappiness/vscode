static BOOL
compile_regex(int options, int oldims, int *brackets, uschar **codeptr,
  const uschar **ptrptr, const char **errorptr, BOOL lookbehind, int skipbytes,
  int *firstbyteptr, int *reqbyteptr, branch_chain *bcptr, compile_data *cd)
{
const uschar *ptr = *ptrptr;
uschar *code = *codeptr;
uschar *last_branch = code;
uschar *start_bracket = code;
uschar *reverse_count = NULL;
int firstbyte, reqbyte;
int branchfirstbyte, branchreqbyte;
branch_chain bc;

bc.outer = bcptr;
bc.current = code;

firstbyte = reqbyte = REQ_UNSET;

/* Offset is set zero to mark that this bracket is still open */

PUT(code, 1, 0);
code += 1 + LINK_SIZE + skipbytes;

/* Loop for each alternative branch */

for (;;)
  {
  /* Handle a change of ims options at the start of the branch */

  if ((options & PCRE_IMS) != oldims)
    {
    *code++ = OP_OPT;
    *code++ = options & PCRE_IMS;
    }

  /* Set up dummy OP_REVERSE if lookbehind assertion */

  if (lookbehind)
    {
    *code++ = OP_REVERSE;
    reverse_count = code;
    PUTINC(code, 0, 0);
    }

  /* Now compile the branch */

  if (!compile_branch(&options, brackets, &code, &ptr, errorptr,
        &branchfirstbyte, &branchreqbyte, &bc, cd))
    {
    *ptrptr = ptr;
    return FALSE;
    }

  /* If this is the first branch, the firstbyte and reqbyte values for the
  branch become the values for the regex. */

  if (*last_branch != OP_ALT)
    {
    firstbyte = branchfirstbyte;
    reqbyte = branchreqbyte;
    }

  /* If this is not the first branch, the first char and reqbyte have to
  match the values from all the previous branches, except that if the previous
  value for reqbyte didn't have REQ_VARY set, it can still match, and we set
  REQ_VARY for the regex. */

  else
    {
    /* If we previously had a firstbyte, but it doesn't match the new branch,
    we have to abandon the firstbyte for the regex, but if there was previously
    no reqbyte, it takes on the value of the old firstbyte. */

    if (firstbyte >= 0 && firstbyte != branchfirstbyte)
      {
      if (reqbyte < 0) reqbyte = firstbyte;
      firstbyte = REQ_NONE;
      }

    /* If we (now or from before) have no firstbyte, a firstbyte from the
    branch becomes a reqbyte if there isn't a branch reqbyte. */

    if (firstbyte < 0 && branchfirstbyte >= 0 && branchreqbyte < 0)
        branchreqbyte = branchfirstbyte;

    /* Now ensure that the reqbytes match */

    if ((reqbyte & ~REQ_VARY) != (branchreqbyte & ~REQ_VARY))
      reqbyte = REQ_NONE;
    else reqbyte |= branchreqbyte;   /* To "or" REQ_VARY */
    }

  /* If lookbehind, check that this branch matches a fixed-length string,
  and put the length into the OP_REVERSE item. Temporarily mark the end of
  the branch with OP_END. */

  if (lookbehind)
    {
    int length;
    *code = OP_END;
    length = find_fixedlength(last_branch, options);
    DPRINTF(("fixed length = %d\n", length));
    if (length < 0)
      {
      *errorptr = (length == -2)? ERR36 : ERR25;
      *ptrptr = ptr;
      return FALSE;
      }
    PUT(reverse_count, 0, length);
    }

  /* Reached end of expression, either ')' or end of pattern. Go back through
  the alternative branches and reverse the chain of offsets, with the field in
  the BRA item now becoming an offset to the first alternative. If there are
  no alternatives, it points to the end of the group. The length in the
  terminating ket is always the length of the whole bracketed item. If any of
  the ims options were changed inside the group, compile a resetting op-code
  following, except at the very end of the pattern. Return leaving the pointer
  at the terminating char. */

  if (*ptr != '|')
    {
    int length = code - last_branch;
    do
      {
      int prev_length = GET(last_branch, 1);
      PUT(last_branch, 1, length);
      length = prev_length;
      last_branch -= length;
      }
    while (length > 0);

    /* Fill in the ket */

    *code = OP_KET;
    PUT(code, 1, code - start_bracket);
    code += 1 + LINK_SIZE;

    /* Resetting option if needed */

    if ((options & PCRE_IMS) != oldims && *ptr == ')')
    