static BOOL
compile_branch(int options, int *brackets, uschar **codeptr,
  const uschar **ptrptr, const char **errorptr, int *optchanged,
  int *reqchar, int *countlits, compile_data *cd)
{
int repeat_type, op_type;
int repeat_min, repeat_max;
int bravalue, length;
int greedy_default, greedy_non_default;
int prevreqchar;
int condcount = 0;
int subcountlits = 0;
register int c;
register uschar *code = *codeptr;
uschar *tempcode;
const uschar *ptr = *ptrptr;
const uschar *tempptr;
uschar *previous = NULL;
uschar class[32];

/* Set up the default and non-default settings for greediness */

greedy_default = ((options & PCRE_UNGREEDY) != 0);
greedy_non_default = greedy_default ^ 1;

/* Initialize no required char, and count of literals */

*reqchar = prevreqchar = -1;
*countlits = 0;

/* Switch on next character until the end of the branch */

for (;; ptr++)
  {
  BOOL negate_class;
  int class_charcount;
  int class_lastchar;
  int newoptions;
  int skipbytes;
  int subreqchar;

  c = *ptr;
  if ((options & PCRE_EXTENDED) != 0)
    {
    if ((cd->ctypes[c] & ctype_space) != 0) continue;
    if (c == '#')
      {
      /* The space before the ; is to avoid a warning on a silly compiler
      on the Macintosh. */
      while ((c = *(++ptr)) != 0 && c != NEWLINE) ;
      continue;
      }
    }

  switch(c)
    {
    /* The branch terminates at end of string, |, or ). */

    case 0:
    case '|':
    case ')':
    *codeptr = code;
    *ptrptr = ptr;
    return TRUE;

    /* Handle single-character metacharacters */

    case '^':
    previous = NULL;
    *code++ = OP_CIRC;
    break;

    case '$':
    previous = NULL;
    *code++ = OP_DOLL;
    break;

    case '.':
    previous = code;
    *code++ = OP_ANY;
    break;

    /* Character classes. These always build a 32-byte bitmap of the permitted
    characters, except in the special case where there is only one character.
    For negated classes, we build the map as usual, then invert it at the end.
    */

    case '[':
    previous = code;
    *code++ = OP_CLASS;

    /* If the first character is '^', set the negation flag and skip it. */

    if ((c = *(++ptr)) == '^')
      {
      negate_class = TRUE;
      c = *(++ptr);
      }
    else negate_class = FALSE;

    /* Keep a count of chars so that we can optimize the case of just a single
    character. */

    class_charcount = 0;
    class_lastchar = -1;

    /* Initialize the 32-char bit map to all zeros. We have to build the
    map in a temporary bit of store, in case the class contains only 1
    character, because in that case the compiled code doesn't use the
    bit map. */

    memset(class, 0, 32 * sizeof(uschar));

    /* Process characters until ] is reached. By writing this as a "do" it
    means that an initial ] is taken as a data character. */

    do
      {
      if (c == 0)
        {
        *errorptr = ERR6;
        goto FAILED;
        }

      /* Handle POSIX class names. Perl allows a negation extension of the
      form [:^name]. A square bracket that doesn't match the syntax is
      treated as a literal. We also recognize the POSIX constructions
      [.ch.] and [=ch=] ("collating elements") and fault them, as Perl
      5.6 does. */

      if (c == '[' &&
          (ptr[1] == ':' || ptr[1] == '.' || ptr[1] == '=') &&
          check_posix_syntax(ptr, &tempptr, cd))
        {
        BOOL local_negate = FALSE;
        int posix_class, i;
        register const uschar *cbits = cd->cbits;

        if (ptr[1] != ':')
          {
          *errorptr = ERR31;
          goto FAILED;
          }

        ptr += 2;
        if (*ptr == '^')
          {
          local_negate = TRUE;
          ptr++;
          }

        posix_class = check_posix_name(ptr, tempptr - ptr);
        if (posix_class < 0)
          {
          *errorptr = ERR30;
          goto FAILED;
          }

        /* If matching is caseless, upper and lower are converted to
        alpha. This relies on the fact that the class table starts with
        alpha, lower, upper as the first 3 entries. */

        if ((options & PCRE_CASELESS) != 0 && posix_class <= 2)
          posix_class = 0;

        /* Or into the map we are building up to 3 of the static class
        tables, or their negations. */

        posix_class *= 3;
        for (i = 0; i < 3; i++)
          {
          int taboffset = posix_class_maps[posix_class + i];
          if (taboffset < 0) break;
          if (local_negate)
            for (c = 0; c < 32; c++) class[c] |= ~cbits[c+taboffset];
          else
            for (c = 0; c < 32; c++) class[c] |= cbits[c+taboffset];
          }

        ptr = tempptr + 1;
        class_charcount = 10;  /* Set > 1; assumes more than 1 per class */
        continue;
        }

      /* Backslash may introduce a single character, or it may introduce one
      of the specials, which just set a flag. Escaped items are checked for
      validity in the pre-compiling pass. The sequence \b is a special case.
      Inside a class (and only there) it is treated as backspace. Elsewhere
      it marks a word boundary. Other escapes have preset maps ready to
      or into the one we are building. We assume they have more than one
      character in them, so set class_count bigger than one. */

      if (c == '\\')
        {
        c = check_escape(&ptr, errorptr, *brackets, options, TRUE, cd);
        if (-c == ESC_b) c = '\b';
        else if (c < 0)
          {
          register const uschar *cbits = cd->cbits;
          class_charcount = 10;
          switch (-c)
            {
            case ESC_d:
            for (c = 0; c < 32; c++) class[c] |= cbits[c+cbit_digit];
            continue;

            case ESC_D:
            for (c = 0; c < 32; c++) class[c] |= ~cbits[c+cbit_digit];
            continue;

            case ESC_w:
            for (c = 0; c < 32; c++) class[c] |= cbits[c+cbit_word];
            continue;

            case ESC_W:
            for (c = 0; c < 32; c++) class[c] |= ~cbits[c+cbit_word];
            continue;

            case ESC_s:
            for (c = 0; c < 32; c++) class[c] |= cbits[c+cbit_space];
            continue;

            case ESC_S:
            for (c = 0; c < 32; c++) class[c] |= ~cbits[c+cbit_space];
            continue;

            default:
            *errorptr = ERR7;
            goto FAILED;
            }
          }

        /* Fall through if single character, but don't at present allow
        chars > 255 in UTF-8 mode. */

#ifdef SUPPORT_UTF8
        if (c > 255)
          {
          *errorptr = ERR33;
          goto FAILED;
          }
#endif
        }

      /* A single character may be followed by '-' to form a range. However,
      Perl does not permit ']' to be the end of the range. A '-' character
      here is treated as a literal. */

      if (ptr[1] == '-' && ptr[2] != ']')
        {
        int d;
        ptr += 2;
        d = *ptr;

        if (d == 0)
          {
          *errorptr = ERR6;
          goto FAILED;
          }

        /* The second part of a range can be a single-character escape, but
        not any of the other escapes. Perl 5.6 treats a hyphen as a literal
        in such circumstances. */

        if (d == '\\')
          {
          const uschar *oldptr = ptr;
          d = check_escape(&ptr, errorptr, *brackets, options, TRUE, cd);

#ifdef SUPPORT_UTF8
          if (d > 255)
            {
            *errorptr = ERR33;
            goto FAILED;
            }
#endif
          /* \b is backslash; any other special means the '-' was literal */

          if (d < 0)
            {
            if (d == -ESC_b) d = '\b'; else
              {
              ptr = oldptr - 2;
              goto SINGLE_CHARACTER;  /* A few lines below */
              }
            }
          }

        if (d < c)
          {
          *errorptr = ERR8;
          goto FAILED;
          }

        for (; c <= d; c++)
          {
          class[c/8] |= (1 << (c&7));
          if ((options & PCRE_CASELESS) != 0)
            {
            int uc = cd->fcc[c];           /* flip case */
            class[uc/8] |= (1 << (uc&7));
            }
          class_charcount++;                /* in case a one-char range */
          class_lastchar = c;
          }
        continue;   /* Go get the next char in the class */
        }

      /* Handle a lone single character - we can get here for a normal
      non-escape char, or after \ that introduces a single character. */

      SINGLE_CHARACTER:

      class [c/8] |= (1 << (c&7));
      if ((options & PCRE_CASELESS) != 0)
        {
        c = cd->fcc[c];   /* flip case */
        class[c/8] |= (1 << (c&7));
        }
      class_charcount++;
      class_lastchar = c;
      }

    /* Loop until ']' reached; the check for end of string happens inside the
    loop. This "while" is the end of the "do" above. */

    while ((c = *(++ptr)) != ']');

    /* If class_charcount is 1 and class_lastchar is not negative, we saw
    precisely one character. This doesn't need the whole 32-byte bit map.
    We turn it into a 1-character OP_CHAR if it's positive, or OP_NOT if
    it's negative. */

    if (class_charcount == 1 && class_lastchar >= 0)
      {
      if (negate_class)
        {
        code[-1] = OP_NOT;
        }
      else
        {
        code[-1] = OP_CHARS;
        *code++ = 1;
        }
      *code++ = class_lastchar;
      }

    /* Otherwise, negate the 32-byte map if necessary, and copy it into
    the code vector. */

    else
      {
      if (negate_class)
        for (c = 0; c < 32; c++) code[c] = ~class[c];
      else
        memcpy(code, class, 32);
      code += 32;
      }
    break;

    /* Various kinds of repeat */

    case '{':
    if (!is_counted_repeat(ptr+1, cd)) goto NORMAL_CHAR;
    ptr = read_repeat_counts(ptr+1, &repeat_min, &repeat_max, errorptr, cd);
    if (*errorptr != NULL) goto FAILED;
    goto REPEAT;

    case '*':
    repeat_min = 0;
    repeat_max = -1;
    goto REPEAT;

    case '+':
    repeat_min = 1;
    repeat_max = -1;
    goto REPEAT;

    case '?':
    repeat_min = 0;
    repeat_max = 1;

    REPEAT:
    if (previous == NULL)
      {
      *errorptr = ERR9;
      goto FAILED;
      }

    /* If the next character is '?' this is a minimizing repeat, by default,
    but if PCRE_UNGREEDY is set, it works the other way round. Advance to the
    next character. */

    if (ptr[1] == '?')
      { repeat_type = greedy_non_default; ptr++; }
    else repeat_type = greedy_default;

    /* If previous was a string of characters, chop off the last one and use it
    as the subject of the repeat. If there was only one character, we can
    abolish the previous item altogether. A repeat with a zero minimum wipes
    out any reqchar setting, backing up to the previous value. We must also
    adjust the countlits value. */

    if (*previous == OP_CHARS)
      {
      int len = previous[1];

      if (repeat_min == 0) *reqchar = prevreqchar;
      *countlits += repeat_min - 1;

      if (len == 1)
        {
        c = previous[2];
        code = previous;
        }
      else
        {
        c = previous[len+1];
        previous[1]--;
        code--;
        }
      op_type = 0;                 /* Use single-char op codes */
      goto OUTPUT_SINGLE_REPEAT;   /* Code shared with single character types */
      }

    /* If previous was a single negated character ([^a] or similar), we use
    one of the special opcodes, replacing it. The code is shared with single-
    character repeats by adding a suitable offset into repeat_type. */

    else if ((int)*previous == OP_NOT)
      {
      op_type = OP_NOTSTAR - OP_STAR;  /* Use "not" opcodes */
      c = previous[1];
      code = previous;
      goto OUTPUT_SINGLE_REPEAT;
      }

    /* If previous was a character type match (\d or similar), abolish it and
    create a suitable repeat item. The code is shared with single-character
    repeats by adding a suitable offset into repeat_type. */

    else if ((int)*previous < OP_EODN || *previous == OP_ANY)
      {
      op_type = OP_TYPESTAR - OP_STAR;  /* Use type opcodes */
      c = *previous;
      code = previous;

      OUTPUT_SINGLE_REPEAT:

      /* If the maximum is zero then the minimum must also be zero; Perl allows
      this case, so we do too - by simply omitting the item altogether. */

      if (repeat_max == 0) goto END_REPEAT;

      /* Combine the op_type with the repeat_type */

      repeat_type += op_type;

      /* A minimum of zero is handled either as the special case * or ?, or as
      an UPTO, with the maximum given. */

      if (repeat_min == 0)
        {
        if (repeat_max == -1) *code++ = OP_STAR + repeat_type;
          else if (repeat_max == 1) *code++ = OP_QUERY + repeat_type;
        else
          {
          *code++ = OP_UPTO + repeat_type;
          *code++ = repeat_max >> 8;
          *code++ = (repeat_max & 255);
          }
        }

      /* The case {1,} is handled as the special case + */

      else if (repeat_min == 1 && repeat_max == -1)
        *code++ = OP_PLUS + repeat_type;

      /* The case {n,n} is just an EXACT, while the general case {n,m} is
      handled as an EXACT followed by an UPTO. An EXACT of 1 is optimized. */

      else
        {
        if (repeat_min != 1)
          {
          *code++ = OP_EXACT + op_type;  /* NB EXACT doesn't have repeat_type */
          *code++ = repeat_min >> 8;
          *code++ = (repeat_min & 255);
          }

        /* If the mininum is 1 and the previous item was a character string,
        we either have to put back the item that got cancelled if the string
        length was 1, or add the character back onto the end of a longer
        string. For a character type nothing need be done; it will just get
        put back naturally. Note that the final character is always going to
        get added below. */

        else if (*previous == OP_CHARS)
          {
          if (code == previous) code += 2; else previous[1]++;
          }

        /*  For a single negated character we also have to put back the
        item that got cancelled. */

        else if (*previous == OP_NOT) code++;

        /* If the maximum is unlimited, insert an OP_STAR. */

        if (repeat_max < 0)
          {
          *code++ = c;
          *code++ = OP_STAR + repeat_type;
          }

        /* Else insert an UPTO if the max is greater than the min. */

        else if (repeat_max != repeat_min)
          {
          *code++ = c;
          repeat_max -= repeat_min;
          *code++ = OP_UPTO + repeat_type;
          *code++ = repeat_max >> 8;
          *code++ = (repeat_max & 255);
          }
        }

      /* The character or character type itself comes last in all cases. */

      *code++ = c;
      }

    /* If previous was a character class or a back reference, we put the repeat
    stuff after it, but just skip the item if the repeat was {0,0}. */

    else if (*previous == OP_CLASS || *previous == OP_REF)
      {
      if (repeat_max == 0)
        {
        code = previous;
        goto END_REPEAT;
        }
      if (repeat_min == 0 && repeat_max == -1)
        *code++ = OP_CRSTAR + repeat_type;
      else if (repeat_min == 1 && repeat_max == -1)
        *code++ = OP_CRPLUS + repeat_type;
      else if (repeat_min == 0 && repeat_max == 1)
        *code++ = OP_CRQUERY + repeat_type;
      else
        {
        *code++ = OP_CRRANGE + repeat_type;
        *code++ = repeat_min >> 8;
        *code++ = repeat_min & 255;
        if (repeat_max == -1) repeat_max = 0;  /* 2-byte encoding for max */
        *code++ = repeat_max >> 8;
        *code++ = repeat_max & 255;
        }
      }

    /* If previous was a bracket group, we may have to replicate it in certain
    cases. */

    else if ((int)*previous >= OP_BRA || (int)*previous == OP_ONCE ||
             (int)*previous == OP_COND)
      {
      register int i;
      int ketoffset = 0;
      int len = code - previous;
      uschar *bralink = NULL;

      /* If the maximum repeat count is unlimited, find the end of the bracket
      by scanning through from the start, and compute the offset back to it
      from the current code pointer. There may be an OP_OPT setting following
      the final KET, so we can't find the end just by going back from the code
      pointer. */

      if (repeat_max == -1)
        {
        register uschar *ket = previous;
        do ket += (ket[1] << 8) + ket[2]; while (*ket != OP_KET);
        ketoffset = code - ket;
        }

      /* The case of a zero minimum is special because of the need to stick
      OP_BRAZERO in front of it, and because the group appears once in the
      data, whereas in other cases it appears the minimum number of times. For
      this reason, it is simplest to treat this case separately, as otherwise
      the code gets far too messy. There are several special subcases when the
      minimum is zero. */

      if (repeat_min == 0)
        {
        /* If we set up a required char from the bracket, we must back off
        to the previous value and reset the countlits value too. */

        if (subcountlits > 0)
          {
          *reqchar = prevreqchar;
          *countlits -= subcountlits;
          }

        /* If the maximum is also zero, we just omit the group from the output
        altogether. */

        if (repeat_max == 0)
          {
          code = previous;
          goto END_REPEAT;
          }

        /* If the maximum is 1 or unlimited, we just have to stick in the
        BRAZERO and do no more at this point. */

        if (repeat_max <= 1)
          {
          memmove(previous+1, previous, len);
          code++;
          *previous++ = OP_BRAZERO + repeat_type;
          }

        /* If the maximum is greater than 1 and limited, we have to replicate
        in a nested fashion, sticking OP_BRAZERO before each set of brackets.
        The first one has to be handled carefully because it's the original
        copy, which has to be moved up. The remainder can be handled by code
        that is common with the non-zero minimum case below. We just have to
        adjust the value or repeat_max, since one less copy is required. */

        else
          {
          int offset;
          memmove(previous+4, previous, len);
          code += 4;
          *previous++ = OP_BRAZERO + repeat_type;
          *previous++ = OP_BRA;

          /* We chain together the bracket offset fields that have to be
          filled in later when the ends of the brackets are reached. */

          offset = (bralink == NULL)? 0 : previous - bralink;
          bralink = previous;
          *previous++ = offset >> 8;
          *previous++ = offset & 255;
          }

        repeat_max--;
        }

      /* If the minimum is greater than zero, replicate the group as many
      times as necessary, and adjust the maximum to the number of subsequent
      copies that we need. */

      else
        {
        for (i = 1; i < repeat_min; i++)
          {
          memcpy(code, previous, len);
          code += len;
          }
        if (repeat_max > 0) repeat_max -= repeat_min;
        }

      /* This code is common to both the zero and non-zero minimum cases. If
      the maximum is limited, it replicates the group in a nested fashion,
      remembering the bracket starts on a stack. In the case of a zero minimum,
      the first one was set up above. In all cases the repeat_max now specifies
      the number of additional copies needed. */

      if (repeat_max >= 0)
        {
        for (i = repeat_max - 1; i >= 0; i--)
          {
          *code++ = OP_BRAZERO + repeat_type;

          /* All but the final copy start a new nesting, maintaining the
          chain of brackets outstanding. */

          if (i != 0)
            {
            int offset;
            *code++ = OP_BRA;
            offset = (bralink == NULL)? 0 : code - bralink;
            bralink = code;
            *code++ = offset >> 8;
            *code++ = offset & 255;
            }

          memcpy(code, previous, len);
          code += len;
          }

        /* Now chain through the pending brackets, and fill in their length
        fields (which are holding the chain links pro tem). */

        while (bralink != NULL)
          {
          int oldlinkoffset;
          int offset = code - bralink + 1;
          uschar *bra = code - offset;
          oldlinkoffset = (bra[1] << 8) + bra[2];
          bralink = (oldlinkoffset == 0)? NULL : bralink - oldlinkoffset;
          *code++ = OP_KET;
          *code++ = bra[1] = offset >> 8;
          *code++ = bra[2] = (offset & 255);
          }
        }

      /* If the maximum is unlimited, set a repeater in the final copy. We
      can't just offset backwards from the current code point, because we
      don't know if there's been an options resetting after the ket. The
      correct offset was computed above. */

      else code[-ketoffset] = OP_KETRMAX + repeat_type;
      }

    /* Else there's some kind of shambles */

    else
      {
      *errorptr = ERR11;
      goto FAILED;
      }

    /* In all case we no longer have a previous item. */

    END_REPEAT:
    previous = NULL;
    break;


    /* Start of nested bracket sub-expression, or comment or lookahead or
    lookbehind or option setting or condition. First deal with special things
    that can come after a bracket; all are introduced by ?, and the appearance
    of any of them means that this is not a referencing group. They were
    checked for validity in the first pass over the string, so we don't have to
    check for syntax errors here.  */

    case '(':
    newoptions = options;
    skipbytes = 0;

    if (*(++ptr) == '?')
      {
      int set, unset;
      int *optset;

      switch (*(++ptr))
        {
        case '#':                 /* Comment; skip to ket */
        ptr++;
        while (*ptr != ')') ptr++;
        continue;

        case ':':                 /* Non-extracting bracket */
        bravalue = OP_BRA;
        ptr++;
        break;

        case '(':
        bravalue = OP_COND;       /* Conditional group */
        if ((cd->ctypes[*(++ptr)] & ctype_digit) != 0)
          {
          int condref = *ptr - '0';
          while (*(++ptr) != ')') condref = condref*10 + *ptr - '0';
          if (condref == 0)
            {
            *errorptr = ERR35;
            goto FAILED;
            }
          ptr++;
          code[3] = OP_CREF;
          code[4] = condref >> 8;
          code[5] = condref & 255;
          skipbytes = 3;
          }
        else ptr--;
        break;

        case '=':                 /* Positive lookahead */
        bravalue = OP_ASSERT;
        ptr++;
        break;

        case '!':                 /* Negative lookahead */
        bravalue = OP_ASSERT_NOT;
        ptr++;
        break;

        case '<':                 /* Lookbehinds */
        switch (*(++ptr))
          {
          case '=':               /* Positive lookbehind */
          bravalue = OP_ASSERTBACK;
          ptr++;
          break;

          case '!':               /* Negative lookbehind */
          bravalue = OP_ASSERTBACK_NOT;
          ptr++;
          break;

          default:                /* Syntax error */
          *errorptr = ERR24;
          goto FAILED;
          }
        break;

        case '>':                 /* One-time brackets */
        bravalue = OP_ONCE;
        ptr++;
        break;

        case 'R':                 /* Pattern recursion */
        *code++ = OP_RECURSE;
        ptr++;
        continue;

        default:                  /* Option setting */
        set = unset = 0;
        optset = &set;

        while (*ptr != ')' && *ptr != ':')
          {
          switch (*ptr++)
            {
            case '-': optset = &unset; break;

            case 'i': *optset |= PCRE_CASELESS; break;
            case 'm': *optset |= PCRE_MULTILINE; break;
            case 's': *optset |= PCRE_DOTALL; break;
            case 'x': *optset |= PCRE_EXTENDED; break;
            case 'U': *optset |= PCRE_UNGREEDY; break;
            case 'X': *optset |= PCRE_EXTRA; break;

            default:
            *errorptr = ERR12;
            goto FAILED;
            }
          }

        /* Set up the changed option bits, but don't change anything yet. */

        newoptions = (options | set) & (~unset);

        /* If the options ended with ')' this is not the start of a nested
        group with option changes, so the options change at this level. At top
        level there is nothing else to be done (the options will in fact have
        been set from the start of compiling as a result of the first pass) but
        at an inner level we must compile code to change the ims options if
        necessary, and pass the new setting back so that it can be put at the
        start of any following branches, and when this group ends, a resetting
        item can be compiled. */

        if (*ptr == ')')
          {
          if ((options & PCRE_INGROUP) != 0 &&
              (options & PCRE_IMS) != (newoptions & PCRE_IMS))
            {
            *code++ = OP_OPT;
            *code++ = *optchanged = newoptions & PCRE_IMS;
            }
          options = newoptions;  /* Change options at this level */
          previous = NULL;       /* This item can't be repeated */
          continue;              /* It is complete */
          }

        /* If the options ended with ':' we are heading into a nested group
        with possible change of options. Such groups are non-capturing and are
        not assertions of any kind. All we need to do is skip over the ':';
        the newoptions value is handled below. */

        bravalue = OP_BRA;
        ptr++;
        }
      }

    /* Else we have a referencing group; adjust the opcode. If the bracket
    number is greater than EXTRACT_BASIC_MAX, we set the opcode one higher, and
    arrange for the true number to follow later, in an OP_BRANUMBER item. */

    else
      {
      if (++(*brackets) > EXTRACT_BASIC_MAX)
        {
        bravalue = OP_BRA + EXTRACT_BASIC_MAX + 1;
        code[3] = OP_BRANUMBER;
        code[4] = *brackets >> 8;
        code[5] = *brackets & 255;
        skipbytes = 3;
        }
      else bravalue = OP_BRA + *brackets;
      }

    /* Process nested bracketed re. Assertions may not be repeated, but other
    kinds can be. We copy code into a non-register variable in order to be able
    to pass its address because some compilers complain otherwise. Pass in a
    new setting for the ims options if they have changed. */

    previous = (bravalue >= OP_ONCE)? code : NULL;
    *code = bravalue;
    tempcode = code;

    if (!compile_regex(
         options | PCRE_INGROUP,       /* Set for all nested groups */
         ((options & PCRE_IMS) != (newoptions & PCRE_IMS))?
           newoptions & PCRE_IMS : -1, /* Pass ims options if changed */
         brackets,                     /* Extracting bracket count */
         &tempcode,                    /* Where to put code (updated) */
         &ptr,                         /* Input pointer (updated) */
         errorptr,                     /* Where to put an error message */
         (bravalue == OP_ASSERTBACK ||
          bravalue == OP_ASSERTBACK_NOT), /* TRUE if back assert */
         skipbytes,                    /* Skip over OP_COND/OP_BRANUMBER */
         &subreqchar,                  /* For possible last char */
         &subcountlits,                /* For literal count */
         cd))                          /* Tables block */
      goto FAILED;

    /* At the end of compiling, code is still pointing to the start of the
    group, while tempcode has been updated to point past the end of the group
    and any option resetting that may follow it. The pattern pointer (ptr)
    is on the bracket. */

    /* If this is a conditional bracket, check that there are no more than
    two branches in the group. */

    else if (bravalue == OP_COND)
      {
      uschar *tc = code;
      condcount = 0;

      do {
         condcount++;
         tc += (tc[1] << 8) | tc[2];
         }
      while (*tc != OP_KET);

      if (condcount > 2)
        {
        *errorptr = ERR27;
        goto FAILED;
        }
      }

    /* Handle updating of the required character. If the subpattern didn't
    set one, leave it as it was. Otherwise, update it for normal brackets of
    all kinds, forward assertions, and conditions with two branches. Don't
    update the literal count for forward assertions, however. If the bracket
    is followed by a quantifier with zero repeat, we have to back off. Hence
    the definition of prevreqchar and subcountlits outside the main loop so
    that they can be accessed for the back off. */

    if (subreqchar > 0 &&
         (bravalue >= OP_BRA || bravalue == OP_ONCE || bravalue == OP_ASSERT ||
         (bravalue == OP_COND && condcount == 2)))
      {
      prevreqchar = *reqchar;
      *reqchar = subreqchar;
      if (bravalue != OP_ASSERT) *countlits += subcountlits;
      }

    /* Now update the main code pointer to the end of the group. */

    code = tempcode;

    /* Error if hit end of pattern */

    if (*ptr != ')')
      {
      *errorptr = ERR14;
      goto FAILED;
      }
    break;

    /* Check \ for being a real metacharacter; if not, fall through and handle
    it as a data character at the start of a string. Escape items are checked
    for validity in the pre-compiling pass. */

    case '\\':
    tempptr = ptr;
    c = check_escape(&ptr, errorptr, *brackets, options, FALSE, cd);

    /* Handle metacharacters introduced by \. For ones like \d, the ESC_ values
    are arranged to be the negation of the corresponding OP_values. For the
    back references, the values are ESC_REF plus the reference number. Only
    back references and those types that consume a character may be repeated.
    We can test for values between ESC_b and ESC_Z for the latter; this may
    have to change if any new ones are ever created. */

    if (c < 0)
      {
      if (-c >= ESC_REF)
        {
        int number = -c - ESC_REF;
        previous = code;
        *code++ = OP_REF;
        *code++ = number >> 8;
        *code++ = number & 255;
        }
      else
        {
        previous = (-c > ESC_b && -c < ESC_Z)? code : NULL;
        *code++ = -c;
        }
      continue;
      }

    /* Data character: reset and fall through */

    ptr = tempptr;
    c = '\\';

    /* Handle a run of data characters until a metacharacter is encountered.
    The first character is guaranteed not to be whitespace or # when the
    extended flag is set. */

    NORMAL_CHAR:
    default:
    previous = code;
    *code = OP_CHARS;
    code += 2;
    length = 0;

    do
      {
      if ((options & PCRE_EXTENDED) != 0)
        {
        if ((cd->ctypes[c] & ctype_space) != 0) continue;
        if (c == '#')
          {
          /* The space before the ; is to avoid a warning on a silly compiler
          on the Macintosh. */
          while ((c = *(++ptr)) != 0 && c != NEWLINE) ;
          if (c == 0) break;
          continue;
          }
        }

      /* Backslash may introduce a data char or a metacharacter. Escaped items
      are checked for validity in the pre-compiling pass. Stop the string
      before a metaitem. */

      if (c == '\\')
        {
        tempptr = ptr;
        c = check_escape(&ptr, errorptr, *brackets, options, FALSE, cd);
        if (c < 0) { ptr = tempptr; break; }

        /* If a character is > 127 in UTF-8 mode, we have to turn it into
        two or more characters in the UTF-8 encoding. */

#ifdef SUPPORT_UTF8
        if (c > 127 && (options & PCRE_UTF8) != 0)
          {
          uschar buffer[8];
          int len = ord2utf8(c, buffer);
          for (c = 0; c < len; c++) *code++ = buffer[c];
          length += len;
          continue;
          }
#endif
        }

      /* Ordinary character or single-char escape */

      *code++ = c;
      length++;
      }

    /* This "while" is the end of the "do" above. */

    while (length < MAXLIT && (cd->ctypes[c = *(++ptr)] & ctype_meta) == 0);

    /* Update the last character and the count of literals */

    prevreqchar = (length > 1)? code[-2] : *reqchar;
    *reqchar = code[-1];
    *countlits += length;

    /* Compute the length and set it in the data vector, and advance to
    the next state. */

    previous[1] = length;
    if (length < MAXLIT) ptr--;
    break;
    }
  }                   /* end of big loop */

/* Control never reaches here by falling through, only by a goto for all the
error states. Pass back the position in the pattern so that it can be displayed
to the user for diagnosing the error. */

FAILED:
*ptrptr = ptr;
return FALSE;
}