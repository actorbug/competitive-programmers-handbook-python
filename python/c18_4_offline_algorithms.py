import unittest
from collections import Counter,defaultdict
from c15_2_union_find_structure import UnionFind
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def merging(adj,val,x,q):
    a=[None]*len(q)
    r=defaultdict(list)
    for i,(p,_) in enumerate(q):
        r[p].append(i)
    d=[Counter([v]) for v in val]
    def dfs(s,e):
        for u in adj[s]:
            if u!=e:
                dfs(u,s)
                if len(d[u])>len(d[s]):
                    d[u],d[s]=d[s],d[u]
                d[s].update(d[u])
        for i in r[s]:
            a[i]=d[s][q[i][1]]
    dfs(x,0)
    return a

def lca(adj,x,q):
    a=[None]*len(q)
    r=defaultdict(list)
    for i,(j,k) in enumerate(q):
        r[j].append((i,k))
        r[k].append((i,j))
    n=len(adj)
    uf=UnionFind(n)
    value=[*range(n)]
    visited=[False]*n
    def dfs(s,e):
        for i,k in r[s]:
            if visited[k]:
                a[i]=value[uf.find(k)]
        visited[s]=True
        for u in adj[s]:
            if u!=e:
                dfs(u,s)
                uf.unite(u,s)
                value[uf.find(s)]=s
    dfs(x,0)
    return a

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(merging([[],[]],[0,3],1,[]),[])
        self.assertEqual(merging([[],[2,3,4,5],[1,6],[1],[1,7,8,9],[1],[2],[4],[4],[4]],[0,2,3,5,3,1,4,4,3,1],1,[(4,3)]),[2])

        self.assertEqual(lca([[],[]],1,[]),[])
        self.assertEqual(lca([[],[2,3,4],[1,5,6],[1],[1,7],[2],[2,8],[4],[6]],1,[(5,8),(2,7)]),[2,1])

if __name__=='__main__':
    unittest.main()
