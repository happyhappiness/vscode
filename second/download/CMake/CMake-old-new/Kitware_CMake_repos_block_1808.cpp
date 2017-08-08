{ /* beginning of action switch */
			case 0: /* must back up */
			/* undo the effects of YY_DO_BEFORE_ACTION */
			*yy_cp = yyg->yy_hold_char;
			yy_cp = yyg->yy_last_accepting_cpos;
			yy_current_state = yyg->yy_last_accepting_state;
			goto yy_find_action;

case 1:
/* rule 1 can match eol */
YY_RULE_SETUP
#line 82 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_Newline;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  ++lexer->line;
  lexer->column = 1;
  BEGIN(INITIAL);
  return 1;
}
	YY_BREAK
case 2:
/* rule 2 can match eol */
YY_RULE_SETUP
#line 91 "cmListFileLexer.in.l"
{
  const char* bracket = yytext;
  lexer->comment = yytext[0] == '#';
  if (lexer->comment) {
    lexer->token.type = cmListFileLexer_Token_CommentBracket;
    bracket += 1;
  } else {
    lexer->token.type = cmListFileLexer_Token_ArgumentBracket;
  }
  cmListFileLexerSetToken(lexer, "", 0);
  lexer->bracket = strchr(bracket+1, '[') - bracket;
  if (yytext[yyleng-1] == '\n') {
    ++lexer->line;
    lexer->column = 1;
  } else {
    lexer->column += yyleng;
  }
  BEGIN(BRACKET);
}
	YY_BREAK
case 3:
YY_RULE_SETUP
#line 111 "cmListFileLexer.in.l"
{
  lexer->column += yyleng;
  BEGIN(COMMENT);
}
	YY_BREAK
case 4:
YY_RULE_SETUP
#line 116 "cmListFileLexer.in.l"
{
  lexer->column += yyleng;
}
	YY_BREAK
case 5:
YY_RULE_SETUP
#line 120 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_ParenLeft;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case 6:
YY_RULE_SETUP
#line 127 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_ParenRight;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case 7:
YY_RULE_SETUP
#line 134 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_Identifier;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case 8:
YY_RULE_SETUP
#line 141 "cmListFileLexer.in.l"
{
  /* Handle ]]====]=======]*/
  cmListFileLexerAppend(lexer, yytext, yyleng);
  lexer->column += yyleng;
  if (yyleng == lexer->bracket) {
    BEGIN(BRACKETEND);
  }
}
	YY_BREAK
case 9:
YY_RULE_SETUP
#line 150 "cmListFileLexer.in.l"
{
  lexer->column += yyleng;
  /* Erase the partial bracket from the token.  */
  lexer->token.length -= lexer->bracket;
  lexer->token.text[lexer->token.length] = 0;
  BEGIN(INITIAL);
  return 1;
}
	YY_BREAK
case 10:
YY_RULE_SETUP
#line 159 "cmListFileLexer.in.l"
{
  cmListFileLexerAppend(lexer, yytext, yyleng);
  lexer->column += yyleng;
}
	YY_BREAK
case 11:
/* rule 11 can match eol */
YY_RULE_SETUP
#line 164 "cmListFileLexer.in.l"
{
  cmListFileLexerAppend(lexer, yytext, yyleng);
  ++lexer->line;
  lexer->column = 1;
  BEGIN(BRACKET);
}
	YY_BREAK
case 12:
YY_RULE_SETUP
#line 171 "cmListFileLexer.in.l"
{
  cmListFileLexerAppend(lexer, yytext, yyleng);
  lexer->column += yyleng;
  BEGIN(BRACKET);
}
	YY_BREAK
case YY_STATE_EOF(BRACKET):
case YY_STATE_EOF(BRACKETEND):
#line 177 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_BadBracket;
  BEGIN(INITIAL);
  return 1;
}
	YY_BREAK
case 13:
YY_RULE_SETUP
#line 183 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_ArgumentUnquoted;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case 14:
YY_RULE_SETUP
#line 190 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_ArgumentUnquoted;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case 15:
YY_RULE_SETUP
#line 197 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_ArgumentUnquoted;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case 16:
YY_RULE_SETUP
#line 204 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_ArgumentQuoted;
  cmListFileLexerSetToken(lexer, "", 0);
  lexer->column += yyleng;
  BEGIN(STRING);
}
	YY_BREAK
case 17:
YY_RULE_SETUP
#line 211 "cmListFileLexer.in.l"
{
  cmListFileLexerAppend(lexer, yytext, yyleng);
  lexer->column += yyleng;
}
	YY_BREAK
case 18:
/* rule 18 can match eol */
YY_RULE_SETUP
#line 216 "cmListFileLexer.in.l"
{
  /* Continuation: text is not part of string */
  ++lexer->line;
  lexer->column = 1;
}
	YY_BREAK
case 19:
/* rule 19 can match eol */
YY_RULE_SETUP
#line 222 "cmListFileLexer.in.l"
{
  cmListFileLexerAppend(lexer, yytext, yyleng);
  ++lexer->line;
  lexer->column = 1;
}
	YY_BREAK
case 20:
YY_RULE_SETUP
#line 228 "cmListFileLexer.in.l"
{
  lexer->column += yyleng;
  BEGIN(INITIAL);
  return 1;
}
	YY_BREAK
case 21:
YY_RULE_SETUP
#line 234 "cmListFileLexer.in.l"
{
  cmListFileLexerAppend(lexer, yytext, yyleng);
  lexer->column += yyleng;
}
	YY_BREAK
case YY_STATE_EOF(STRING):
#line 239 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_BadString;
  BEGIN(INITIAL);
  return 1;
}
	YY_BREAK
case 22:
YY_RULE_SETUP
#line 245 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_Space;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case 23:
YY_RULE_SETUP
#line 252 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_BadCharacter;
  cmListFileLexerSetToken(lexer, yytext, yyleng);
  lexer->column += yyleng;
  return 1;
}
	YY_BREAK
case YY_STATE_EOF(INITIAL):
case YY_STATE_EOF(COMMENT):
#line 259 "cmListFileLexer.in.l"
{
  lexer->token.type = cmListFileLexer_Token_None;
  cmListFileLexerSetToken(lexer, 0, 0);
  return 0;
}
	YY_BREAK
case 24:
YY_RULE_SETUP
#line 265 "cmListFileLexer.in.l"
ECHO;
	YY_BREAK
#line 1205 "cmListFileLexer.c"

	case YY_END_OF_BUFFER:
		{
		/* Amount of text matched not including the EOB char. */
		int yy_amount_of_matched_text = (int) (yy_cp - yyg->yytext_ptr) - 1;

		/* Undo the effects of YY_DO_BEFORE_ACTION. */
		*yy_cp = yyg->yy_hold_char;
		YY_RESTORE_YY_MORE_OFFSET

		if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW )
			{
			/* We're scanning a new file or input source.  It's
			 * possible that this happened because the user
			 * just pointed yyin at a new source and called
			 * cmListFileLexer_yylex().  If so, then we have to assure
			 * consistency between YY_CURRENT_BUFFER and our
			 * globals.  Here is the right place to do so, because
			 * this is the first action (other than possibly a
			 * back-up) that will match for the new input source.
			 */
			yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
			YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
			}

		/* Note that here we test for yy_c_buf_p "<=" to the position
		 * of the first EOB in the buffer, since yy_c_buf_p will
		 * already have been incremented past the NUL character
		 * (since all states make transitions on EOB to the
		 * end-of-buffer state).  Contrast this with the test
		 * in input().
		 */
		if ( yyg->yy_c_buf_p <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] )
			{ /* This was really a NUL. */
			yy_state_type yy_next_state;

			yyg->yy_c_buf_p = yyg->yytext_ptr + yy_amount_of_matched_text;

			yy_current_state = yy_get_previous_state( yyscanner );

			/* Okay, we're now positioned to make the NUL
			 * transition.  We couldn't have
			 * yy_get_previous_state() go ahead and do it
			 * for us because it doesn't know how to deal
			 * with the possibility of jamming (and we don't
			 * want to build jamming into it because then it
			 * will run more slowly).
			 */

			yy_next_state = yy_try_NUL_trans( yy_current_state , yyscanner);

			yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;

			if ( yy_next_state )
				{
				/* Consume the NUL. */
				yy_cp = ++yyg->yy_c_buf_p;
				yy_current_state = yy_next_state;
				goto yy_match;
				}

			else
				{
				yy_cp = yyg->yy_c_buf_p;
				goto yy_find_action;
				}
			}

		else switch ( yy_get_next_buffer( yyscanner ) )
			{
			case EOB_ACT_END_OF_FILE:
				{
				yyg->yy_did_buffer_switch_on_eof = 0;

				if ( cmListFileLexer_yywrap(yyscanner ) )
					{
					/* Note: because we've taken care in
					 * yy_get_next_buffer() to have set up
					 * yytext, we can now set up
					 * yy_c_buf_p so that if some total
					 * hoser (like flex itself) wants to
					 * call the scanner after we return the
					 * YY_NULL, it'll still work - another
					 * YY_NULL will get returned.
					 */
					yyg->yy_c_buf_p = yyg->yytext_ptr + YY_MORE_ADJ;

					yy_act = YY_STATE_EOF(YY_START);
					goto do_action;
					}

				else
					{
					if ( ! yyg->yy_did_buffer_switch_on_eof )
						YY_NEW_FILE;
					}
				break;
				}

			case EOB_ACT_CONTINUE_SCAN:
				yyg->yy_c_buf_p =
					yyg->yytext_ptr + yy_amount_of_matched_text;

				yy_current_state = yy_get_previous_state( yyscanner );

				yy_cp = yyg->yy_c_buf_p;
				yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
				goto yy_match;

			case EOB_ACT_LAST_MATCH:
				yyg->yy_c_buf_p =
				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars];

				yy_current_state = yy_get_previous_state( yyscanner );

				yy_cp = yyg->yy_c_buf_p;
				yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
				goto yy_find_action;
			}
		break;
		}

	default:
		YY_FATAL_ERROR(
			"fatal flex scanner internal error--no action found" );
	}