void mutt_init_history(void)
{
  history_class_t hclass;
  
  if (HistSize == OldSize)
    return;
  
  for(hclass = HC_FIRST; hclass < HC_LAST; hclass++)
    init_history(&History[hclass]);

  OldSize = HistSize;
}