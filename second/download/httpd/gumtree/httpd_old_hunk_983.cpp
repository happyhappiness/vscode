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

