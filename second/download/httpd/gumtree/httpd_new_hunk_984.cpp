        }

      /* First, ensure the minimum number of matches are present. */

      for (i = 1; i <= min; i++)
        {
        if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
        GETCHARINC(c, eptr);
        if (!match_xclass(c, data)) RRETURN(MATCH_NOMATCH);
        }

      /* If max == min we can continue with the main loop without the
      need to recurse. */

      if (min == max) continue;

      /* If minimizing, keep testing the rest of the expression and advancing
      the pointer while it matches the class. */

      if (minimize)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          GETCHARINC(c, eptr);
          if (!match_xclass(c, data)) RRETURN(MATCH_NOMATCH);
          }
        /* Control never gets here */
        }

      /* If maximizing, find the longest possible run, then work backwards. */

      else
        {
        pp = eptr;
        for (i = min; i < max; i++)
          {
          int len = 1;
          if (eptr >= md->end_subject) break;
          GETCHARLEN(c, eptr, len);
          if (!match_xclass(c, data)) break;
          eptr += len;
          }
        for(;;)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        /* Stop if tried at original pos */
          BACKCHAR(eptr)
          }
        RRETURN(MATCH_NOMATCH);
        }

      /* Control never gets here */
      }
#endif    /* End of XCLASS */

    /* Match a single character, casefully */

    case OP_CHAR:
#ifdef SUPPORT_UTF8
    if (md->utf8)
      {
      length = 1;
      ecode++;
      GETCHARLEN(fc, ecode, length);
      if (length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
      while (length-- > 0) if (*ecode++ != *eptr++) RRETURN(MATCH_NOMATCH);
      }
    else
#endif

    /* Non-UTF-8 mode */
      {
      if (md->end_subject - eptr < 1) RRETURN(MATCH_NOMATCH);
      if (ecode[1] != *eptr++) RRETURN(MATCH_NOMATCH);
      ecode += 2;
      }
    break;

    /* Match a single character, caselessly */

    case OP_CHARNC:
#ifdef SUPPORT_UTF8
    if (md->utf8)
      {
      length = 1;
      ecode++;
      GETCHARLEN(fc, ecode, length);

      if (length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);

      /* If the pattern character's value is < 128, we have only one byte, and
      can use the fast lookup table. */

      if (fc < 128)
        {
        if (md->lcc[*ecode++] != md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
        }

      /* Otherwise we must pick up the subject character */

      else
        {
        int dc;
        GETCHARINC(dc, eptr);
        ecode += length;

        /* If we have Unicode property support, we can use it to test the other
        case of the character, if there is one. The result of ucp_findchar() is
        < 0 if the char isn't found, and othercase is returned as zero if there
        isn't one. */

        if (fc != dc)
          {
#ifdef SUPPORT_UCP
          int chartype;
          int othercase;
          if (ucp_findchar(fc, &chartype, &othercase) < 0 || dc != othercase)
#endif
            RRETURN(MATCH_NOMATCH);
          }
        }
      }
    else
#endif   /* SUPPORT_UTF8 */

    /* Non-UTF-8 mode */
      {
      if (md->end_subject - eptr < 1) RRETURN(MATCH_NOMATCH);
      if (md->lcc[ecode[1]] != md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
      ecode += 2;
      }
    break;

    /* Match a single character repeatedly; different opcodes share code. */

    case OP_EXACT:
    min = max = GET2(ecode, 1);
    ecode += 3;
    goto REPEATCHAR;

    case OP_UPTO:
    case OP_MINUPTO:
    min = 0;
    max = GET2(ecode, 1);
    minimize = *ecode == OP_MINUPTO;
    ecode += 3;
    goto REPEATCHAR;

    case OP_STAR:
    case OP_MINSTAR:
