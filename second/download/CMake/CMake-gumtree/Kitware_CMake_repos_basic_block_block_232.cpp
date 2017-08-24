(Has_Invisible_Parts(field))
        {
          werase(form->w);
          Buffer_To_Window(field,form->w);
        } 
      else 
        {
          if (Justification_Allowed(field))
            {
              werase(form->w);
              Undo_Justification(field,form->w);
              wsyncup(form->w);
            }
        }