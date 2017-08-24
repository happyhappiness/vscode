{
          FIELD **field = &form->field[proposed->index];
          FIELD **first = &form->field[form->page[form->curpage].pmin];

          do
            {
              field = (field==last_on_page) ? first : field + 1;
              if (((*field)->opts & O_VISIBLE))
                break;
            } while(proposed!=(*field));
          
          proposed = *field;

          if ((proposed == *last_on_page) && !(proposed->opts&O_VISIBLE))
            { /* This means, there is also no visible field on the page.
                 So we propose the first one and hope the very best... 
                 Some very clever user has designed a readonly and invisible
                 page on this form.
               */
              proposed = *first;
            }
        }