static void mix_add_entry (REMAILER ***type2_list, REMAILER *entry,
			   size_t *slots, size_t *used)
{
  if (*used == *slots)
  {
    *slots += 5;
    safe_realloc (type2_list, sizeof (REMAILER *) * (*slots));
  }
  
  (*type2_list)[(*used)++] = entry;
  if (entry) entry->num = *used;
}