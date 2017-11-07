void
print_partial_compiled_pattern (start, end)
    unsigned char *start;
    unsigned char *end;
{
  int mcnt, mcnt2;
  unsigned char *p1;
  unsigned char *p = start;
  unsigned char *pend = end;

  if (start == NULL)
    {
      printf ("(null)\n");
      return;
    }

  /* Loop over pattern commands.  */
  while (p < pend)
    {
      printf ("%d:\t", p - start);

      switch ((re_opcode_t) *p++)
	{
        case no_op:
          printf ("/no_op");
          break;

	case exactn:
	  mcnt = *p++;
          printf ("/exactn/%d", mcnt);
          do
	    {
              putchar ('/');
	      putchar (*p++);
            }
          while (--mcnt);
          break;

	case start_memory:
          mcnt = *p++;
          printf ("/start_memory/%d/%d", mcnt, *p++);
          break;

	case stop_memory:
          mcnt = *p++;
	  printf ("/stop_memory/%d/%d", mcnt, *p++);
          break;

	case duplicate:
	  printf ("/duplicate/%d", *p++);
	  break;

	case anychar:
	  printf ("/anychar");
	  break;

	case charset:
        case charset_not:
          {
            register int c, last = -100;
	    register int in_range = 0;

	    printf ("/charset [%s",
	            (re_opcode_t) *(p - 1) == charset_not ? "^" : "");

            assert (p + *p < pend);

            for (c = 0; c < 256; c++)
	      if (c / 8 < *p
		  && (p[1 + (c/8)] & (1 << (c % 8))))
		{
		  /* Are we starting a range?  */
		  if (last + 1 == c && ! in_range)
		    {
		      putchar ('-');
		      in_range = 1;
		    }
		  /* Have we broken a range?  */
		  else if (last + 1 != c && in_range)
              {
		      putchar (last);
		      in_range = 0;
		    }

		  if (! in_range)
		    putchar (c);

		  last = c;
              }

	    if (in_range)
	      putchar (last);

	    putchar (']');

	    p += 1 + *p;
	  }
	  break;

	case begline:
	  printf ("/begline");
          break;

	case endline:
          printf ("/endline");
          break;

	case on_failure_jump:
          extract_number_and_incr (&mcnt, &p);
  	  printf ("/on_failure_jump to %d", p + mcnt - start);
          break;

	case on_failure_keep_string_jump:
          extract_number_and_incr (&mcnt, &p);
  	  printf ("/on_failure_keep_string_jump to %d", p + mcnt - start);
          break;

	case dummy_failure_jump:
          extract_number_and_incr (&mcnt, &p);
  	  printf ("/dummy_failure_jump to %d", p + mcnt - start);
          break;

	case push_dummy_failure:
          printf ("/push_dummy_failure");
          break;

        case maybe_pop_jump:
          extract_number_and_incr (&mcnt, &p);
  	  printf ("/maybe_pop_jump to %d", p + mcnt - start);
	  break;

        case pop_failure_jump:
	  extract_number_and_incr (&mcnt, &p);
  	  printf ("/pop_failure_jump to %d", p + mcnt - start);
	  break;

        case jump_past_alt:
	  extract_number_and_incr (&mcnt, &p);
  	  printf ("/jump_past_alt to %d", p + mcnt - start);
	  break;

        case jump:
	  extract_number_and_incr (&mcnt, &p);
  	  printf ("/jump to %d", p + mcnt - start);
	  break;

        case succeed_n:
          extract_number_and_incr (&mcnt, &p);
	  p1 = p + mcnt;
          extract_number_and_incr (&mcnt2, &p);
	  printf ("/succeed_n to %d, %d times", p1 - start, mcnt2);
          break;

        case jump_n:
          extract_number_and_incr (&mcnt, &p);
	  p1 = p + mcnt;
          extract_number_and_incr (&mcnt2, &p);
	  printf ("/jump_n to %d, %d times", p1 - start, mcnt2);
          break;

        case set_number_at:
          extract_number_and_incr (&mcnt, &p);
	  p1 = p + mcnt;
          extract_number_and_incr (&mcnt2, &p);
	  printf ("/set_number_at location %d to %d", p1 - start, mcnt2);
          break;

        case wordbound:
	  printf ("/wordbound");
	  break;

	case notwordbound:
	  printf ("/notwordbound");
          break;

	case wordbeg:
	  printf ("/wordbeg");
	  break;

	case wordend:
	  printf ("/wordend");

#ifdef emacs
	case before_dot:
	  printf ("/before_dot");
          break;

	case at_dot:
	  printf ("/at_dot");
          break;

	case after_dot:
	  printf ("/after_dot");
          break;

	case syntaxspec:
          printf ("/syntaxspec");
	  mcnt = *p++;
	  printf ("/%d", mcnt);
          break;

	case notsyntaxspec:
          printf ("/notsyntaxspec");
	  mcnt = *p++;
	  printf ("/%d", mcnt);
	  break;
#endif /* emacs */

	case wordchar:
	  printf ("/wordchar");
          break;

	case notwordchar:
	  printf ("/notwordchar");
          break;

	case begbuf:
	  printf ("/begbuf");
          break;

	case endbuf:
	  printf ("/endbuf");
          break;

        default:
          printf ("?%d", *(p-1));
	}

      putchar ('\n');
    }

  printf ("%d:\tend of pattern.\n", p - start);
}