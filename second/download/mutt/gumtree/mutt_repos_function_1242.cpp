BODY *mutt_make_multipart (BODY *b)
{
  BODY *new;

  new = mutt_new_body ();
  new->type = TYPEMULTIPART;
  new->subtype = safe_strdup ("mixed");
  new->encoding = get_toplevel_encoding (b);
  do
  {
    mutt_generate_boundary (&new->parameter);
    if (mutt_check_boundary (mutt_get_parameter ("boundary", new->parameter),
			     b))
      mutt_delete_parameter ("boundary", &new->parameter);
  }
  while (!mutt_get_parameter ("boundary", new->parameter));
  new->use_disp = 0;
  new->disposition = DISPINLINE;
  new->parts = b;

  return new;
}