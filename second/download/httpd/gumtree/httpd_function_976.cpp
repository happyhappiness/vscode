static BOOL
match(register const uschar *eptr, register const uschar *ecode,
  int offset_top, match_data *md, unsigned long int ims, eptrblock *eptrb,
  int flags)
{
unsigned long int original_ims = ims;   /* Save for resetting on ')' */
eptrblock newptrb;

/* At the start of a bracketed group, add the current subject pointer to the
stack of such pointers, to be re-instated at the end of the group when we hit
the closing ket. When match() is called in other circumstances, we don't add to
the stack. */

if ((flags & match_isgroup) != 0)
  {
  newptrb.prev = eptrb;
  newptrb.saved_eptr = eptr;
  eptrb = &newptrb;
  }

/* Now start processing the operations. */

for (;;)
  {
  int op = (int)*ecode;
  int min, max, ctype;
  register int i;
  register int c;
  BOOL minimize = FALSE;

  /* Opening capturing bracket. If there is space in the offset vector, save
  the current subject position in the working slot at the top of the vector. We
  mustn't change the current values of the data slot, because they may be set
  from a previous iteration of this group, and be referred to by a reference
  inside the group.

  If the bracket fails to match, we need to restore this value and also the
  values of the final offsets, in case they were set by a previous iteration of
  the same bracket.

  If there isn't enough space in the offset vector, treat this as if it were a
  non-capturing bracket. Don't worry about setting the flag for the error case
  here; that is handled in the code for KET. */

  if (op > OP_BRA)
    {
    int offset;
    int number = op - OP_BRA;

    /* For extended extraction brackets (large number), we have to fish out the
    number from a dummy opcode at the start. */

    if (number > EXTRACT_BASIC_MAX) number = (ecode[4] << 8) | ecode[5];
    offset = number << 1;

#ifdef DEBUG
    printf("start bracket %d subject=", number);
    pchars(eptr, 16, TRUE, md);
    printf("\n");
#endif

    if (offset < md->offset_max)
      {
      int save_offset1 = md->offset_vector[offset];
      int save_offset2 = md->offset_vector[offset+1];
      int save_offset3 = md->offset_vector[md->offset_end - number];

      DPRINTF(("saving %d %d %d\n", save_offset1, save_offset2, save_offset3));
      md->offset_vector[md->offset_end - number] = eptr - md->start_subject;

      do
        {
        if (match(eptr, ecode+3, offset_top, md, ims, eptrb, match_isgroup))
          return TRUE;
        ecode += (ecode[1] << 8) + ecode[2];
        }
      while (*ecode == OP_ALT);

      DPRINTF(("bracket %d failed\n", number));

      md->offset_vector[offset] = save_offset1;
      md->offset_vector[offset+1] = save_offset2;
      md->offset_vector[md->offset_end - number] = save_offset3;

      return FALSE;
      }

    /* Insufficient room for saving captured contents */

    else op = OP_BRA;
    }

  /* Other types of node can be handled by a switch */

  switch(op)
    {
    case OP_BRA:     /* Non-capturing bracket: optimized */
    DPRINTF(("start bracket 0\n"));
    do
      {
      if (match(eptr, ecode+3, offset_top, md, ims, eptrb, match_isgroup))
        return TRUE;
      ecode += (ecode[1] << 8) + ecode[2];
      }
    while (*ecode == OP_ALT);
    DPRINTF(("bracket 0 failed\n"));
    return FALSE;

    /* Conditional group: compilation checked that there are no more than
    two branches. If the condition is false, skipping the first branch takes us
    past the end if there is only one branch, but that's OK because that is
    exactly what going to the ket would do. */

    case OP_COND:
    if (ecode[3] == OP_CREF)         /* Condition is extraction test */
      {
      int offset = (ecode[4] << 9) | (ecode[5] << 1); /* Doubled ref number */
      return match(eptr,
        ecode + ((offset < offset_top && md->offset_vector[offset] >= 0)?
          6 : 3 + (ecode[1] << 8) + ecode[2]),
        offset_top, md, ims, eptrb, match_isgroup);
      }

    /* The condition is an assertion. Call match() to evaluate it - setting
    the final argument TRUE causes it to stop at the end of an assertion. */

    else
      {
      if (match(eptr, ecode+3, offset_top, md, ims, NULL,
          match_condassert | match_isgroup))
        {
        ecode += 3 + (ecode[4] << 8) + ecode[5];
        while (*ecode == OP_ALT) ecode += (ecode[1] << 8) + ecode[2];
        }
      else ecode += (ecode[1] << 8) + ecode[2];
      return match(eptr, ecode+3, offset_top, md, ims, eptrb, match_isgroup);
      }
    /* Control never reaches here */

    /* Skip over conditional reference or large extraction number data if
    encountered. */

    case OP_CREF:
    case OP_BRANUMBER:
    ecode += 3;
    break;

    /* End of the pattern. If PCRE_NOTEMPTY is set, fail if we have matched
    an empty string - recursion will then try other alternatives, if any. */

    case OP_END:
    if (md->notempty && eptr == md->start_match) return FALSE;
    md->end_match_ptr = eptr;          /* Record where we ended */
    md->end_offset_top = offset_top;   /* and how many extracts were taken */
    return TRUE;

    /* Change option settings */

    case OP_OPT:
    ims = ecode[1];
    ecode += 2;
    DPRINTF(("ims set to %02lx\n", ims));
    break;

    /* Assertion brackets. Check the alternative branches in turn - the
    matching won't pass the KET for an assertion. If any one branch matches,
    the assertion is true. Lookbehind assertions have an OP_REVERSE item at the
    start of each branch to move the current point backwards, so the code at
    this level is identical to the lookahead case. */

    case OP_ASSERT:
    case OP_ASSERTBACK:
    do
      {
      if (match(eptr, ecode+3, offset_top, md, ims, NULL, match_isgroup)) break;
      ecode += (ecode[1] << 8) + ecode[2];
      }
    while (*ecode == OP_ALT);
    if (*ecode == OP_KET) return FALSE;

    /* If checking an assertion for a condition, return TRUE. */

    if ((flags & match_condassert) != 0) return TRUE;

    /* Continue from after the assertion, updating the offsets high water
    mark, since extracts may have been taken during the assertion. */

    do ecode += (ecode[1] << 8) + ecode[2]; while (*ecode == OP_ALT);
    ecode += 3;
    offset_top = md->end_offset_top;
    continue;

    /* Negative assertion: all branches must fail to match */

    case OP_ASSERT_NOT:
    case OP_ASSERTBACK_NOT:
    do
      {
      if (match(eptr, ecode+3, offset_top, md, ims, NULL, match_isgroup))
        return FALSE;
      ecode += (ecode[1] << 8) + ecode[2];
      }
    while (*ecode == OP_ALT);

    if ((flags & match_condassert) != 0) return TRUE;

    ecode += 3;
    continue;

    /* Move the subject pointer back. This occurs only at the start of
    each branch of a lookbehind assertion. If we are too close to the start to
    move back, this match function fails. When working with UTF-8 we move
    back a number of characters, not bytes. */

    case OP_REVERSE:
#ifdef SUPPORT_UTF8
    c = (ecode[1] << 8) + ecode[2];
    for (i = 0; i < c; i++)
      {
      eptr--;
      BACKCHAR(eptr)
      }
#else
    eptr -= (ecode[1] << 8) + ecode[2];
#endif

    if (eptr < md->start_subject) return FALSE;
    ecode += 3;
    break;

    /* Recursion matches the current regex, nested. If there are any capturing
    brackets started but not finished, we have to save their starting points
    and reinstate them after the recursion. However, we don't know how many
    such there are (offset_top records the completed total) so we just have
    to save all the potential data. There may be up to 99 such values, which
    is a bit large to put on the stack, but using malloc for small numbers
    seems expensive. As a compromise, the stack is used when there are fewer
    than 16 values to store; otherwise malloc is used. A problem is what to do
    if the malloc fails ... there is no way of returning to the top level with
    an error. Save the top 15 values on the stack, and accept that the rest
    may be wrong. */

    case OP_RECURSE:
      {
      BOOL rc;
      int *save;
      int stacksave[15];

      c = md->offset_max;

      if (c < 16) save = stacksave; else
        {
        save = (int *)(pcre_malloc)((c+1) * sizeof(int));
        if (save == NULL)
          {
          save = stacksave;
          c = 15;
          }
        }

      for (i = 1; i <= c; i++)
        save[i] = md->offset_vector[md->offset_end - i];
      rc = match(eptr, md->start_pattern, offset_top, md, ims, eptrb,
        match_isgroup);
      for (i = 1; i <= c; i++)
        md->offset_vector[md->offset_end - i] = save[i];
      if (save != stacksave) (pcre_free)(save);
      if (!rc) return FALSE;

      /* In case the recursion has set more capturing values, save the final
      number, then move along the subject till after the recursive match,
      and advance one byte in the pattern code. */

      offset_top = md->end_offset_top;
      eptr = md->end_match_ptr;
      ecode++;
      }
    break;

    /* "Once" brackets are like assertion brackets except that after a match,
    the point in the subject string is not moved back. Thus there can never be
    a move back into the brackets. Check the alternative branches in turn - the
    matching won't pass the KET for this kind of subpattern. If any one branch
    matches, we carry on as at the end of a normal bracket, leaving the subject
    pointer. */

    case OP_ONCE:
      {
      const uschar *prev = ecode;
      const uschar *saved_eptr = eptr;

      do
        {
        if (match(eptr, ecode+3, offset_top, md, ims, eptrb, match_isgroup))
          break;
        ecode += (ecode[1] << 8) + ecode[2];
        }
      while (*ecode == OP_ALT);

      /* If hit the end of the group (which could be repeated), fail */

      if (*ecode != OP_ONCE && *ecode != OP_ALT) return FALSE;

      /* Continue as from after the assertion, updating the offsets high water
      mark, since extracts may have been taken. */

      do ecode += (ecode[1] << 8) + ecode[2]; while (*ecode == OP_ALT);

      offset_top = md->end_offset_top;
      eptr = md->end_match_ptr;

      /* For a non-repeating ket, just continue at this level. This also
      happens for a repeating ket if no characters were matched in the group.
      This is the forcible breaking of infinite loops as implemented in Perl
      5.005. If there is an options reset, it will get obeyed in the normal
      course of events. */

      if (*ecode == OP_KET || eptr == saved_eptr)
        {
        ecode += 3;
        break;
        }

      /* The repeating kets try the rest of the pattern or restart from the
      preceding bracket, in the appropriate order. We need to reset any options
      that changed within the bracket before re-running it, so check the next
      opcode. */

      if (ecode[3] == OP_OPT)
        {
        ims = (ims & ~PCRE_IMS) | ecode[4];
        DPRINTF(("ims set to %02lx at group repeat\n", ims));
        }

      if (*ecode == OP_KETRMIN)
        {
        if (match(eptr, ecode+3, offset_top, md, ims, eptrb, 0) ||
            match(eptr, prev, offset_top, md, ims, eptrb, match_isgroup))
              return TRUE;
        }
      else  /* OP_KETRMAX */
        {
        if (match(eptr, prev, offset_top, md, ims, eptrb, match_isgroup) ||
            match(eptr, ecode+3, offset_top, md, ims, eptrb, 0)) return TRUE;
        }
      }
    return FALSE;

    /* An alternation is the end of a branch; scan along to find the end of the
    bracketed group and go to there. */

    case OP_ALT:
    do ecode += (ecode[1] << 8) + ecode[2]; while (*ecode == OP_ALT);
    break;

    /* BRAZERO and BRAMINZERO occur just before a bracket group, indicating
    that it may occur zero times. It may repeat infinitely, or not at all -
    i.e. it could be ()* or ()? in the pattern. Brackets with fixed upper
    repeat limits are compiled as a number of copies, with the optional ones
    preceded by BRAZERO or BRAMINZERO. */

    case OP_BRAZERO:
      {
      const uschar *next = ecode+1;
      if (match(eptr, next, offset_top, md, ims, eptrb, match_isgroup))
        return TRUE;
      do next += (next[1] << 8) + next[2]; while (*next == OP_ALT);
      ecode = next + 3;
      }
    break;

    case OP_BRAMINZERO:
      {
      const uschar *next = ecode+1;
      do next += (next[1] << 8) + next[2]; while (*next == OP_ALT);
      if (match(eptr, next+3, offset_top, md, ims, eptrb, match_isgroup))
        return TRUE;
      ecode++;
      }
    break;

    /* End of a group, repeated or non-repeating. If we are at the end of
    an assertion "group", stop matching and return TRUE, but record the
    current high water mark for use by positive assertions. Do this also
    for the "once" (not-backup up) groups. */

    case OP_KET:
    case OP_KETRMIN:
    case OP_KETRMAX:
      {
      const uschar *prev = ecode - (ecode[1] << 8) - ecode[2];
      const uschar *saved_eptr = eptrb->saved_eptr;

      eptrb = eptrb->prev;    /* Back up the stack of bracket start pointers */

      if (*prev == OP_ASSERT || *prev == OP_ASSERT_NOT ||
          *prev == OP_ASSERTBACK || *prev == OP_ASSERTBACK_NOT ||
          *prev == OP_ONCE)
        {
        md->end_match_ptr = eptr;      /* For ONCE */
        md->end_offset_top = offset_top;
        return TRUE;
        }

      /* In all other cases except a conditional group we have to check the
      group number back at the start and if necessary complete handling an
      extraction by setting the offsets and bumping the high water mark. */

      if (*prev != OP_COND)
        {
        int offset;
        int number = *prev - OP_BRA;

        /* For extended extraction brackets (large number), we have to fish out
        the number from a dummy opcode at the start. */

        if (number > EXTRACT_BASIC_MAX) number = (prev[4] << 8) | prev[5];
        offset = number << 1;

#ifdef DEBUG
        printf("end bracket %d", number);
        printf("\n");
#endif

        if (number > 0)
          {
          if (offset >= md->offset_max) md->offset_overflow = TRUE; else
            {
            md->offset_vector[offset] =
              md->offset_vector[md->offset_end - number];
            md->offset_vector[offset+1] = eptr - md->start_subject;
            if (offset_top <= offset) offset_top = offset + 2;
            }
          }
        }

      /* Reset the value of the ims flags, in case they got changed during
      the group. */

      ims = original_ims;
      DPRINTF(("ims reset to %02lx\n", ims));

      /* For a non-repeating ket, just continue at this level. This also
      happens for a repeating ket if no characters were matched in the group.
      This is the forcible breaking of infinite loops as implemented in Perl
      5.005. If there is an options reset, it will get obeyed in the normal
      course of events. */

      if (*ecode == OP_KET || eptr == saved_eptr)
        {
        ecode += 3;
        break;
        }

      /* The repeating kets try the rest of the pattern or restart from the
      preceding bracket, in the appropriate order. */

      if (*ecode == OP_KETRMIN)
        {
        if (match(eptr, ecode+3, offset_top, md, ims, eptrb, 0) ||
            match(eptr, prev, offset_top, md, ims, eptrb, match_isgroup))
              return TRUE;
        }
      else  /* OP_KETRMAX */
        {
        if (match(eptr, prev, offset_top, md, ims, eptrb, match_isgroup) ||
            match(eptr, ecode+3, offset_top, md, ims, eptrb, 0)) return TRUE;
        }
      }
    return FALSE;

    /* Start of subject unless notbol, or after internal newline if multiline */

    case OP_CIRC:
    if (md->notbol && eptr == md->start_subject) return FALSE;
    if ((ims & PCRE_MULTILINE) != 0)
      {
      if (eptr != md->start_subject && eptr[-1] != NEWLINE) return FALSE;
      ecode++;
      break;
      }
    /* ... else fall through */

    /* Start of subject assertion */

    case OP_SOD:
    if (eptr != md->start_subject) return FALSE;
    ecode++;
    break;

    /* Assert before internal newline if multiline, or before a terminating
    newline unless endonly is set, else end of subject unless noteol is set. */

    case OP_DOLL:
    if ((ims & PCRE_MULTILINE) != 0)
      {
      if (eptr < md->end_subject) { if (*eptr != NEWLINE) return FALSE; }
        else { if (md->noteol) return FALSE; }
      ecode++;
      break;
      }
    else
      {
      if (md->noteol) return FALSE;
      if (!md->endonly)
        {
        if (eptr < md->end_subject - 1 ||
           (eptr == md->end_subject - 1 && *eptr != NEWLINE)) return FALSE;

        ecode++;
        break;
        }
      }
    /* ... else fall through */

    /* End of subject assertion (\z) */

    case OP_EOD:
    if (eptr < md->end_subject) return FALSE;
    ecode++;
    break;

    /* End of subject or ending \n assertion (\Z) */

    case OP_EODN:
    if (eptr < md->end_subject - 1 ||
       (eptr == md->end_subject - 1 && *eptr != NEWLINE)) return FALSE;
    ecode++;
    break;

    /* Word boundary assertions */

    case OP_NOT_WORD_BOUNDARY:
    case OP_WORD_BOUNDARY:
      {
      BOOL prev_is_word = (eptr != md->start_subject) &&
        ((md->ctypes[eptr[-1]] & ctype_word) != 0);
      BOOL cur_is_word = (eptr < md->end_subject) &&
        ((md->ctypes[*eptr] & ctype_word) != 0);
      if ((*ecode++ == OP_WORD_BOUNDARY)?
           cur_is_word == prev_is_word : cur_is_word != prev_is_word)
        return FALSE;
      }
    break;

    /* Match a single character type; inline for speed */

    case OP_ANY:
    if ((ims & PCRE_DOTALL) == 0 && eptr < md->end_subject && *eptr == NEWLINE)
      return FALSE;
    if (eptr++ >= md->end_subject) return FALSE;
#ifdef SUPPORT_UTF8
    if (md->utf8)
      while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
#endif
    ecode++;
    break;

    case OP_NOT_DIGIT:
    if (eptr >= md->end_subject ||
       (md->ctypes[*eptr++] & ctype_digit) != 0)
      return FALSE;
    ecode++;
    break;

    case OP_DIGIT:
    if (eptr >= md->end_subject ||
       (md->ctypes[*eptr++] & ctype_digit) == 0)
      return FALSE;
    ecode++;
    break;

    case OP_NOT_WHITESPACE:
    if (eptr >= md->end_subject ||
       (md->ctypes[*eptr++] & ctype_space) != 0)
      return FALSE;
    ecode++;
    break;

    case OP_WHITESPACE:
    if (eptr >= md->end_subject ||
       (md->ctypes[*eptr++] & ctype_space) == 0)
      return FALSE;
    ecode++;
    break;

    case OP_NOT_WORDCHAR:
    if (eptr >= md->end_subject ||
       (md->ctypes[*eptr++] & ctype_word) != 0)
      return FALSE;
    ecode++;
    break;

    case OP_WORDCHAR:
    if (eptr >= md->end_subject ||
       (md->ctypes[*eptr++] & ctype_word) == 0)
      return FALSE;
    ecode++;
    break;

    /* Match a back reference, possibly repeatedly. Look past the end of the
    item to see if there is repeat information following. The code is similar
    to that for character classes, but repeated for efficiency. Then obey
    similar code to character type repeats - written out again for speed.
    However, if the referenced string is the empty string, always treat
    it as matched, any number of times (otherwise there could be infinite
    loops). */

    case OP_REF:
      {
      int length;
      int offset = (ecode[1] << 9) | (ecode[2] << 1); /* Doubled ref number */
      ecode += 3;                                     /* Advance past item */

      /* If the reference is unset, set the length to be longer than the amount
      of subject left; this ensures that every attempt at a match fails. We
      can't just fail here, because of the possibility of quantifiers with zero
      minima. */

      length = (offset >= offset_top || md->offset_vector[offset] < 0)?
        md->end_subject - eptr + 1 :
        md->offset_vector[offset+1] - md->offset_vector[offset];

      /* Set up for repetition, or handle the non-repeated case */

      switch (*ecode)
        {
        case OP_CRSTAR:
        case OP_CRMINSTAR:
        case OP_CRPLUS:
        case OP_CRMINPLUS:
        case OP_CRQUERY:
        case OP_CRMINQUERY:
        c = *ecode++ - OP_CRSTAR;
        minimize = (c & 1) != 0;
        min = rep_min[c];                 /* Pick up values from tables; */
        max = rep_max[c];                 /* zero for max => infinity */
        if (max == 0) max = INT_MAX;
        break;

        case OP_CRRANGE:
        case OP_CRMINRANGE:
        minimize = (*ecode == OP_CRMINRANGE);
        min = (ecode[1] << 8) + ecode[2];
        max = (ecode[3] << 8) + ecode[4];
        if (max == 0) max = INT_MAX;
        ecode += 5;
        break;

        default:               /* No repeat follows */
        if (!match_ref(offset, eptr, length, md, ims)) return FALSE;
        eptr += length;
        continue;              /* With the main loop */
        }

      /* If the length of the reference is zero, just continue with the
      main loop. */

      if (length == 0) continue;

      /* First, ensure the minimum number of matches are present. We get back
      the length of the reference string explicitly rather than passing the
      address of eptr, so that eptr can be a register variable. */

      for (i = 1; i <= min; i++)
        {
        if (!match_ref(offset, eptr, length, md, ims)) return FALSE;
        eptr += length;
        }

      /* If min = max, continue at the same level without recursion.
      They are not both allowed to be zero. */

      if (min == max) continue;

      /* If minimizing, keep trying and advancing the pointer */

      if (minimize)
        {
        for (i = min;; i++)
          {
          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
          if (i >= max || !match_ref(offset, eptr, length, md, ims))
            return FALSE;
          eptr += length;
          }
        /* Control never gets here */
        }

      /* If maximizing, find the longest string and work backwards */

      else
        {
        const uschar *pp = eptr;
        for (i = min; i < max; i++)
          {
          if (!match_ref(offset, eptr, length, md, ims)) break;
          eptr += length;
          }
        while (eptr >= pp)
          {
          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
          eptr -= length;
          }
        return FALSE;
        }
      }
    /* Control never gets here */



    /* Match a character class, possibly repeatedly. Look past the end of the
    item to see if there is repeat information following. Then obey similar
    code to character type repeats - written out again for speed. */

    case OP_CLASS:
      {
      const uschar *data = ecode + 1;  /* Save for matching */
      ecode += 33;                     /* Advance past the item */

      switch (*ecode)
        {
        case OP_CRSTAR:
        case OP_CRMINSTAR:
        case OP_CRPLUS:
        case OP_CRMINPLUS:
        case OP_CRQUERY:
        case OP_CRMINQUERY:
        c = *ecode++ - OP_CRSTAR;
        minimize = (c & 1) != 0;
        min = rep_min[c];                 /* Pick up values from tables; */
        max = rep_max[c];                 /* zero for max => infinity */
        if (max == 0) max = INT_MAX;
        break;

        case OP_CRRANGE:
        case OP_CRMINRANGE:
        minimize = (*ecode == OP_CRMINRANGE);
        min = (ecode[1] << 8) + ecode[2];
        max = (ecode[3] << 8) + ecode[4];
        if (max == 0) max = INT_MAX;
        ecode += 5;
        break;

        default:               /* No repeat follows */
        min = max = 1;
        break;
        }

      /* First, ensure the minimum number of matches are present. */

      for (i = 1; i <= min; i++)
        {
        if (eptr >= md->end_subject) return FALSE;
        GETCHARINC(c, eptr)         /* Get character; increment eptr */

#ifdef SUPPORT_UTF8
        /* We do not yet support class members > 255 */
        if (c > 255) return FALSE;
#endif

        if ((data[c/8] & (1 << (c&7))) != 0) continue;
        return FALSE;
        }

      /* If max == min we can continue with the main loop without the
      need to recurse. */

      if (min == max) continue;

      /* If minimizing, keep testing the rest of the expression and advancing
      the pointer while it matches the class. */

      if (minimize)
        {
        for (i = min;; i++)
          {
          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
          if (i >= max || eptr >= md->end_subject) return FALSE;
          GETCHARINC(c, eptr)       /* Get character; increment eptr */

#ifdef SUPPORT_UTF8
          /* We do not yet support class members > 255 */
          if (c > 255) return FALSE;
#endif
          if ((data[c/8] & (1 << (c&7))) != 0) continue;
          return FALSE;
          }
        /* Control never gets here */
        }

      /* If maximizing, find the longest possible run, then work backwards. */

      else
        {
        const uschar *pp = eptr;
        int len = 1;
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject) break;
          GETCHARLEN(c, eptr, len)  /* Get character, set length if UTF-8 */

#ifdef SUPPORT_UTF8
          /* We do not yet support class members > 255 */
          if (c > 255) break;
#endif
          if ((data[c/8] & (1 << (c&7))) == 0) break;
          eptr += len;
          }

        while (eptr >= pp)
          {
          if (match(eptr--, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;

#ifdef SUPPORT_UTF8
          BACKCHAR(eptr)
#endif
          }
        return FALSE;
        }
      }
    /* Control never gets here */

    /* Match a run of characters */

    case OP_CHARS:
      {
      register int length = ecode[1];
      ecode += 2;

#ifdef DEBUG    /* Sigh. Some compilers never learn. */
      if (eptr >= md->end_subject)
        printf("matching subject <null> against pattern ");
      else
        {
        printf("matching subject ");
        pchars(eptr, length, TRUE, md);
        printf(" against pattern ");
        }
      pchars(ecode, length, FALSE, md);
      printf("\n");
#endif

      if (length > md->end_subject - eptr) return FALSE;
      if ((ims & PCRE_CASELESS) != 0)
        {
        while (length-- > 0)
          if (md->lcc[*ecode++] != md->lcc[*eptr++])
            return FALSE;
        }
      else
        {
        while (length-- > 0) if (*ecode++ != *eptr++) return FALSE;
        }
      }
    break;

    /* Match a single character repeatedly; different opcodes share code. */

    case OP_EXACT:
    min = max = (ecode[1] << 8) + ecode[2];
    ecode += 3;
    goto REPEATCHAR;

    case OP_UPTO:
    case OP_MINUPTO:
    min = 0;
    max = (ecode[1] << 8) + ecode[2];
    minimize = *ecode == OP_MINUPTO;
    ecode += 3;
    goto REPEATCHAR;

    case OP_STAR:
    case OP_MINSTAR:
    case OP_PLUS:
    case OP_MINPLUS:
    case OP_QUERY:
    case OP_MINQUERY:
    c = *ecode++ - OP_STAR;
    minimize = (c & 1) != 0;
    min = rep_min[c];                 /* Pick up values from tables; */
    max = rep_max[c];                 /* zero for max => infinity */
    if (max == 0) max = INT_MAX;

    /* Common code for all repeated single-character matches. We can give
    up quickly if there are fewer than the minimum number of characters left in
    the subject. */

    REPEATCHAR:
    if (min > md->end_subject - eptr) return FALSE;
    c = *ecode++;

    /* The code is duplicated for the caseless and caseful cases, for speed,
    since matching characters is likely to be quite common. First, ensure the
    minimum number of matches are present. If min = max, continue at the same
    level without recursing. Otherwise, if minimizing, keep trying the rest of
    the expression and advancing one matching character if failing, up to the
    maximum. Alternatively, if maximizing, find the maximum number of
    characters and work backwards. */

    DPRINTF(("matching %c{%d,%d} against subject %.*s\n", c, min, max,
      max, eptr));

    if ((ims & PCRE_CASELESS) != 0)
      {
      c = md->lcc[c];
      for (i = 1; i <= min; i++)
        if (c != md->lcc[*eptr++]) return FALSE;
      if (min == max) continue;
      if (minimize)
        {
        for (i = min;; i++)
          {
          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
          if (i >= max || eptr >= md->end_subject ||
              c != md->lcc[*eptr++])
            return FALSE;
          }
        /* Control never gets here */
        }
      else
        {
        const uschar *pp = eptr;
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || c != md->lcc[*eptr]) break;
          eptr++;
          }
        while (eptr >= pp)
          if (match(eptr--, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
        return FALSE;
        }
      /* Control never gets here */
      }

    /* Caseful comparisons */

    else
      {
      for (i = 1; i <= min; i++) if (c != *eptr++) return FALSE;
      if (min == max) continue;
      if (minimize)
        {
        for (i = min;; i++)
          {
          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
          if (i >= max || eptr >= md->end_subject || c != *eptr++) return FALSE;
          }
        /* Control never gets here */
        }
      else
        {
        const uschar *pp = eptr;
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || c != *eptr) break;
          eptr++;
          }
        while (eptr >= pp)
         if (match(eptr--, ecode, offset_top, md, ims, eptrb, 0))
           return TRUE;
        return FALSE;
        }
      }
    /* Control never gets here */

    /* Match a negated single character */

    case OP_NOT:
    if (eptr >= md->end_subject) return FALSE;
    ecode++;
    if ((ims & PCRE_CASELESS) != 0)
      {
      if (md->lcc[*ecode++] == md->lcc[*eptr++]) return FALSE;
      }
    else
      {
      if (*ecode++ == *eptr++) return FALSE;
      }
    break;

    /* Match a negated single character repeatedly. This is almost a repeat of
    the code for a repeated single character, but I haven't found a nice way of
    commoning these up that doesn't require a test of the positive/negative
    option for each character match. Maybe that wouldn't add very much to the
    time taken, but character matching *is* what this is all about... */

    case OP_NOTEXACT:
    min = max = (ecode[1] << 8) + ecode[2];
    ecode += 3;
    goto REPEATNOTCHAR;

    case OP_NOTUPTO:
    case OP_NOTMINUPTO:
    min = 0;
    max = (ecode[1] << 8) + ecode[2];
    minimize = *ecode == OP_NOTMINUPTO;
    ecode += 3;
    goto REPEATNOTCHAR;

    case OP_NOTSTAR:
    case OP_NOTMINSTAR:
    case OP_NOTPLUS:
    case OP_NOTMINPLUS:
    case OP_NOTQUERY:
    case OP_NOTMINQUERY:
    c = *ecode++ - OP_NOTSTAR;
    minimize = (c & 1) != 0;
    min = rep_min[c];                 /* Pick up values from tables; */
    max = rep_max[c];                 /* zero for max => infinity */
    if (max == 0) max = INT_MAX;

    /* Common code for all repeated single-character matches. We can give
    up quickly if there are fewer than the minimum number of characters left in
    the subject. */

    REPEATNOTCHAR:
    if (min > md->end_subject - eptr) return FALSE;
    c = *ecode++;

    /* The code is duplicated for the caseless and caseful cases, for speed,
    since matching characters is likely to be quite common. First, ensure the
    minimum number of matches are present. If min = max, continue at the same
    level without recursing. Otherwise, if minimizing, keep trying the rest of
    the expression and advancing one matching character if failing, up to the
    maximum. Alternatively, if maximizing, find the maximum number of
    characters and work backwards. */

    DPRINTF(("negative matching %c{%d,%d} against subject %.*s\n", c, min, max,
      max, eptr));

    if ((ims & PCRE_CASELESS) != 0)
      {
      c = md->lcc[c];
      for (i = 1; i <= min; i++)
        if (c == md->lcc[*eptr++]) return FALSE;
      if (min == max) continue;
      if (minimize)
        {
        for (i = min;; i++)
          {
          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
          if (i >= max || eptr >= md->end_subject ||
              c == md->lcc[*eptr++])
            return FALSE;
          }
        /* Control never gets here */
        }
      else
        {
        const uschar *pp = eptr;
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || c == md->lcc[*eptr]) break;
          eptr++;
          }
        while (eptr >= pp)
          if (match(eptr--, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
        return FALSE;
        }
      /* Control never gets here */
      }

    /* Caseful comparisons */

    else
      {
      for (i = 1; i <= min; i++) if (c == *eptr++) return FALSE;
      if (min == max) continue;
      if (minimize)
        {
        for (i = min;; i++)
          {
          if (match(eptr, ecode, offset_top, md, ims, eptrb, 0))
            return TRUE;
          if (i >= max || eptr >= md->end_subject || c == *eptr++) return FALSE;
          }
        /* Control never gets here */
        }
      else
        {
        const uschar *pp = eptr;
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || c == *eptr) break;
          eptr++;
          }
        while (eptr >= pp)
         if (match(eptr--, ecode, offset_top, md, ims, eptrb, 0))
           return TRUE;
        return FALSE;
        }
      }
    /* Control never gets here */

    /* Match a single character type repeatedly; several different opcodes
    share code. This is very similar to the code for single characters, but we
    repeat it in the interests of efficiency. */

    case OP_TYPEEXACT:
    min = max = (ecode[1] << 8) + ecode[2];
    minimize = TRUE;
    ecode += 3;
    goto REPEATTYPE;

    case OP_TYPEUPTO:
    case OP_TYPEMINUPTO:
    min = 0;
    max = (ecode[1] << 8) + ecode[2];
    minimize = *ecode == OP_TYPEMINUPTO;
    ecode += 3;
    goto REPEATTYPE;

    case OP_TYPESTAR:
    case OP_TYPEMINSTAR:
    case OP_TYPEPLUS:
    case OP_TYPEMINPLUS:
    case OP_TYPEQUERY:
    case OP_TYPEMINQUERY:
    c = *ecode++ - OP_TYPESTAR;
    minimize = (c & 1) != 0;
    min = rep_min[c];                 /* Pick up values from tables; */
    max = rep_max[c];                 /* zero for max => infinity */
    if (max == 0) max = INT_MAX;

    /* Common code for all repeated single character type matches */

    REPEATTYPE:
    ctype = *ecode++;      /* Code for the character type */

    /* First, ensure the minimum number of matches are present. Use inline
    code for maximizing the speed, and do the type test once at the start
    (i.e. keep it out of the loop). Also we can test that there are at least
    the minimum number of bytes before we start, except when doing '.' in
    UTF8 mode. Leave the test in in all cases; in the special case we have
    to test after each character. */

    if (min > md->end_subject - eptr) return FALSE;
    if (min > 0) switch(ctype)
      {
      case OP_ANY:
#ifdef SUPPORT_UTF8
      if (md->utf8)
        {
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject ||
             (*eptr++ == NEWLINE && (ims & PCRE_DOTALL) == 0))
            return FALSE;
          while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
          }
        break;
        }
#endif
      /* Non-UTF8 can be faster */
      if ((ims & PCRE_DOTALL) == 0)
        { for (i = 1; i <= min; i++) if (*eptr++ == NEWLINE) return FALSE; }
      else eptr += min;
      break;

      case OP_NOT_DIGIT:
      for (i = 1; i <= min; i++)
        if ((md->ctypes[*eptr++] & ctype_digit) != 0) return FALSE;
      break;

      case OP_DIGIT:
      for (i = 1; i <= min; i++)
        if ((md->ctypes[*eptr++] & ctype_digit) == 0) return FALSE;
      break;

      case OP_NOT_WHITESPACE:
      for (i = 1; i <= min; i++)
        if ((md->ctypes[*eptr++] & ctype_space) != 0) return FALSE;
      break;

      case OP_WHITESPACE:
      for (i = 1; i <= min; i++)
        if ((md->ctypes[*eptr++] & ctype_space) == 0) return FALSE;
      break;

      case OP_NOT_WORDCHAR:
      for (i = 1; i <= min; i++)
        if ((md->ctypes[*eptr++] & ctype_word) != 0)
          return FALSE;
      break;

      case OP_WORDCHAR:
      for (i = 1; i <= min; i++)
        if ((md->ctypes[*eptr++] & ctype_word) == 0)
          return FALSE;
      break;
      }

    /* If min = max, continue at the same level without recursing */

    if (min == max) continue;

    /* If minimizing, we have to test the rest of the pattern before each
    subsequent match. */

    if (minimize)
      {
      for (i = min;; i++)
        {
        if (match(eptr, ecode, offset_top, md, ims, eptrb, 0)) return TRUE;
        if (i >= max || eptr >= md->end_subject) return FALSE;

        c = *eptr++;
        switch(ctype)
          {
          case OP_ANY:
          if ((ims & PCRE_DOTALL) == 0 && c == NEWLINE) return FALSE;
#ifdef SUPPORT_UTF8
          if (md->utf8)
            while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
#endif
          break;

          case OP_NOT_DIGIT:
          if ((md->ctypes[c] & ctype_digit) != 0) return FALSE;
          break;

          case OP_DIGIT:
          if ((md->ctypes[c] & ctype_digit) == 0) return FALSE;
          break;

          case OP_NOT_WHITESPACE:
          if ((md->ctypes[c] & ctype_space) != 0) return FALSE;
          break;

          case OP_WHITESPACE:
          if  ((md->ctypes[c] & ctype_space) == 0) return FALSE;
          break;

          case OP_NOT_WORDCHAR:
          if ((md->ctypes[c] & ctype_word) != 0) return FALSE;
          break;

          case OP_WORDCHAR:
          if ((md->ctypes[c] & ctype_word) == 0) return FALSE;
          break;
          }
        }
      /* Control never gets here */
      }

    /* If maximizing it is worth using inline code for speed, doing the type
    test once at the start (i.e. keep it out of the loop). */

    else
      {
      const uschar *pp = eptr;
      switch(ctype)
        {
        case OP_ANY:

        /* Special code is required for UTF8, but when the maximum is unlimited
        we don't need it. */

#ifdef SUPPORT_UTF8
        if (md->utf8 && max < INT_MAX)
          {
          if ((ims & PCRE_DOTALL) == 0)
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject || *eptr++ == NEWLINE) break;
              while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
              }
            }
          else
            {
            for (i = min; i < max; i++)
              {
              eptr++;
              while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
              }
            }
          break;
          }
#endif
        /* Non-UTF8 can be faster */
        if ((ims & PCRE_DOTALL) == 0)
          {
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || *eptr == NEWLINE) break;
            eptr++;
            }
          }
        else
          {
          c = max - min;
          if (c > md->end_subject - eptr) c = md->end_subject - eptr;
          eptr += c;
          }
        break;

        case OP_NOT_DIGIT:
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_digit) != 0)
            break;
          eptr++;
          }
        break;

        case OP_DIGIT:
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_digit) == 0)
            break;
          eptr++;
          }
        break;

        case OP_NOT_WHITESPACE:
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_space) != 0)
            break;
          eptr++;
          }
        break;

        case OP_WHITESPACE:
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_space) == 0)
            break;
          eptr++;
          }
        break;

        case OP_NOT_WORDCHAR:
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_word) != 0)
            break;
          eptr++;
          }
        break;

        case OP_WORDCHAR:
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_word) == 0)
            break;
          eptr++;
          }
        break;
        }

      while (eptr >= pp)
        {
        if (match(eptr--, ecode, offset_top, md, ims, eptrb, 0))
          return TRUE;
#ifdef SUPPORT_UTF8
        if (md->utf8)
          while (eptr > pp && (*eptr & 0xc0) == 0x80) eptr--;
#endif
        }
      return FALSE;
      }
    /* Control never gets here */

    /* There's been some horrible disaster. */

    default:
    DPRINTF(("Unknown opcode %d\n", *ecode));
    md->errorcode = PCRE_ERROR_UNKNOWN_NODE;
    return FALSE;
    }

  /* Do not stick any code in here without much thought; it is assumed
  that "continue" in the code above comes out to here to repeat the main
  loop. */

  }             /* End of main loop */
/* Control never reaches here */
}