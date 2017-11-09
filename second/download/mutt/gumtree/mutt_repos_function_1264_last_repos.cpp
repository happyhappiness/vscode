void mutt_break_thread (HEADER *hdr)
{
  mutt_free_list (&hdr->env->in_reply_to);
  mutt_free_list (&hdr->env->references);
  hdr->env->irt_changed = hdr->env->refs_changed = hdr->changed = 1;

  clean_references (hdr->thread, hdr->thread->child);
}