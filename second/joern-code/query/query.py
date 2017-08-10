from joern.all import JoernSteps

class Joern_api:
    joern_instance = None

    def __init__(self):
        # initialization
        if Joern_api.joern_instance is None:
            # initialization joern
            Joern_api.joern_instance = JoernSteps()
            Joern_api.joern_instance.addStepsDir("/usr/info/code/cpp/LogMonitor/LogMonitor/second/joern-code/query/")
            Joern_api.joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
            # connect to database
            Joern_api.joern_instance.connectToDatabase()
        self.log = None
        self.order = '5'
        self.control_dependence = None
        self.data_dependence = None
    
    def set_order(self, order):
        self.order = str(order)
    
    def set_log(self, file_name, log_loc):
        log_loc = str(log_loc + 1) + ':'
        base_query = '_().getLogByFileAndLoc("' + file_name + '","' + log_loc + '")'
        log_result = Joern_api.joern_instance.runGremlinQuery(base_query)
        if log_result is not None:
            log_result = log_result[0][0]
            print log_result
            self.log_id = str(log_result[0])
            self.log =  log_result[1]
        return self.log

    def get_control_dependence(self):
        cdg_query = '_().getControlDependence(' + self.log_id + ',' + self.order +')'
        cdg_list = Joern_api.joern_instance.runGremlinQuery(cdg_query)
        self.control_dependence = []
        if cdg_list is not None:
            cdg_list = cdg_list[0]
            # node_id, statement, label
            for condition in cdg_list:
                condition = condition[0]
                print condition
                node_id = str(condition[0])
                statement = condition[1]
                label_query = '_().getControlLabel(' + self.log_id + ',' + node_id +')'
                label = Joern_api.joern_instance.runGremlinQuery(label_query)
                if label is not None:
                    if len(label) == 0:
                        label = ''
                    else:
                        label = label[0]
                self.control_dependence.append([node_id, statement, label])
        print self.control_dependence
        return self.control_dependence

    def get_data_dependence(self):
        ddg_query = '_().getDefDependence(' + self.log_id + ')'
        ddg_list = Joern_api.joern_instance.runGremlinQuery(ddg_query)
        self.data_dependence = []
        if ddg_list is not None:
            # node_id, statement, var
            ddg_list = ddg_list[0]
            for data in ddg_list:
                var = data[0]
                node_id = data[1][0]
                statement = data[1][1]
                self.data_dependence.append([node_id, statement, var])
        print self.data_dependence
        return self.data_dependence

if __name__ is '__main__':
    loc = 20
    filename = 'mytest.c'
    joern_api = Joern_api()
    joern_api.set_log(filename, loc)
    joern_api.get_control_dependence()
    joern_api.get_data_dependence()

