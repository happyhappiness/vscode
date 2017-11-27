static int email_read(void) {
  double score_old;
  int score_count_old;

  if (disabled)
    return (-1);

  /* email count */
  pthread_mutex_lock(&count_mutex);

  copy_type_list(&list_count, &list_count_copy);

  pthread_mutex_unlock(&count_mutex);

  for (type_t *ptr = list_count_copy.head; NULL != ptr; ptr = ptr->next) {
    email_submit("email_count", ptr->name, ptr->value);
  }

  /* email size */
  pthread_mutex_lock(&size_mutex);

  copy_type_list(&list_size, &list_size_copy);

  pthread_mutex_unlock(&size_mutex);

  for (type_t *ptr = list_size_copy.head; NULL != ptr; ptr = ptr->next) {
    email_submit("email_size", ptr->name, ptr->value);
  }

  /* spam score */
  pthread_mutex_lock(&score_mutex);

  score_old = score;
  score_count_old = score_count;
  score = 0.0;
  score_count = 0;

  pthread_mutex_unlock(&score_mutex);

  if (score_count_old > 0)
    email_submit("spam_score", "", score_old);

  /* spam checks */
  pthread_mutex_lock(&check_mutex);

  copy_type_list(&list_check, &list_check_copy);

  pthread_mutex_unlock(&check_mutex);

  for (type_t *ptr = list_check_copy.head; NULL != ptr; ptr = ptr->next)
    email_submit("spam_check", ptr->name, ptr->value);

  return (0);
}