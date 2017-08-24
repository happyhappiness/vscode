{
          if (!Field_Grown(field,1))
            {
            free(Space);
            return(E_SYSTEM_ERROR);
            }
          /* !!!Side-Effect : might be changed due to growth!!! */
          bp = Address_Of_Row_In_Buffer(field,row); 
        }