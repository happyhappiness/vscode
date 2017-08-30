case 8:

/* rule 8 can match eol */

YY_RULE_SETUP



{ 

  //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;

  yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 

  return cal_SYMBOL; 

}

case 9:

YY_RULE_SETUP



{

  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 

  yylvalp->str = yyextra->DOLLARVariable;

  return cal_DOLLAR; 

}

case 10:

YY_RULE_SETUP



{

  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 

  yylvalp->str = yyextra->LCURLYVariable;

  return cal_LCURLY; 

}

case 11:

YY_RULE_SETUP



{

  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 

  yylvalp->str = yyextra->BSLASHVariable;

  return cal_BSLASH; 

}

case 12:

YY_RULE_SETUP



ECHO;

  YY_BREAK



case YY_STATE_EOF(INITIAL):

  yyterminate();



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

       * cmCommandArgument_yylex().  If so, then we have to assure

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



        if ( cmCommandArgument_yywrap(yyscanner ) )

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

  } /* end of action switch */

    } /* end of scanning one token */

} /* end of cmCommandArgument_yylex */



/* yy_get_next_buffer - try to read in a new buffer

 *

 * Returns a code representing an action:

 *  EOB_ACT_LAST_MATCH -

 *  EOB_ACT_CONTINUE_SCAN - continue scanning from current position

 *  EOB_ACT_END_OF_FILE - end of file

 */

static int yy_get_next_buffer (yyscan_t yyscanner)

{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

  register char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;

  register char *source = yyg->yytext_ptr;

  register int number_to_move, i;

  int ret_val;



  if ( yyg->yy_c_buf_p > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] )

    YY_FATAL_ERROR(

    "fatal flex scanner internal error--end of buffer missed" );



  if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 )

    { /* Don't try to fill the buffer, so this is an EOF. */

    if ( yyg->yy_c_buf_p - yyg->yytext_ptr - YY_MORE_ADJ == 1 )

      {

      /* We matched a single character, the EOB, so

       * treat this as a final EOF.

       */

      return EOB_ACT_END_OF_FILE;

      }



    else

      {

      /* We matched some text prior to the EOB, first

       * process it.

       */

      return EOB_ACT_LAST_MATCH;

      }

    }



  /* Try to read more data. */



  /* First move last chars to start of buffer. */

  number_to_move = (int) (yyg->yy_c_buf_p - yyg->yytext_ptr) - 1;



  for ( i = 0; i < number_to_move; ++i )

    *(dest++) = *(source++);



  if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )

    /* don't do the read, it's not guaranteed to return an EOF,

     * just force an EOF

     */

    YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars = 0;



  else

    {

      size_t nuto_read =

      YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;



    while ( nuto_read <= 0 )

      { /* Not enough room in the buffer - grow it. */



      /* just a shorter name for the current buffer */

      YY_BUFFER_STATE b = YY_CURRENT_BUFFER;



      int yy_c_buf_p_offset =

        (int) (yyg->yy_c_buf_p - b->yy_ch_buf);



      if ( b->yy_is_our_buffer )

        {

        int new_size = b->yy_buf_size * 2;



        if ( new_size <= 0 )

          b->yy_buf_size += b->yy_buf_size / 8;

        else

          b->yy_buf_size *= 2;



        b->yy_ch_buf = (char *)

          /* Include room in for 2 EOB chars. */

          cmCommandArgument_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );

        }

      else

        /* Can't grow it, we don't own it. */

        b->yy_ch_buf = 0;



      if ( ! b->yy_ch_buf )

        YY_FATAL_ERROR(

        "fatal error - scanner input buffer overflow" );



      yyg->yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];



      nuto_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -

            number_to_move - 1;



      }



    if ( nuto_read > YY_READ_BUF_SIZE )

      nuto_read = YY_READ_BUF_SIZE;



    /* Read in more data. */

    YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),

      yyg->yy_n_chars, nuto_read );



    YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;

    }



  if ( yyg->yy_n_chars == 0 )

    {

    if ( number_to_move == YY_MORE_ADJ )

      {

      ret_val = EOB_ACT_END_OF_FILE;

      cmCommandArgument_yyrestart(yyin  ,yyscanner);

      }



    else

      {

      ret_val = EOB_ACT_LAST_MATCH;

      YY_CURRENT_BUFFER_LVALUE->yy_buffer_status =

        YY_BUFFER_EOF_PENDING;

      }

    }



  else

    ret_val = EOB_ACT_CONTINUE_SCAN;



  yyg->yy_n_chars += number_to_move;

  YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;

  YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;



  yyg->yytext_ptr = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];



  return ret_val;

}



/* yy_get_previous_state - get the state just before the EOB char was

   reached */



    static yy_state_type yy_get_previous_state (yyscan_t yyscanner)

{

  register yy_state_type yy_current_state;

  register char *yy_cp;

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;



  yy_current_state = yyg->yy_start;



  for ( yy_cp = yyg->yytext_ptr + YY_MORE_ADJ; yy_cp < yyg->yy_c_buf_p; ++yy_cp )

    {

    register YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);

    if ( yy_accept[yy_current_state] )

      {

      yyg->yy_last_accepting_state = yy_current_state;

      yyg->yy_last_accepting_cpos = yy_cp;

      }

    while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )

      {

      yy_current_state = (int) yy_def[yy_current_state];

      if ( yy_current_state >= 20 )

        yy_c = yy_meta[(unsigned int) yy_c];

      }

    yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];

    }



  return yy_current_state;

}



/* yy_try_NUL_trans - try to make a transition on the NUL character

 *

 * synopsis

 *  next_state = yy_try_NUL_trans( current_state );

 */

    static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state , yyscan_t yyscanner)

{

  register int yy_is_jam;

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

  register char *yy_cp = yyg->yy_c_buf_p;



  register YY_CHAR yy_c = 1;

  if ( yy_accept[yy_current_state] )

    {

    yyg->yy_last_accepting_state = yy_current_state;

    yyg->yy_last_accepting_cpos = yy_cp;

    }

  while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )

    {

    yy_current_state = (int) yy_def[yy_current_state];

    if ( yy_current_state >= 20 )

      yy_c = yy_meta[(unsigned int) yy_c];

    }

  yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];

  yy_is_jam = (yy_current_state == 19);



  return yy_is_jam ? 0 : yy_current_state;

}



#ifndef YY_NO_INPUT

