do
    {
      field_on_page = field_on_page->sprev;
      if (Field_Is_Selectable(field_on_page))
        break;
    } while(field_on_page!=field);