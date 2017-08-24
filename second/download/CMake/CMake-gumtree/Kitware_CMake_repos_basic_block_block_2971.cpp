(i = 0; i < 32; i++) { 
      SET_BH(nblock + 2*i);
      CLEAR_BH(nblock + 2*i + 1);
   }