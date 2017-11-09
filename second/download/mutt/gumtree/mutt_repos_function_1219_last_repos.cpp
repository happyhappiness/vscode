static char *apply_subject_mods (ENVELOPE *env)
{
  if (env == NULL)
    return NULL;

  if (SubjectRxList == NULL)
    return env->subject;

  if (env->subject == NULL || *env->subject == '\0')
    return env->disp_subj = NULL;

  env->disp_subj = mutt_apply_replace(NULL, 0, env->subject, SubjectRxList);
  return env->disp_subj;
}