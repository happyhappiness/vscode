               break;
           }
 
           snprintf (buf, sizeof (buf), _("%s Do you really want to use the key?"),
                     _(s));
 
-          if (mutt_yesorno (buf, M_NO) != M_YES)
+          if (mutt_yesorno (buf, MUTT_NO) != MUTT_YES)
           {
             mutt_clear_error ();
             break;
           }
         }
 
