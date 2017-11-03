void rfc1524_free_entry(rfc1524_entry **entry)
{
  rfc1524_entry *p = *entry;

  FREE (&p->command);
  FREE (&p->testcommand);
  FREE (&p->composecommand);
  FREE (&p->composetypecommand);
  FREE (&p->editcommand);
  FREE (&p->printcommand);
  FREE (&p->nametemplate);
  FREE (entry);		/* __FREE_CHECKED__ */
}