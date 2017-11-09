static int strict_cmp_bodies (const BODY *b1, const BODY *b2)
{
  if (b1->type != b2->type ||
      b1->encoding != b2->encoding ||
      mutt_strcmp (b1->subtype, b2->subtype) ||
      mutt_strcmp (b1->description, b2->description) ||
      !strict_cmp_parameters (b1->parameter, b2->parameter) ||
      b1->length != b2->length)
    return (0);
  return (1);
}