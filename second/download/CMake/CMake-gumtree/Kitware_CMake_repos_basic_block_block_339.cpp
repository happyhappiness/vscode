(field_on_page->opts & O_VISIBLE)
            if ((res=Display_Field(field_on_page))!=E_OK) 
              return(res);