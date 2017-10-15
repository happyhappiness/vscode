    fflush (stdout);
    printf("\nCurrent attachments settings:\n\n");
    print_attach_list(AttachAllow,   '+', "A");
    print_attach_list(AttachExclude, '-', "A");
    print_attach_list(InlineAllow,   '+', "I");
    print_attach_list(InlineExclude, '-', "I");
    mutt_any_key_to_continue (NULL);
    return 0;
  }

  if (op != '+' && op != '-') {
    op = '+';
