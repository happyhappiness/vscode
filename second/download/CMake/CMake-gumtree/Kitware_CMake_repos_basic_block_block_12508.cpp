(!rar->init_default_conversion) {
      rar->sconv_default =
          archive_string_default_conversion_for_read(
            &(a->archive));
      rar->init_default_conversion = 1;
    }