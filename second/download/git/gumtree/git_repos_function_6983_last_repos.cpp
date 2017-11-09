static int
internal_function
check_node_accept (const re_match_context_t *mctx, const re_token_t *node,
		   int idx)
{
  unsigned char ch;
  ch = re_string_byte_at (&mctx->input, idx);
  switch (node->type)
    {
    case CHARACTER:
      if (node->opr.c != ch)
	return 0;
      break;

    case SIMPLE_BRACKET:
      if (!bitset_contain (node->opr.sbcset, ch))
	return 0;
      break;

#ifdef RE_ENABLE_I18N
    case OP_UTF8_PERIOD:
      if (ch >= 0x80)
	return 0;
      /* FALLTHROUGH */
#endif
    case OP_PERIOD:
      if ((ch == '\n' && !(mctx->dfa->syntax & RE_DOT_NEWLINE))
	  || (ch == '\0' && (mctx->dfa->syntax & RE_DOT_NOT_NULL)))
	return 0;
      break;

    default:
      return 0;
    }

  if (node->constraint)
    {
      /* The node has constraints.  Check whether the current context
	 satisfies the constraints.  */
      unsigned int context = re_string_context_at (&mctx->input, idx,
						   mctx->eflags);
      if (NOT_SATISFY_NEXT_CONSTRAINT (node->constraint, context))
	return 0;
    }

  return 1;
}