void mix_make_chain (LIST **chainp)
{
  LIST *p;
  MIXCHAIN *chain;
  int c_cur = 0, c_old = 0;
  short c_redraw = 1;
  
  REMAILER **type2_list = NULL;
  size_t ttll = 0;
  
  struct coord *coords = NULL;
  
  MUTTMENU *menu;
  char helpstr[LONG_STRING];
  short loop = 1;
  int op;
  
  int i, j;
  char *t;

  if (!(type2_list = mix_type2_list (&ttll)))
  {
    mutt_error _("Can't get mixmaster's type2.list!");
    return;
  }

  chain = safe_calloc (sizeof (MIXCHAIN), 1);
  for (p = *chainp; p; p = p->next)
    mix_chain_add (chain, (char *) p->data, type2_list);

  mutt_free_list (chainp);
  
  /* safety check */
  for (i = 0; i < chain->cl; i++)
  {
    if (chain->ch[i] >= ttll)
      chain->ch[i] = 0;
  }
  
  mix_screen_coordinates (type2_list, &coords, chain, 0);
  
  menu = mutt_new_menu (MENU_MIX);
  menu->max = ttll;
  menu->make_entry = mix_entry;
  menu->tag = NULL;
  menu->title = _("Select a remailer chain.");
  menu->data = type2_list;
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_MIX, RemailerHelp);
  menu->pagelen = MIX_VOFFSET - 1;
  mutt_push_current_menu (menu);
  
  while (loop) 
  {
    if (menu->pagelen != MIX_VOFFSET - 1)
    {
      menu->pagelen = MIX_VOFFSET - 1;
      menu->redraw = REDRAW_FULL;
    }
    
    if (c_redraw)
    {
      mix_redraw_head (chain);
      mix_redraw_chain (type2_list, coords, chain, c_cur);
      c_redraw = 0;
    }
    else if (c_cur != c_old)
    {
      mix_redraw_ce (type2_list, coords, chain, c_old, 0);
      mix_redraw_ce (type2_list, coords, chain, c_cur, 1);
    }
    
    c_old = c_cur;
    
    switch ((op = mutt_menuLoop (menu)))
    {
      case OP_REDRAW:
      {
	menu_redraw_status (menu);
	mix_redraw_head (chain);
	mix_screen_coordinates (type2_list, &coords, chain, 0);
	mix_redraw_chain (type2_list, coords, chain, c_cur);
	menu->pagelen = MIX_VOFFSET - 1;
	break;
      }
      
      case OP_EXIT:
      {
	chain->cl = 0;
	loop = 0;
	break;
      }

      case OP_MIX_USE:
      {
	if (!chain->cl)
	{
	  chain->cl++;
	  chain->ch[0] = menu->current;
	  mix_screen_coordinates (type2_list, &coords, chain, c_cur);
	  c_redraw = 1;
	}
	
	if (chain->cl && chain->ch[chain->cl - 1] && 
	    (type2_list[chain->ch[chain->cl-1]]->caps & MIX_CAP_MIDDLEMAN))
	{
	  mutt_error ( _("Error: %s can't be used as the final remailer of a chain."),
		    type2_list[chain->ch[chain->cl - 1]]->shortname);
	}
	else
	{
	  loop = 0;
	}
	break;
      }

      case OP_GENERIC_SELECT_ENTRY:
      case OP_MIX_APPEND:
      {
	if (chain->cl < MAXMIXES && c_cur < chain->cl)
	  c_cur++;
      }
      /* fallthrough */
      case OP_MIX_INSERT:
      {
	if (chain->cl < MAXMIXES)
	{
	  chain->cl++;
	  for (i = chain->cl - 1; i > c_cur; i--)
	    chain->ch[i] = chain->ch[i-1];
	  
	  chain->ch[c_cur] = menu->current;
	  mix_screen_coordinates (type2_list, &coords, chain, c_cur);
	  c_redraw = 1;
	}
	else
	  mutt_error ( _("Mixmaster chains are limited to %d elements."),
		    MAXMIXES);
	
	break;
      }
      
      case OP_MIX_DELETE:
      {
	if (chain->cl)
	{
	  chain->cl--;
	  
	  for (i = c_cur; i < chain->cl; i++)
	    chain->ch[i] = chain->ch[i+1];

	  if (c_cur == chain->cl && c_cur)
	    c_cur--;
	  
	  mix_screen_coordinates (type2_list, &coords, chain, c_cur);
	  c_redraw = 1;
	}
	else
	{
	  mutt_error _("The remailer chain is already empty.");
	}
	break;
      }
      
      case OP_MIX_CHAIN_PREV:
      {
	if (c_cur) 
	  c_cur--;
	else
	  mutt_error _("You already have the first chain element selected.");
	
	break;
      }
      
      case OP_MIX_CHAIN_NEXT:
      {
	if (chain->cl && c_cur < chain->cl - 1)
	  c_cur++;
	else
	  mutt_error _("You already have the last chain element selected.");
	
	break;
      }
    }
  }
  
  mutt_pop_current_menu (menu);
  mutt_menuDestroy (&menu);

  /* construct the remailer list */
  
  if (chain->cl)
  {
    for (i = 0; i < chain->cl; i++)
    {
      if ((j = chain->ch[i]))
	t = type2_list[j]->shortname;
      else
	t = "*";
      
      *chainp = mutt_add_list (*chainp, t);
    }
  }
  
  mix_free_type2_list (&type2_list);
  FREE (&coords);
  FREE (&chain);
}