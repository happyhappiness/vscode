#-*-coding: utf-8 -*-
import csv
import json
from itertools import islice
import block
from block import Block
import my_constant

"""
@ param  old and new log location and file name
@ return old block and new block object
@ caller analyze_record_to_block
@ callee nothing
@ involve from log loc and file -> block
"""
def get_old_new_block(old_loc, old_file, new_loc, new_file):

    # get old log id and new log id
    old_block = None
    new_block = None
    old_log_query = "_().getLogByFileAndLoc('" + old_file + "','"+ str(old_loc) + ":')"
    old_log_id = Block.joern_instance.runGremlinQuery(old_log_query)
    if not len(old_log_id) == 0:
        old_log_id = old_log_id[0][0][0]
        old_block = Block(old_log_id)

    new_log_query = "_().getLogByFileAndLoc('" + new_file + "','"+ str(new_loc) + ":')"
    new_log_id = Block.joern_instance.runGremlinQuery(new_log_query)
    if not len(new_log_id) == 0:
        new_log_id = new_log_id[0][0][0]
        new_block = Block(new_log_id)

    return old_block, new_block

"""
@ param fetch record and dictionary for old and new block
@ return dictionary modified and flag 
@ caller main
@ callee get_old_new_block
@ involve from log loc and file -> block record (log in same old_new_block aggregate together)
"""
def analyze_record_to_block(log_record, old_new_block_dict):

    old_loc = log_record[my_constant.FETCH_LOG_OLD_LOC]
    new_loc = log_record[my_constant.FETCH_LOG_NEW_LOC]
    old_file_name = log_record[my_constant.FETCH_LOG_OLD_FILE]
    new_file_name = log_record[my_constant.FETCH_LOG_NEW_FILE]

    # call get_old_new_block to get block from loc and file
    analyze_record = None
    old_block, new_block = get_old_new_block(old_loc, old_file_name, new_loc, new_file_name)
    if(old_block is not None) and (new_block is not None):
        old_block.get_block_identity()
        new_block.get_block_identity()
        identity = old_block.identity + new_block.identity
        old_block.get_block_feature()
        new_block.get_block_feature()
        old_block.get_block_vector()
        new_block.get_block_vector()
        # log info (change type, log statement, old and new loc)
        log_info = []
        log_info.append([log_record[my_constant.FETCH_LOG_CHANGE_TYPE],\
                        log_record[my_constant.FETCH_LOG_LOG], old_loc, new_loc])
        # create new record or modify past
        if old_new_block_dict.has_key(identity):
            analyze_record = old_new_block_dict[identity]
            analyze_record[my_constant.ANALYZE_OLD_NEW_LOG_INFO] += log_info
        else:
            analyze_record = []
            analyze_record.append(identity)
            analyze_record += old_block.get_info_except_identity()
            analyze_record += new_block.get_info_except_identity()
            # update info and log info
            analyze_record.append(log_record[my_constant.FETCH_LOG_COMMIT_SHA])
            analyze_record.append(log_record[my_constant.FETCH_LOG_COMMIT_MESSAGE])
            analyze_record.append(log_record[my_constant.FETCH_LOG_FILE])
            analyze_record.append(log_info)
        old_new_block_dict[identity] = analyze_record

    return old_new_block_dict, analyze_record

"""
@ param ...
@ return nothing
@ caller main
@ callee analyze_record_to_block
@ involve operate fetch and analyze files
"""
def analyze_old_new():

    fetch = file(my_constant.FETCH_LOG_FILE_NAME, 'rb')
    # initialize write file
    analysis = file(my_constant.ANALYZE_OLD_NEW_FILE_NAME, 'wb')
    analyze_writer = csv.writer(analysis)
    analyze_writer.writerow(my_constant.ANALYZE_OLD_NEW_TITLE)
    # initialize read file
    records = csv.reader(fetch)

    # traverse the fetch csv file to update context info
    count = 0
    old_new_block_dict = {}
    block.initialize_joern()
    for record in islice(records, 1, None):
        print "now record the No. %d analyze" %count
        # call analyze_record_to_block to retrieve block info
        old_new_block_dict, flag = analyze_record_to_block(record, old_new_block_dict)
        if flag is not None:
            count += 1
    # write back to analyze old new file
    for analyzed_record in old_new_block_dict.values():
        analyzed_record[my_constant.ANALYZE_OLD_NEW_OLD_BLOCK_VECTOR] = \
            json.dumps(analyzed_record[my_constant.ANALYZE_OLD_NEW_OLD_BLOCK_VECTOR])
        analyzed_record[my_constant.ANALYZE_OLD_NEW_NEW_BLOCK_VECTOR] = \
            json.dumps(analyzed_record[my_constant.ANALYZE_OLD_NEW_NEW_BLOCK_VECTOR])
        analyzed_record[my_constant.ANALYZE_OLD_NEW_LOG_INFO] = \
            json.dumps(analyzed_record[my_constant.ANALYZE_OLD_NEW_LOG_INFO])
        analyze_writer.writerow(analyzed_record)
    # close files
    analysis.close()
    fetch.close()


"""
main function
"""
if __name__ == "__main__":

    analyze_old_new()
