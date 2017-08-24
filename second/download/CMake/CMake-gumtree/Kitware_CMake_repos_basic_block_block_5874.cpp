f(check->ntlm.state != NTLMSTATE_NONE) {
          /* Connection is using NTLM auth but we don't want NTLM */
          continue;
        }