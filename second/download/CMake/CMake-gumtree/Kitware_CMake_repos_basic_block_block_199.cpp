(field->opts & O_PUBLIC)
        {
          if (Justification_Allowed(field))
            Perform_Justification(field,win);
          else
            Buffer_To_Window(field,win);
        }