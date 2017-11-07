static void 
mutt_make_reference_headers (ENVELOPE *curenv, ENVELOPE *env, CONTEXT *ctx)
{
  env->references = NULL;
  env->in_reply_to = NULL;
  
  if (!curenv)
  {
    HEADER *h;
    LIST **p = NULL, **q = NULL;
    int i;
    
    for(i = 0; i < ctx->vcount; i++)
    {
      h = ctx->hdrs[ctx->v2r[i]];
      if (h->tagged)
	mutt_add_to_reference_headers (env, h->env, &p, &q);
    }
  }
  else
    mutt_add_to_reference_headers (env, curenv, NULL, NULL);

  /* if there's more than entry in In-Reply-To (i.e. message has
     multiple parents), don't generate a References: header as it's
     discouraged by RfC2822, sect. 3.6.4 */
  if (ctx->tagged > 0 && env->in_reply_to && env->in_reply_to->next)
    mutt_free_list (&env->references);
}