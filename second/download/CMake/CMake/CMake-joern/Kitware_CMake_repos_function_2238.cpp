static void CCONV FinalPass(void* inf, void* mf)
{
  cmLoadedCommandInfo* info = (cmLoadedCommandInfo*)inf;
  /* get our client data from initial pass */
  cmVTKWrapTclData* cdata = (cmVTKWrapTclData*)info->CAPI->GetClientData(info);
  if (strcmp(info->CAPI->GetDefinition(mf, "TEST_DEF"), "HOO") ||
      strcmp(cdata->LibraryName, "HOO")) {
    fprintf(stderr, "*** Failed LOADED COMMAND Final Pass\n");
  }
}