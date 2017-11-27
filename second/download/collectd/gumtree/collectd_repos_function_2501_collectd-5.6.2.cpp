void cf_unregister(const char *type) {
  for (cf_callback_t *prev = NULL, *this = first_callback; this != NULL;
       prev = this, this = this->next)
    if (strcasecmp(this->type, type) == 0) {
      if (prev == NULL)
        first_callback = this->next;
      else
        prev->next = this->next;

      free(this);
      break;
    }
}