from itertools import islice 
import csv
import json
import my_constant

"""
@ param csv file name
@ return statistic info(no.cluster, no.>1cluster, no.repeted log) 
@ involve get statistical info about cluster
"""
def statistical_cluster(csv_file_name):
    reading_file = file(csv_file_name)
    records = csv.reader(reading_file)
    edit_type_dict = {}
    cluster_dict = {}
    number_log = 0
    number_cluster = 0
    repeted_cluster = 0
    repeted_log = 0
    for record in islice(records, 1, None):
        # build dictary about edition type
        edit_types = json.loads(record[my_constant.ANALYZE_EDIT_TYPE])
        for edit_type in edit_types:
            if edit_type_dict.has_key(edit_type):
                edit_type_dict[edit_type] += 1
            else:
                edit_type_dict[edit_type] = 0
        # deal with edit feature 
        number_log += 1
        edit_feature = json.loads(record[my_constant.ANALYZE_EDIT_FEATURE])
        # ignore empty edition
        if edit_feature == [0]:
            continue
        cluster = json.loads(record[my_constant.ANALYZE_CLUSTER])
        # if has been in dict then increment counter
        if cluster_dict.has_key(cluster):
            # first repetetion -> repeted cluster
            if cluster_dict[cluster] == 1:
                repeted_cluster += 1
                # repeted log initialize
                repeted_log += 1
            # if have repetion, increment value(mark)
            cluster_dict[cluster] += 1
            # repeted log
            repeted_log += 1
        # if new, add to dict(mark)
        else:
            cluster_dict[cluster] = 1
            number_cluster += 1

    # show edition type result
    for edit_type, count in edit_type_dict:
        print "%s: %d" %(edit_type, count)
    # show cluster result
    print "log is %d, cluster is %d, repeted cluster is %d, repeted log is %d" %(number_log, number_cluster, repeted_cluster, repeted_log)


if __name__ == "__main__":
    # statistics about edition cluster
    edition_file_name = my_constant.CLUSTER_EDITION_OLD_NEW_FILE_NAME
    statistical_cluster(edition_file_name)
    # statistics about edition and feature cluster
    edition_and_feature_file_name = my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME
    statistical_cluster(edition_and_feature_file_name)
