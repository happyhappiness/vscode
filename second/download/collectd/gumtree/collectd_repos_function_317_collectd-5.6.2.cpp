static int add_ignorelist(const char *dev, const char *type, const char *inst) {
  ir_ignorelist_t *entry;

  entry = calloc(1, sizeof(*entry));
  if (entry == NULL)
    return (-1);

  if (strcasecmp(dev, "All") != 0) {
    entry->device = strdup(dev);
    if (entry->device == NULL) {
      sfree(entry);
      return (-1);
    }
  }

  entry->type = strdup(type);
  if (entry->type == NULL) {
    sfree(entry->device);
    sfree(entry);
    return (-1);
  }

  if (inst != NULL) {
    entry->inst = strdup(inst);
    if (entry->inst == NULL) {
      sfree(entry->type);
      sfree(entry->device);
      sfree(entry);
      return (-1);
    }
  }

  entry->next = ir_ignorelist_head;
  ir_ignorelist_head = entry;

  return (0);
}