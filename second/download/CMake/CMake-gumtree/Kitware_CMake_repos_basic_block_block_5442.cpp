f(smtp->rcpt) {
          /* Send the next command */
          result = smtp_perform_command(conn);
        }
        else
          /* End of DO phase */
          state(conn, SMTP_STOP)