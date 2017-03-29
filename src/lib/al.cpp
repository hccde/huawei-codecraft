#include "Graph.cpp"
//find shortest path ==test
bool bellmanford(int s, int t, int &flow, int &cost, vector< vector<int> > &temp_routine, int &count)
{
	for (int i = 0; i < N; i++)
		d[i] = INF;//这里一开始用memset结果出错，调试了半天才找出来
	d[s] = 0;
	memset(vis, false, sizeof(vis));
	memset(p, -1, sizeof(p));
	p[s] = -1;
	a[s] = INF;
	queue<int> que;
	que.push(s);
	vis[s] = true;
	while (!que.empty())
	{
		int u = que.front();
		que.pop();
		vis[u] = false;
		for (int i = 0; i < g[u].size(); i++)
		{
			Edge& e = edges[g[u][i]];
			if (e.cap > e.flow&&d[e.to] > d[u] + e.cost)//进行松弛，寻找最短路径也就是最小费用
			{
				d[e.to] = d[u] + e.cost;
				p[e.to] = g[u][i];
				a[e.to] = min(a[u], e.cap - e.flow);
				if (!vis[e.to])
				{
					que.push(e.to);
					vis[e.to] = true;
				}
			}
		}
	}
	if (d[t] == INF)
		return false;
	flow += a[t];
	cost += d[t] * a[t];
	int temp_size = m_set.size();
	vector<int> oneRoutine;
	oneRoutine.clear();
	for (int i = t; i != s; i = edges[p[i]].from)
	{
		edges[p[i]].flow += a[t];
		edges[p[i] ^ 1].flow -= a[t];
		oneRoutine.push_back(i);
		//cout << i << " ";
	}


	//cout << a[t] << endl;
	//调整方向
	oneRoutine.erase(oneRoutine.begin());
	reverse(oneRoutine.begin(), oneRoutine.end());
	oneRoutine.push_back(custom_set.find(*(oneRoutine.end() - 1))->second);
	oneRoutine.push_back(a[t]);
	m_set.insert(pair<int, int>(*oneRoutine.begin(), count));
	if (m_set.size() > temp_size)
	{
		cost += (m_set.size() - temp_size)*severcost;
	}
	temp_routine.push_back(oneRoutine);
	//cout << endl;
	return true;
}