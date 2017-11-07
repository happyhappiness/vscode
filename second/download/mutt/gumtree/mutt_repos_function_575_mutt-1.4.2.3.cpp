void rfc1524_free_entry(rfc1524_entry **entry)
{
  rfc1524_entry *p = *entry;

  safe_free((void **)&p->command);
  safe_free((void **)&p->testcommand);
  safe_free((void **)&p->composecommand);
  safe_free((void **)&p->composetypecommand);
  safe_free((void **)&p->editcommand);
  safe_free((void **)&p->printcommand);
  safe_free((void **)&p->nametemplate);
  safe_free((void **)entry);
}