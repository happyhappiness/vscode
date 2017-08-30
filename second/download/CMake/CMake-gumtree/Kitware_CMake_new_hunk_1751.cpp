        case HOSTVALID:

          /* we are now parsing sub-keywords concerning "our" host */

          if(state_login) {

            if (specific_login) {

              state_our_login = strequal(login, tok);

            }else{

              strncpy(login, tok, LOGINSIZE-1);

#ifdef _NETRC_DEBUG

              printf("LOGIN: %s\n", login);

#endif

            }

            state_login=0;

          }

          else if(state_password) {

            if (state_our_login || !specific_login) {

              strncpy(password, tok, PASSWORDSIZE-1);

#ifdef _NETRC_DEBUG

              printf("PASSWORD: %s\n", password);

#endif

            }

            state_password=0;

          }

          else if(strequal("login", tok))

