      rar->range_dec.Stream = &rar->bytein;

      __archive_ppmd7_functions.Ppmd7_Construct(&rar->ppmd7_context);



      if (!__archive_ppmd7_functions.Ppmd7_Alloc(&rar->ppmd7_context,

        rar->dictionary_size, &g_szalloc))

      {

