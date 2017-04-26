#/usr/bin/python
from clusterBase import importData,pearson_distance
from PIL import Image, ImageDraw

class bicluster:
    def __init__(self, vec, left=None, right=None, distance=0.0, id=None):
        # for drawing picture of clusters
        self.left = left
        self.right = right
        # feature vector
        self.vec = vec
        #  id label for locating label
        self.id = id
        self.distance = distance

"""
@param: blogwords(entiry vectors), blognames(labels)
@return top cluster
@caller main
@callee pearson_distance
@involve: cluster entities based on distance
"""
def hcluster(blogwords, blognames):
    # initialize the custers to consist of each entity
    biclusters = [bicluster(vec=blogwords[i], id=i) for i in range(len(blogwords))]
    distances = {}
    flag = None
    currentclusted = -1

    # stop clustering based on culster number ( == 1)
    while len(biclusters) > 1:
        min_val = 2

        # traverse cluster a and cluster b in clusters
        biclusters_len = len(biclusters)
        for i in range(biclusters_len-1):
            for j in range(i + 1, biclusters_len):
                # compute distances if no record in dictory of distances
                if distances.get((biclusters[i].id, biclusters[j].id)) is None:
                    # compute distances by calling pearson_distance on (vector a, vector b)
                    distances[(biclusters[i].id, biclusters[j].id)] = pearson_distance(biclusters[i].vec,biclusters[j].vec)
                #  fetch the distance
                dist = distances[(biclusters[i].id, biclusters[j].id)]
                # find cluster pair with miniest distance and flag them
                if dist < min_val:
                    min_val = dist
                    flag = (i, j)
        # combine the two clusters
        bic1, bic2 = flag
        # compute new vector with calculating the average vector
        newvec = [(biclusters[bic1].vec[i] + biclusters[bic2].vec[i])/2 for i in range(len(biclusters[bic1].vec))]
        # create new bicluster(cluster id is minus number)
        newbic = bicluster(newvec, left=biclusters[bic1], right=biclusters[bic2], distance=min_val, id = currentclusted)
        currentclusted -= 1
        # remove old cluster from the clusters
        # have not destroy it
        del biclusters[bic2]
        del biclusters[bic1]
        biclusters.append(newbic)

    return biclusters[0]


"""
@param: cluster
@return int height
@caller drawnode
@callee self
@involve: get height of the cluster with children
"""
def getheight(clust):
    if clust.left is None and clust.right is None:
        return 1
    return getheight(clust.left) + getheight(clust.right)

"""
@param: cluster
@return int depth
@caller draw_dendrogram
@callee self
@involve: get depth of the cluster with children
"""
def getdepth(clust):
    if clust.left is None and clust.right is None:
        return 0
    return max(getdepth(clust.left), getdepth(clust.right)) + clust.distance

"""
@param: cluster, labels, img name to save
@return none
@caller main
@callee drawnode, getdepth, getheight
@involve: draw clusters with labels and save to given image file
"""
def draw_dendrogram(clust, labels, jpeg='clusters.jpg'):
    # set hight according to cluster height (number of entity)
    h = getheight(clust) * 20
    w = 1200
    # get depth of cluster(total distance)
    depth = getdepth(clust) 

    scaling = float(w-150) / depth

    img = Image.new('RGB', (w, h), (255, 255, 255))
    draw = ImageDraw.Draw(img)
    draw.line((0, h/2, 10, h/2), fill=(255, 0, 0))
    # draw the cluster from top by calling drawnode (center in h)
    drawnode(draw, clust, 10, (h/2), scaling, labels)
    img.save(jpeg, 'JPEG')

"""
@param: draw, cluster, x(w), y(h), scaling, labels
@return int depth
@caller draw_dendrogram
@callee self
@involve: draw cluster by coping with children
"""
def drawnode(draw, clust, x, y, scaling, labels):
    if clust.id < 0:
        h1 = getheight(clust.left) * 20
        h2 = getheight(clust.right) * 20

        top = y - (h1+h2)/2
        bottom = y + (h1+h2)/2
        #line length by distance multiply scaling
        ll = clust.distance * scaling

        # left line
        draw.line((x, top+h1/2, x, bottom-h2/2), fill=(255, 0, 0))
        # top line
        draw.line((x, top+h1/2, x+ll, top+h1/2), fill=(255, 0, 0))
        # bottom line
        draw.line((x, bottom-h2/2, x+ll, bottom-h2/2), fill=(255, 0, 0))
        # left children
        drawnode(draw, clust.left, x+ll, top+h1/2, scaling, labels)
        # right children
        drawnode(draw, clust.right, x+ll, bottom-h2/2, scaling, labels)
    else:
        # draw label
        draw.text((x+5, y-7), labels[clust.id], (0, 0, 0))


if __name__ == '__main__':
    #pearson_distance
    blogwords, blognames = importData()
    clust = hcluster(blogwords, blognames)
    print clust
    draw_dendrogram(clust, blognames, jpeg='blogclust.jpg')