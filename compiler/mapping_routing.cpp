#include"initializer.h"
#include"qctype.h"
#include"outputer.h"
#include<bits/stdc++.h>


namespace MR{
    // 0.712  1/sqrt(2.) 0.7 0.69
    const double alpha=1/sqrt(2.),INF=1e9;
    // double Rand(){return 1.0*rand()/RAND_MAX;}
    int n,dist[15][15];Schedule x;Graph G,G0;
    std::vector<std::vector<int> > path[15][15];

    double calc(const std::vector<int>& mp, const std::vector<int>& vis){
        std::vector<int> dep,deg;std::queue<int> Q;
        dep.resize(n,-1);deg.resize(n,0);
        for(int i=0;i<n;i++)if(!vis[i])for(int j:G[i])++deg[j];
        for(int i=0;i<n;i++)if(!vis[i]&&deg[i]==0)dep[i]=0,Q.push(i);
        double sum=0;
        while(!Q.empty()){
            int u=Q.front();Q.pop();
            sum+=pow(alpha,dep[u])*dist[mp[x[u].subj[0]]][mp[x[u].subj[1]]];
            for(int v:G[u])if(!--deg[v])dep[v]=dep[u]+1,Q.push(v);
        }
        return sum;
    }
    std::mt19937 rnd(
        std::chrono::steady_clock().now().time_since_epoch().count()
    );
    double now=INF;std::vector<int> pos,rev,vis;

    void allClear() {
        now = INF, x.clear(), G.clear();
        pos.clear(), rev.clear(), vis.clear();
    }

    void SA(){
        auto st = clock();
        std::vector<int> mp;mp.resize(13);
        std::iota(mp.begin(),mp.end(),0);
        std::uniform_int_distribution<> dtr(0, 12);
        for(double t=1e5;t>=1e-7;t*=0.99){
            auto lst=mp;
            double tmp=calc(mp,vis);
            if (t > 1) {
                shuffle(mp.begin(),mp.end(),rnd);
            } else if (t > 1e-3) {
                int p = dtr(rnd), q = dtr(rnd);
                if (p > q) std::swap(p, q);
                std::reverse(mp.begin() + p, mp.begin() + q + 1);
            } else {
                int p = dtr(rnd), q = dtr(rnd);
                std::swap(mp[p], mp[q]);
            }
            if(tmp<now) now = tmp, pos = mp;
            else {
                bool ok = std::bernoulli_distribution(exp((tmp-now)/t))(rnd);
                if (ok) now = tmp;
                else mp = lst;
            }
        }
        auto ed = clock();
#ifdef GATE_LOG
        // fprintf(stderr, "SA time cost: %f\n", double(ed - st) / CLOCKS_PER_SEC);
#endif
    }
    void init(){
        auto add=[&](int u,int v){G0[u].push_back(v);G0[v].push_back(u);};
        int n=13;G0.resize(n);add(5,6);add(4,6);add(6,7);
        add(4,1);add(6,3);add(7,8);add(2,1);add(1,3);add(3,8);
        add(8,9);add(1,0);add(3,12);add(8,10);add(0,12);add(12,10);add(12,11);
        auto bfs=[&](int st){
            int*dis=dist[st];std::queue<int> Q;
            for(int i=0;i<n;i++)dis[i]=-1;dis[st]=0;Q.push(st);
            path[st][st].push_back({st});
            while(!Q.empty()){
                int u=Q.front();Q.pop();
                for(int v:G0[u]){
                    if(dis[v]==-1)dis[v]=dis[u]+1,Q.push(v);
                    if(dis[v]==dis[u]+1)
                        for(auto x:path[st][u])
                            x.push_back(v),path[st][v].push_back(x);
                }
            }
        };
        for(int i=0;i<n;i++)bfs(i);
    }
    std::pair<std::vector<int>, Schedule> solve(Schedule _x,Schedule x1,Graph _G,Graph G1){
    	// std::cout<<"print G,G1\n";
		// for(int i=0;i<_G.size();i++){
		// 	std::cout<<_x[i].name<<",{";
		// 	for(int j:_x[i].subj)std::cout<<j<<(j==_x[i].subj.back()?"":",");
		// 	std::cout<<"},"<<_x[i].param<<":\nG=";
		// 	for(int j:_G[i])std::cout<<j<<" ";std::cout<<"\nG1=";
		// 	for(int j:G1[i])std::cout<<j<<" ";std::cout<<"\n";
		// }
        x=_x;G=_G;n=x.size();pos.resize(13);vis.resize(n);
        for(int i=1;i<=10;i++)SA();
        rev.resize(13);
        for(int i=0;i<13;i++)rev[pos[i]]=i;
        Schedule result{};
        auto change=[&](Gate v){
        	Gate tmp=v;for(int&z:tmp.subj)z=pos[z];return tmp;
		};
		for(int id:G1[n])result.push_back(change(x1[id]));

        // for (int i = 0; i < 13; ++i) fprintf(stderr, "%d ", pos[i]);
        // fprintf(stderr, "\n");

        for(int rd=1;rd<=n;rd++){
            std::vector<int> cho,deg;deg.resize(n,0);
            for(int i=0;i<n;i++)if(!vis[i])for(int j:G[i])++deg[j];
            for(int i=0;i<n;i++)if(!vis[i]&&deg[i]==0)cho.push_back(i);
            double minimum=INF;int minid=-1,mindis=-1;
            std::vector<int> minpos,minrev;Schedule minres,tres;
            for(int id:cho){
                int tu=x[id].subj[0],tv=x[id].subj[1];
				int u=pos[tu],v=pos[tv];
                auto tpos=pos,trev=rev,tvis=vis;tvis[id]=1;
                auto Swap=[&](int u,int v){
                    int x=trev[u],y=trev[v];
                    tres.push_back({"swap",{u,v},0.0});
                    std::swap(tpos[x],tpos[y]);
                    std::swap(trev[u],trev[v]);
                };
                for(int x=0;x<13;x++)for(int y:G0[x])
                    if(dist[u][x]+dist[v][y]+1==dist[u][v])
                        for(auto pa:path[u][x])
                        for(auto pb:path[v][y]){
                            tpos=pos;trev=rev;tres.clear();
                            for(int i=1;i<pa.size();i++)Swap(pa[i-1],pa[i]);
                            for(int i=pb.size()-1;i>=1;i--)Swap(pb[i-1],pb[i]);
                            double value=calc(tpos,tvis)+dist[u][v];
                            if(value<minimum)
                                minimum=value,minid=id,mindis=dist[u][v],
                                minpos=tpos,minrev=trev,minres=tres;
                        }
            }
            vis[minid]=1;pos=minpos;rev=minrev;
            for(auto z:minres)result.push_back(z);
            result.push_back(change(x[minid]));
			for(int id:G1[minid])result.push_back(change(x1[id]));
        }
        // for (int i = 0; i < 13; ++i) fprintf(stderr, "%d ", pos[i]);
        // fprintf(stderr, "\n");
#ifdef GATE_LOG
        fprintf(stderr, "total gate: %zd\n", result.size());
#endif
        return { pos, result };
    }
}

std::pair<std::vector<int>, Schedule> mapping_routing(Schedule _x,Graph _G){
    int n=_x.size(),m=0;Graph G,G1;Schedule x;
    std::vector<int> lst,nxt,type,rev,vis;
    rev.resize(n,-1);vis.resize(n,0);
    for(int i=0;i<n;i++){
        type.push_back(_x[i].subj.size()==2);
        if(type[i]==1)rev[i]=m,++m,x.push_back(_x[i]);
    }
    G.resize(m);G1.resize(m+1);lst.resize(n,-1);nxt.resize(n,-1);
    for(int i=n-1;i>=0;i--)if(type[i]==0){
        assert(_G[i].size()<=1);
        if(_G[i].size()==1){
            int z=_G[i][0];
            if(type[z]==1)nxt[i]=z;
            else nxt[i]=nxt[z];
        }
    }
    for(int i=0;i<n;i++){
        if(type[i]==0&&vis[i]==0)
            G1[lst[i]=m].push_back(i),vis[i]=1;
        if(type[i]==0&&_G[i].size()==1){
            int z=_G[i][0];if(type[z]!=0)continue;
            G1[lst[z]=lst[i]].push_back(z);vis[z]=1;
        }
        if(type[i]==1)for(int j:_G[i]){
            if(type[j]==1)G[rev[i]].push_back(rev[j]);
            else{
                G1[lst[j]=rev[i]].push_back(j),vis[j]=1;
                if(nxt[j]!=-1)G[rev[i]].push_back(rev[nxt[j]]);
            }
        }
    }

    MR::init();

    int ATTEMPT = 10;
    MR::allClear();
    auto ans = MR::solve(x, _x, G, G1);
    while (--ATTEMPT) {
        MR::allClear();
        auto tmp = MR::solve(x, _x, G, G1);
        if (tmp.second.size() < ans.second.size()) ans = tmp;
    }
    return ans;
}

int n=13;Schedule sch;Graph grp;
int main(){
	// freopen("1.in","r",stdin);
    // freopen("1.py", "w", stdout);
    auto st = clock();
    Init::init(n,sch,grp);
    auto res = mapping_routing(sch, grp);

#if defined(GATE_LOG) && defined(GATE_COUNT)
    std::map<std::string, int> _gateCnt;
    for (auto g: sch) ++_gateCnt[g.name];
    for (auto [name, cnt]: _gateCnt) {
        fprintf(stderr, "%s: %d\n", name.c_str(), cnt);
    }
    fprintf(stderr, "------\n");

    _gateCnt.clear();
    for (auto g: res.second) ++_gateCnt[g.name];
    for (auto [name, cnt]: _gateCnt) {
        fprintf(stderr, "%s: %d\n", name.c_str(), cnt);
    }
#endif

    output(res.first, res.second);
    auto ed = clock();
#ifdef GATE_LOG
    fprintf(stderr, "transpiling time: %f\n", double(ed - st) / CLOCKS_PER_SEC);
#endif
    return 0;
}
