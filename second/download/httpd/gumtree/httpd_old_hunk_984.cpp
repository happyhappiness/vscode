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
