static void mix_screen_coordinates (REMAILER **type2_list,
				    struct coord **coordsp,
				    MIXCHAIN *chain,
				    int i)
{
  short c, r, oc;
  struct coord *coords;

  if (!chain->cl)
    return;
  
  safe_realloc (coordsp, sizeof (struct coord) * chain->cl);
  
  coords = *coordsp;
  
  if (i)
  {
    c = coords[i-1].c + strlen (type2_list[chain->ch[i-1]]->shortname) + 2;
    r = coords[i-1].r;
  }
  else
  {
    r = MIX_VOFFSET;
    c = MIX_HOFFSET;
  }
    
  
  for (; i < chain->cl; i++)
  {
    oc = c;
    c += strlen (type2_list[chain->ch[i]]->shortname) + 2;

    if (c  >= MuttIndexWindow->cols)
    {
      oc = c = MIX_HOFFSET;
      r++;
    }
    
    coords[i].c = oc;
    coords[i].r = r;
    
  }
  
}