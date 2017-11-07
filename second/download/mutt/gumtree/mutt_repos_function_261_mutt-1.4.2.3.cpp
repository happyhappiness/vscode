struct binding_t *km_get_table (int menu)
{
  switch (menu)
  {
    case MENU_MAIN:
      return OpMain;
    case MENU_GENERIC:
      return OpGeneric;
    case MENU_COMPOSE:
      return OpCompose;
    case MENU_PAGER:
      return OpPager;
    case MENU_POST:
      return OpPost;
    case MENU_FOLDER:
      return OpBrowser;
    case MENU_ALIAS:
      return OpAlias;
    case MENU_ATTACH:
      return OpAttach;
    case MENU_EDITOR:
      return OpEditor;
    case MENU_QUERY:
      return OpQuery;



#ifdef HAVE_PGP
    case MENU_PGP:
      return OpPgp;
#endif


#ifdef MIXMASTER
    case MENU_MIX:
      return OpMix;
#endif

  }
  return NULL;
}