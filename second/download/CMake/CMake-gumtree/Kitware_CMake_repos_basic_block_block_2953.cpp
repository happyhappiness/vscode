(i = l; i <= r; i++) {
               cc1 = eclass[fmap[i]];
               if (cc != cc1) { SET_BH(i); cc = cc1; };
            }