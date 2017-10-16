{
  puts("Build-time engines:");
  if(!engines) {
    puts("  <none>");
    return;
  }
  for( ; engines; engines = engines->next)
    printf("  %s\n", engines->data);
}

/***************************************************************************
 *
 * formparse()
