bool RegularExpression::find(const char* string)
{
  const char* s;

  this->searchstring = string;

  if (!this->program) {
    return false;
  }

  // Check validity of program.
  if (UCHARAT(this->program) != MAGIC) {
    // RAISE Error, SYM(RegularExpression), SYM(Internal_Error),
    printf(
      "RegularExpression::find(): Compiled regular expression corrupted.\n");
    return 0;
  }

  // If there is a "must appear" string, look for it.
  if (this->regmust != 0) {
    s = string;
    while ((s = strchr(s, this->regmust[0])) != 0) {
      if (strncmp(s, this->regmust, this->regmlen) == 0)
        break; // Found it.
      s++;
    }
    if (s == 0) // Not present.
      return (0);
  }

  // Mark beginning of line for ^ .
  regbol = string;

  // Simplest case:  anchored match need be tried only once.
  if (this->reganch)
    return (regtry(string, this->startp, this->endp, this->program) != 0);

  // Messy cases:  unanchored match.
  s = string;
  if (this->regstart != '\0')
    // We know what char it must start with.
    while ((s = strchr(s, this->regstart)) != 0) {
      if (regtry(s, this->startp, this->endp, this->program))
        return (1);
      s++;
    }
  else
    // We don't -- general case.
    do {
      if (regtry(s, this->startp, this->endp, this->program))
        return (1);
    } while (*s++ != '\0');

  // Failure.
  return (0);
}