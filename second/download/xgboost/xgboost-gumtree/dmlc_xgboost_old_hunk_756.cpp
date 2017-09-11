                }

                if (batch_action == 0){
                    learner.UpdateInteract(interact_action);
                }
                utils::Assert(model_out != "NULL", "interactive mode must specify model_out");
                this->SaveModel(model_out.c_str());
