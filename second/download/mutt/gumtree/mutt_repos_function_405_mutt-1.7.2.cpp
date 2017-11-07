static void smime_entry (char *s, size_t l, MUTTMENU * menu, int num)
{
  smime_key_t **Table = (smime_key_t **) menu->data;
  smime_key_t *this = Table[num];
  char* truststate;
  switch(this->trust) {
    case 't':
      truststate = N_("Trusted   ");
      break;
    case 'v':
      truststate = N_("Verified  ");
      break;
    case 'u':
      truststate = N_("Unverified");
      break;
    case 'e':
      truststate = N_("Expired   ");
      break;
    case 'r':
      truststate = N_("Revoked   ");
      break;
    case 'i':
      truststate = N_("Invalid   ");
      break;
    default:
      truststate = N_("Unknown   ");
  }
  snprintf(s, l, " 0x%s %s %s %-35.35s %s", this->hash,
           smime_key_flags (this->flags), truststate, this->email, this->label);
}