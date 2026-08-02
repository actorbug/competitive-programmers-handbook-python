import unittest
from collections import defaultdict,Counter
from util import reversed_adj
import sys
from itertools import pairwise

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def existence(adj):
    odd=[]
    for i in range(1,len(adj)):
        if len(adj[i])%2==1:
            odd.append(i)
    if len(odd)==0:
        return [0,0]
    elif len(odd)==2:
        return odd
    else:
        return None

def existence2(adj,rev=None):
    if rev is None:
        rev=reversed_adj(adj)
    d=defaultdict(list)
    for e in range(1,len(adj)):
        d[len(rev[e])-len(adj[e])].append(e)
    if len(d[0])==len(adj)-1:
        return (0,0)
    elif len(d[0])==len(adj)-3 and 1 in d:
        return (d[-1][0],d[1][0])
    else:
        return None

def hierhorzer(adj):
    e=existence(adj)
    if e is None or len(adj)<=1:
        return ()
    adj=[*map(Counter,adj)]
    def dfs(s):
        while adj[s]:
            u=next(iter(adj[s].keys()))
            if adj[s][u]>1:
                adj[s][u]-=1
            else:
                del adj[s][u]
            if adj[u][s]>1:
                adj[u][s]-=1
            else:
                del adj[u][s]
            yield from dfs(u)
        yield s
    return dfs(max(1,e[1]))

def hierhorzer2(adj):
    rev=reversed_adj(adj)
    e=existence2(adj,rev)
    if not e or len(adj)<=1:
        return ()
    def dfs(s):
        while rev[s]:
            yield from dfs(rev[s].pop())
        yield s
    return dfs(max(1,e[1]))


class Test(unittest.TestCase):
    def assertHierhorzer(self,adj):
        with self.subTest(adj=adj):
            adj2=[[] for _ in adj]
            for i,j in pairwise(hierhorzer(adj)):
                adj2[i].append(j)
                adj2[j].append(i)
            self.assertEqual([*map(sorted,adj2)],adj)
    def assertHierhorzer2(self,adj):
        with self.subTest(adj=adj):
            adj2=[[] for _ in adj]
            for i,j in pairwise(hierhorzer2(adj)):
                adj2[i].append(j)
            self.assertEqual([*map(sorted,adj2)],adj)
    def test(self):
        adj1=[[],[2,4],[1,3,5],[2,5],[1,5],[2,3,4]]
        adj2=[[],[2,4],[1,3,4,5],[2,5],[1,2],[2,3]]

        self.assertEqual(existence([[]]),[0,0])
        self.assertCountEqual(existence(adj1),[2,5])
        self.assertEqual(existence(adj2),[0,0])
        self.assertIsNone(existence([[],[2,3,4],[1,3,4],[1,2,4],[1,2,3]]))

        adj3=[[],[2],[3,5],[5],[1],[4]]
        adj4=[[],[4],[1,5],[2],[2],[3]]

        self.assertEqual(existence2([[]]),(0,0))
        self.assertEqual(existence2(adj3),(2,5))
        self.assertEqual(existence2(adj4),(0,0))
        self.assertIsNone(existence2([[],[2,3,4],[3,4],[4],[]]))

        self.assertHierhorzer([[]])
        self.assertHierhorzer(adj1)
        self.assertHierhorzer(adj2)
        self.assertHierhorzer([[],[2,3],[1,3,5,6],[1,2,4,6],[3,7],[2,6],[2,3,5,7],[4,6]])

        self.assertHierhorzer2([[]])
        self.assertHierhorzer2(adj3)
        self.assertHierhorzer2(adj4)
        self.assertHierhorzer2([[],[2],[3,5],[1,4],[7],[6],[2,3],[6]])

if __name__=='__main__':
    unittest.main()
