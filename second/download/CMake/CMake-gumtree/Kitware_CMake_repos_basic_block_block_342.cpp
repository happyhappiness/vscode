{
      FIELD *last_field, *field_on_page;

      werase(Get_Form_Window(form));
      form->curpage = page;
      last_field = field_on_page = form->field[form->page[page].smin];
      do
        {
          if (field_on_page->opts & O_VISIBLE)
            if ((res=Display_Field(field_on_page))!=E_OK) 
              return(res);
          field_on_page = field_on_page->snext;
        } while(field_on_page != last_field);

      if (field)
        res = _nc_Set_Current_Field(form,field);
      else
        /* N.B.: we don't encapsulate this by Inter_Field_Navigation(),
           because this is already executed in a page navigation
           context that contains field navigation 
         */
        res = FN_First_Field(form);
    }