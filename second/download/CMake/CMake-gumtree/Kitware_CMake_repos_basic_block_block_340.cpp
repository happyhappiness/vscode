do
        {
          if (field_on_page->opts & O_VISIBLE)
            if ((res=Display_Field(field_on_page))!=E_OK) 
              return(res);
          field_on_page = field_on_page->snext;
        } while(field_on_page != last_field);