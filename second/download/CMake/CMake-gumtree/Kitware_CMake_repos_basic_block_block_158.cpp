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