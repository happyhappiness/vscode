{
      bool single_line_field = Single_Line_Field(field);
      int old_buflen = Buffer_Length(field);
      int new_buflen;
      int old_dcols = field->dcols;
      int old_drows = field->drows;
      char *oldbuf  = field->buf;
      char *newbuf;

      int growth;
      FORM *form = field->form;
      bool need_visual_update = ((form != (FORM *)0)      &&
                                 (form->status & _POSTED) &&
                                 (form->current==field));
      
      if (need_visual_update)
        Synchronize_Buffer(form);
      
      if (single_line_field)
        {
          growth = field->cols * amount;
          if (field->maxgrow)
            growth = Minimum(field->maxgrow - field->dcols,growth);
          field->dcols += growth;
          if (field->dcols == field->maxgrow)
            field->status &= ~_MAY_GROW;
        }
      else
        {
          growth = (field->rows + field->nrow) * amount;
          if (field->maxgrow)
            growth = Minimum(field->maxgrow - field->drows,growth);
          field->drows += growth;
          if (field->drows == field->maxgrow)
            field->status &= ~_MAY_GROW;
        }
      /* drows, dcols changed, so we get really the new buffer length */
      new_buflen = Buffer_Length(field);
      newbuf=(char *)malloc((size_t)Total_Buffer_Size(field));
      if (!newbuf)
        { /* restore to previous state */
          field->dcols = old_dcols;
          field->drows = old_drows;
          if (( single_line_field && (field->dcols!=field->maxgrow)) ||
              (!single_line_field && (field->drows!=field->maxgrow)))
            field->status |= _MAY_GROW;
          return FALSE;
        }
      else
        { /* Copy all the buffers. This is the reason why we can't
             just use realloc().
             */
          int i;
          char *old_bp;
          char *new_bp;
          
          field->buf = newbuf;
          for(i=0;i<=field->nbuf;i++)
            {
              new_bp = Address_Of_Nth_Buffer(field,i);
              old_bp = oldbuf + i*(1+old_buflen);
              memcpy(new_bp,old_bp,(size_t)old_buflen);
              if (new_buflen > old_buflen)
                memset(new_bp + old_buflen,C_BLANK,
                       (size_t)(new_buflen - old_buflen));
              *(new_bp + new_buflen) = '\0';
            }

          if (need_visual_update)
            {         
              WINDOW *new_window = newpad(field->drows,field->dcols);
              if (!new_window)
                { /* restore old state */
                  field->dcols = old_dcols;
                  field->drows = old_drows;
                  field->buf   = oldbuf;
                  if (( single_line_field              && 
                        (field->dcols!=field->maxgrow)) ||
                      (!single_line_field              && 
                       (field->drows!=field->maxgrow)))
                    field->status |= _MAY_GROW;
                  free( newbuf );
                  return FALSE;
                }
              assert(form!=(FORM *)0);
              delwin(form->w);
              form->w = new_window;
              Set_Field_Window_Attributes(field,form->w);
              werase(form->w);
              Buffer_To_Window(field,form->w);
              untouchwin(form->w);
              wmove(form->w,form->currow,form->curcol);
            }

          free(oldbuf);
          /* reflect changes in linked fields */
          if (field != field->link)
            {
              FIELD *linked_field;
              for(linked_field = field->link;
                  linked_field!= field;
                  linked_field = linked_field->link)
                {
                  linked_field->buf   = field->buf;
                  linked_field->drows = field->drows;
                  linked_field->dcols = field->dcols;
                }
            }
          result = TRUE;
        }       
    }