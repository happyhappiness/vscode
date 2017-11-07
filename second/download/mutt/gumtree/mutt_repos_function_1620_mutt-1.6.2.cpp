void mutt_free_opts (void)
{
  int i;

  for (i = 0; MuttVars[i].option; i++)
    mutt_free_opt (MuttVars + i);

  mutt_free_rx_list (&Alternates);
  mutt_free_rx_list (&UnAlternates);
  mutt_free_rx_list (&MailLists);
  mutt_free_rx_list (&UnMailLists);
  mutt_free_rx_list (&SubscribedLists);
  mutt_free_rx_list (&UnSubscribedLists);
  mutt_free_rx_list (&NoSpamList);
}