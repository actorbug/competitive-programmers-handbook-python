import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def topological(adj):
    n=len(adj)
    visited=[0]*n
    ret=[]
    def dfs(s):
        if visited[s]:
            return visited[s]!=1
        visited[s]=1
        if not all(map(dfs,adj[s])):
            return False
        ret.append(s)
        visited[s]=2
        return True
    for x in range(1,n):
        if not visited[x] and not dfs(x):
            return None
    ret.reverse()
    return ret

class Test(unittest.TestCase):
    def assertTopological(self,adj):
        with self.subTest(adj=adj):
            n=len(adj)
            ret=topological(adj)
            self.assertCountEqual(ret, range(1,n))
            pos={v:i for i,v in enumerate(ret)}
            for a in range(1,n):
                for b in adj[a]:
                    self.assertLess(pos[a],pos[b])
    def test(self):
        self.assertTopological([[]])
        self.assertTopological([[],[2],[3],[6],[1,5],[2,3],[]])
        self.assertIsNone(topological([[],[2],[3],[5,6],[1,5],[2],[]]))

if __name__=='__main__':
    unittest.main()
