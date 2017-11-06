int
re_compile_fastmap (bufp)
     struct re_pattern_buffer *bufp;
{
  int j, k;
#ifdef MATCH_MAY_ALLOCATE
  fail_stack_type fail_stack;
#endif
#ifndef REGEX_MALLOC
  char *destination;
#endif
  register char *fastmap = bufp->fastmap;
  unsigned char *pattern = bufp->buffer;
  unsigned char *p = pattern;
  register unsigned char *pend = pattern + bufp->used;

#ifdef REL_ALLOC
  /* This holds the pointer to the failure stack, when
     it is allocated relocatably.  */
  fail_stack_elt_t *failure_stack_ptr;
#endif

  /* Assume that each path through the pattern can be null until
     proven otherwise.  We set this false at the bottom of switch
     statement, to which we get only if a particular path doesn't
     match the empty string.  */
  boolean path_can_be_null = true;

  /* We aren't doing a `succeed_n' to begin with.  */
  boolean succeed_n_p = false;

  assert (fastmap != NULL && p != NULL);

  INIT_FAIL_STACK ();
  bzero (fastmap, 1 << BYTEWIDTH);  /* Assume nothing's valid.  */
  bufp->fastmap_accurate = 1;	    /* It will be when we're done.  */
  bufp->can_be_null = 0;

  while (1)
    {
      if (p == pend || *p == succeed)
	{
	  /* We have reached the (effective) end of pattern.  */
	  if (!FAIL_STACK_EMPTY ())
	    {
	      bufp->can_be_null |= path_can_be_null;

	      /* Reset for next path.  */
	      path_can_be_null = true;

	      p = fail_stack.stack[--fail_stack.avail].pointer;

	      continue;
	    }
	  else
	    break;
	}

      /* We should never be about to go beyond the end of the pattern.  */
      assert (p < pend);

      switch (SWITCH_ENUM_CAST ((re_opcode_t) *p++))
	{

        /* I guess the idea here is to simply not bother with a fastmap
           if a backreference is used, since it's too hard to figure out
           the fastmap for the corresponding group.  Setting
           `can_be_null' stops `re_search_2' from using the fastmap, so
           that is all we do.  */
	case duplicate:
	  bufp->can_be_null = 1;
          goto done;


      /* Following are the cases which match a character.  These end
         with `break'.  */

	case exactn:
          fastmap[p[1]] = 1;
	  break;


        case charset:
          for (j = *p++ * BYTEWIDTH - 1; j >= 0; j--)
	    if (p[j / BYTEWIDTH] & (1 << (j % BYTEWIDTH)))
              fastmap[j] = 1;
	  break;


	case charset_not:
	  /* Chars beyond end of map must be allowed.  */
	  for (j = *p * BYTEWIDTH; j < (1 << BYTEWIDTH); j++)
            fastmap[j] = 1;

	  for (j = *p++ * BYTEWIDTH - 1; j >= 0; j--)
	    if (!(p[j / BYTEWIDTH] & (1 << (j % BYTEWIDTH))))
              fastmap[j] = 1;
          break;


	case wordchar:
	  for (j = 0; j < (1 << BYTEWIDTH); j++)
	    if (SYNTAX (j) == Sword)
	      fastmap[j] = 1;
	  break;


	case notwordchar:
	  for (j = 0; j < (1 << BYTEWIDTH); j++)
	    if (SYNTAX (j) != Sword)
	      fastmap[j] = 1;
	  break;


        case anychar:
	  {
	    int fastmap_newline = fastmap['\n'];

	    /* `.' matches anything ...  */
	    for (j = 0; j < (1 << BYTEWIDTH); j++)
	      fastmap[j] = 1;

	    /* ... except perhaps newline.  */
	    if (!(bufp->syntax & RE_DOT_NEWLINE))
	      fastmap['\n'] = fastmap_newline;

	    /* Return if we have already set `can_be_null'; if we have,
	       then the fastmap is irrelevant.  Something's wrong here.  */
	    else if (bufp->can_be_null)
	      goto done;

	    /* Otherwise, have to check alternative paths.  */
	    break;
	  }

#ifdef emacs
        case syntaxspec:
	  k = *p++;
	  for (j = 0; j < (1 << BYTEWIDTH); j++)
	    if (SYNTAX (j) == (enum syntaxcode) k)
	      fastmap[j] = 1;
	  break;


	case notsyntaxspec:
	  k = *p++;
	  for (j = 0; j < (1 << BYTEWIDTH); j++)
	    if (SYNTAX (j) != (enum syntaxcode) k)
	      fastmap[j] = 1;
	  break;


      /* All cases after this match the empty string.  These end with
         `continue'.  */


	case before_dot:
	case at_dot:
	case after_dot:
          continue;
#endif /* emacs */


        case no_op:
        case begline:
        case endline:
	case begbuf:
	case endbuf:
	case wordbound:
	case notwordbound:
	case wordbeg:
	case wordend:
        case push_dummy_failure:
          continue;


	case jump_n:
        case pop_failure_jump:
	case maybe_pop_jump:
	case jump:
        case jump_past_alt:
	case dummy_failure_jump:
          EXTRACT_NUMBER_AND_INCR (j, p);
	  p += j;
	  if (j > 0)
	    continue;

          /* Jump backward implies we just went through the body of a
             loop and matched nothing.  Opcode jumped to should be
             `on_failure_jump' or `succeed_n'.  Just treat it like an
             ordinary jump.  For a * loop, it has pushed its failure
             point already; if so, discard that as redundant.  */
          if ((re_opcode_t) *p != on_failure_jump
	      && (re_opcode_t) *p != succeed_n)
	    continue;

          p++;
          EXTRACT_NUMBER_AND_INCR (j, p);
          p += j;

          /* If what's on the stack is where we are now, pop it.  */
          if (!FAIL_STACK_EMPTY ()
	      && fail_stack.stack[fail_stack.avail - 1].pointer == p)
            fail_stack.avail--;

          continue;


        case on_failure_jump:
        case on_failure_keep_string_jump:
	handle_on_failure_jump:
          EXTRACT_NUMBER_AND_INCR (j, p);

          /* For some patterns, e.g., `(a?)?', `p+j' here points to the
             end of the pattern.  We don't want to push such a point,
             since when we restore it above, entering the switch will
             increment `p' past the end of the pattern.  We don't need
             to push such a point since we obviously won't find any more
             fastmap entries beyond `pend'.  Such a pattern can match
             the null string, though.  */
          if (p + j < pend)
            {
              if (!PUSH_PATTERN_OP (p + j, fail_stack))
		{
		  RESET_FAIL_STACK ();
		  return -2;
		}
            }
          else
            bufp->can_be_null = 1;

          if (succeed_n_p)
            {
              EXTRACT_NUMBER_AND_INCR (k, p);	/* Skip the n.  */
              succeed_n_p = false;
	    }

          continue;


	case succeed_n:
          /* Get to the number of times to succeed.  */
          p += 2;

          /* Increment p past the n for when k != 0.  */
          EXTRACT_NUMBER_AND_INCR (k, p);
          if (k == 0)
	    {
              p -= 4;
  	      succeed_n_p = true;  /* Spaghetti code alert.  */
              goto handle_on_failure_jump;
            }
          continue;


	case set_number_at:
          p += 4;
          continue;


	case start_memory:
        case stop_memory:
	  p += 2;
	  continue;


	default:
          abort (); /* We have listed all the cases.  */
        } /* switch *p++ */

      /* Getting here means we have found the possible starting
         characters for one path of the pattern -- and that the empty
         string does not match.  We need not follow this path further.
         Instead, look at the next alternative (remembered on the
         stack), or quit if no more.  The test at the top of the loop
         does these things.  */
      path_can_be_null = false;
      p = pend;
    } /* while p */

  /* Set `can_be_null' for the last path (also the first path, if the
     pattern is empty).  */
  bufp->can_be_null |= path_can_be_null;

 done:
  RESET_FAIL_STACK ();
  return 0;
}