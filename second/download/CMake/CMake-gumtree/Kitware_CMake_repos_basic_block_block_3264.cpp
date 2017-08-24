{
      Cell* aa2 = aa->link;
      if (aa->name != NULL) free(aa->name);
      free(aa);
      aa = aa2;
   }