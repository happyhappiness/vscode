BODY *mutt_make_multipart (BODY *b)
{
  BODY *new;

  new = mutt_new_body ();
  new->type = TYPEMULTIPART;
  new->subtype = safe_strdup ("mixed");
  new->encoding = get_toplevel_encoding (b);
  mutt_generate_boundary (&new->parameter);
  new->use_disp = 0;  
  new->disposition = DISPINLINE;
  new->parts = b;

  return new;
}