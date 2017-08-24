f(!strncmp(from, "PASS ", 5) || !strncmp(from, "ACCT ", 5))
      prot_level = PROT_PRIVATE;
    else
      prot_level = conn->command_prot