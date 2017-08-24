{
          if(c != CURL_IAC) {
            /*
             * This is an error.  We only expect to get "IAC IAC" or "IAC SE".
             * Several things may have happened.  An IAC was not doubled, the
             * IAC SE was left off, or another option got inserted into the
             * suboption are all possibilities.  If we assume that the IAC was
             * not doubled, and really the IAC SE was left off, we could get
             * into an infinite loop here.  So, instead, we terminate the
             * suboption, and process the partial suboption if we can.
             */
            CURL_SB_ACCUM(tn, CURL_IAC);
            CURL_SB_ACCUM(tn, c);
            tn->subpointer -= 2;
            CURL_SB_TERM(tn);

            printoption(data, "In SUBOPTION processing, RCVD", CURL_IAC, c);
            suboption(conn);   /* handle sub-option */
            tn->telrcv_state = CURL_TS_IAC;
            goto process_iac;
          }
          CURL_SB_ACCUM(tn, c);
          tn->telrcv_state = CURL_TS_SB;
        }