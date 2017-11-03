static int print_attach_list (LIST *lp, char op, char *name)
{
  while (lp) {
    printf("attachments %c%s %s/%s\n", op, name,
           ((ATTACH_MATCH *)lp->data)->major,
           ((ATTACH_MATCH *)lp->data)->minor);
    lp = lp->next;
  }

  return 0;
}