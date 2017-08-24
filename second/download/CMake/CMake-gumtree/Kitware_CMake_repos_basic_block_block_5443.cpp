f(smtp->rcpt) {
        smtp->rcpt = smtp->rcpt->next;

        if(smtp->rcpt) {
          /* Send the next command */
          result = smtp_perform_command(conn);
        }
        else
          /* End of DO phase */
          state(conn, SMTP_STOP);
      }
      else
        /* End of DO phase */
        state(conn, SMTP_STOP)