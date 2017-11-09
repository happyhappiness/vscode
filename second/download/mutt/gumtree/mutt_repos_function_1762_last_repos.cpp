static void clear_subject_mods (void)
{
  int i;
  if (Context && Context->msgcount) 
  {
    for (i = 0; i < Context->msgcount; i++)
      FREE(&Context->hdrs[i]->env->disp_subj);
  }
}