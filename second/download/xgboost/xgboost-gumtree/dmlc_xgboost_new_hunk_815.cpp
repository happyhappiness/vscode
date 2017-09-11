        *   given the configuation
        * \author Kailong Chen: chenkl198812@gmail.com, Tianqi Chen: tianqi.chen@gmail.com
        */
        class RegBoostTask{
        public:
            inline int Run(int argc, char *argv[]){
                if (argc < 2){
                    printf("Usage: <config>\n");
                    return 0;
                }
                utils::ConfigIterator itr(argv[1]);
                while (itr.Next()){
                    this->SetParam(itr.name(), itr.val());
                }
                for (int i = 2; i < argc; i++){
                    char name[256], val[256];
                    if (sscanf(argv[i], "%[^=]=%s", name, val) == 2){
                        this->SetParam(name, val);
                    }
                }
                this->InitData();
                this->InitLearner();
                if (task == "dump"){
                    this->TaskDump();
                    return 0;
                }
                if (task == "interact"){
                    this->TaskInteractive(); return 0;
                }
                if (task == "dumppath"){
                    this->TaskDumpPath(); return 0;
                }
                if (task == "eval"){
                    this->TaskEval(); return 0;
                }
                if (task == "pred"){
                    this->TaskPred();
                }
                else{
                    this->TaskTrain();
                }
                return 0;
            }
            inline void SetParam(const char *name, const char *val){
                if (!strcmp("silent", name))       silent = atoi(val);
                if (!strcmp("use_buffer", name))   use_buffer = atoi(val);
                if (!strcmp("seed", name))         random::Seed(atoi(val));
                if (!strcmp("num_round", name))    num_round = atoi(val);
                if (!strcmp("save_period", name))  save_period = atoi(val);
                if (!strcmp("task", name))         task = val;
                if (!strcmp("data", name))        train_path = val;
                if (!strcmp("test:data", name))   test_path = val;
                if (!strcmp("model_in", name))    model_in = val;
                if (!strcmp("model_out", name))   model_out = val;
                if (!strcmp("model_dir", name))    model_dir_path = val;
                if (!strcmp("fmap", name))        name_fmap = val;
                if (!strcmp("name_dump", name))   name_dump = val;
                if (!strcmp("name_dumppath", name))   name_dumppath = val;
                if (!strcmp("name_pred", name))   name_pred = val;
                if (!strcmp("dump_stats", name))   dump_model_stats = atoi(val);
                if (!strcmp("interact:action", name))  interact_action = val;
                if (!strncmp("batch:", name, 6)){
                    cfg_batch.PushBack(name + 6, val);
                }
                if (!strncmp("eval[", name, 5)) {
                    char evname[256];
                    utils::Assert(sscanf(name, "eval[%[^]]", evname) == 1, "must specify evaluation name for display");
                    eval_data_names.push_back(std::string(evname));
                    eval_data_paths.push_back(std::string(val));
                }
                cfg.PushBack(name, val);
            }
        public:
            RegBoostTask(void){
                // default parameters
                silent = 0;
                use_buffer = 1;
                num_round = 10;
                save_period = 0;
                dump_model_stats = 0;
                task = "train";
                model_in = "NULL";
                model_out = "NULL";
                name_fmap = "NULL";
