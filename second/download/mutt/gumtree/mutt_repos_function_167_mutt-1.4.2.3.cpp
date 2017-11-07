int mbox_strict_cmp_headers (const HEADER *h1, const HEADER *h2)
{
  if (h1 && h2)
  {
    if (h1->received != h2->received ||
	h1->date_sent != h2->date_sent ||
	h1->content->length != h2->content->length ||
	h1->lines != h2->lines ||
	h1->zhours != h2->zhours ||
	h1->zminutes != h2->zminutes ||
	h1->zoccident != h2->zoccident ||
	h1->mime != h2->mime ||
	!strict_cmp_envelopes (h1->env, h2->env) ||
	!strict_cmp_bodies (h1->content, h2->content))
      return (0);
    else
      return (1);
  }
  else
  {
    if (h1 == NULL && h2 == NULL)
      return (1);
    else
      return (0);
  }
}