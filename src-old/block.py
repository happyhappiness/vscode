#-*-coding: utf-8 -*-
import json
import csv
import numpy as np
from scipy.spatial.distance import pdist
from joern.all import JoernSteps
from itertools import islice
import my_constant
import myUtil

class Block:
    # joern instance shared by all objects
    joern_instance = None
    # node type dictionary between type and index
    node_index_dic = None

    def __init__(self, log_id = None):
        if Block.joern_instance is None:
            initialize_joern()
        self.log_id = log_id
        self.identity = None
        self.file_name = None
        self.log_loc = None
        self.condition_feature = None
        self.statement_feature = None
        self.condition_vector = None
        self.statement_vector = None
        self.vector = None

    def set_log_id(self, log_id):
        self.log_id = log_id

    def get_block_identity(self):
        ident_query = "_().logToLogBlock(" + str(self.log_id) + ")"
        ident = Block.joern_instance.runGremlinQuery(ident_query)[0]
        self.log_loc = ident[1]
        file_name_query = "_().getFileInfo(" + str(ident[2]) + ")"
        self.file_name = Block.joern_instance.runGremlinQuery(file_name_query)[0]
        if not ident[3] == "CFGEntryNode":
            flag_query = "_().logToLogBlockFlag(" + str(self.log_id) + ")"
            flag = Block.joern_instance.runGremlinQuery(flag_query)[0]
        else:
            flag = ''
        self.identity = (ident[0], flag)

    def get_block_feature(self):
        feature_query = "_().getBlockCondition(" + str(self.identity[0]) + ")"
        feature = Block.joern_instance.runGremlinQuery(feature_query)
        self.condition_feature = feature
        feature_query = "_().getBlockStatements(" + str(self.identity[0]) +\
                                                 ",'" + self.identity[1] + "')"
        feature = Block.joern_instance.runGremlinQuery(feature_query)
        self.statement_feature = feature

    def get_block_vector(self):
        self.condition_vector = self.__feature_to_vector(self.condition_feature)
        self.statement_vector = self.__feature_to_vector(self.statement_feature)
        self.vector = self.condition_vector + self.statement_vector

    def similarity_block(self, in_block):
        similairy = compute_similarity(self.vector, in_block.vector)
        return similairy

    # for repos analyze
    def get_info(self):
        info = []
        info.append(self.identity)
        info.append(self.file_name)
        info.append(self.log_loc)
        info.append(self.condition_feature)
        info.append(self.statement_feature)
        info.append(json.dumps(self.vector))
        return info

    # for old new block anlayze 
    def get_info_except_identity(self):
        info = []
        info.append(self.file_name)
        info.append(self.log_loc)
        info.append(self.condition_feature)
        info.append(self.statement_feature)
        info.append(self.vector)
        return info

    def __feature_to_vector(self, in_feature):
        out_vector = [0 for i in range(len(Block.node_index_dic))]
        # 1 dimension
        for node in in_feature:
            # print node
            out_vector[Block.node_index_dic[node]] += 1
        return out_vector
"""
@ param is to rebuild node dictionary or not, if not read from file
@ return nothing
@ callee ...
@ caller *
@ involve initialize Bolck.joern instance and node index dictionary
"""
def initialize_joern(is_rebuild = True):
    # initialization
    if Block.joern_instance is None:
        # initialization joern
        Block.joern_instance = JoernSteps()
        Block.joern_instance.addStepsDir("/opt/joern-code/query/")
        Block.joern_instance.setGraphDbURL("http://localhost:7474/db/data/")
        # connect to database
        Block.joern_instance.connectToDatabase()
    if is_rebuild:
        # get node type dictionary
        node_index_query = "_().getAllASTNodeType()"
        node_index = Block.joern_instance.runGremlinQuery(node_index_query)
        # store list
        node_dic_csv = file(my_constant.NODE_DICT_FILE_NAME, 'wb')
        node_dic_csv_writer = csv.writer(node_dic_csv)
        node_dic_csv_writer.writerow([json.dumps(node_index)])
        node_dic_csv.close()
    else:
        node_dic_csv = file(my_constant.NODE_DICT_FILE_NAME, 'rb')
        node_dic_records = csv.reader(node_dic_csv)
        # fisrt line first column
        for record in islice(node_dic_records, 0, 1):
            node_index = json.loads(record[0])
        node_dic_csv.close()
    # build dic from list
    Block.node_index_dic = myUtil.dict_from_list(node_index)


"""
@ param vactors to compare
@ return similarity
@ callee ...
@ caller *
@ involve compute cos similarity of two vectors
"""
def compute_similarity(in_vector1, in_vector2, method='braycurtis'):
    # multi = np.sum(np.multiply(in_vector1, in_vector2))
    # base = (np.linalg.norm(in_vector1) * np.linalg.norm(in_vector1))
    # if base > 0:
    #     similairy = float(multi) / base
    # else:
    #     return np.sum(in_vector1 + in_vector2) == 0
    # return similairy
    X = np.vstack([in_vector1, in_vector2])
    # standard distance
    distance = pdist(X, metric=method)
    similairty = 1 - distance
    return similairty

"""
@ param  file name, log location and block dictionary
@ return block objecr
@ callee ...
@ caller Block
@ involve create a block instance form its file name and log location \
        store into block ditionary
"""
def get_blocks(log_id, block_dic):
    block = Block(log_id)
    block.get_block_identity()
    # already saved identity
    if block_dic.has_key(block.identity):
        return block_dic, None
    else:
        block.get_block_feature()
        block.get_block_vector()
        block_dic[block.identity] = block
        return block_dic, block

"""
@ param  file name, log location and block dictionary
@ return block objecr
@ callee ...
@ caller Block
@ involve get log function call position and its corresponding log block
"""
def get_log_block():
    # initiation log info writer csv
    out_csv = file(my_constant.ANALYZE_REPOS_FILE_NAME, 'wb')
    out_csv_writer = csv.writer(out_csv)
    out_csv_writer.writerow(my_constant.ANALYZE_REPOS_TITLE)

    # get log statement id from log function name
    record_count = 0
    block_dict = {}
    # get name of log functions
    log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)
    for log_function in log_functions:
        log_call_query = '_().logToCallStatements("' + log_function +'")'
        log_calls = Block.joern_instance.runGremlinQuery(log_call_query)

        # deal with each call statement of log_function
        for log_call in log_calls:
            ########################################## log block  #################################
            block_dict, block = get_blocks(log_call[0][0], block_dict)
            if block is not None:
                out_csv_writer.writerow(block.get_info())
                record_count += 1
                if record_count%10 == 0:
                    print "now analyzing record: %d " %record_count

    out_csv.close()

"""
main function
"""
if __name__ == "__main__":

    initialize_joern()
    get_log_block()
