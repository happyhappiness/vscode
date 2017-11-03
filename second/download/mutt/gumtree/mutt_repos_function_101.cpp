static int is_reply (HEADER *reply, HEADER *orig)
{
  return mutt_find_list (orig->env->references, reply->env->message_id) ||
         mutt_find_list (orig->env->in_reply_to, reply->env->message_id);
}