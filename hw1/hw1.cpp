#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

class packet{

    private:
    int source; //起點
    int destination; //終點
    int last_hop; //上一個點
    int next_hop; //下一個點

    public:
    void initial(int, int, int, int);
    void newdist(int, int);
    int get(int);
};

class node{

    public:
    int id;
    double location_x;
    double location_y;

    vector< node* > neighbor; //鄰居
    queue< packet* > mypacket; //封包

    void send();
    int checkQueue();
    int getNextHop(node &); 
    double dist(node &);
};

void packet::initial(int sc, int des, int last, int next) //封包初始化
{
    this->source = sc;
    this->destination = des;
    this->last_hop = last;
    this->next_hop = next;
}

void packet::newdist(int last, int next) //更新封包資訊
{
    this->last_hop = last;
    this->next_hop = next;
    //cout<<"last = "<<last_hop<<"next = "<<next_hop<<"\n";
}

int packet::get(int num) //取得封包資訊
{
    if(num == 0) return source;
    else if (num == 1) return destination;
    else if (num == 2) return last_hop;
    else if (num == 3) return next_hop;
    else return -1;
}

int node::checkQueue() //檢查封包是否接收正確
{
    if(!(mypacket.empty()) && (mypacket.front()->get(3) == id)) return true;
    if(!(mypacket.empty()) && (mypacket.front()->get(3) != id)) mypacket.pop();
    return false;
}

double node::dist(node &nbr)
{
    return pow((location_x - nbr.location_x), 2) + pow((location_y - nbr.location_y), 2);
}

int node::getNextHop(node &des) //取得更近的點
{
    //first find dist of current node
    int next = id;
    double cur_dist = dist(des); 
    //cout<<"dist="<<cur_dist<<"\n";
    //second find neighbors' dist that closer than current's
    for(int i = 0; i < neighbor.size(); i++){
        //cout<<"nei_dist = "<<neighbor[i]->dist(des)<<"\tby:"<<neighbor[i]->id<<"\n";
        if(neighbor[i]->dist(des) < cur_dist){
            //cout<<"nei_dist = "<<neighbor[i]->dist(des)<<"\tby:"<<neighbor[i]->id<<"\n";
            next = neighbor[i]->id;
            cur_dist = neighbor[i]->dist(des);
        }
    }
    if(id == next) return -1;
    mypacket.front()->newdist(mypacket.front()->get(3), next);
    return next;
}

void node::send() //送出封包
{
    for(int i = 0; i < neighbor.size(); i++){
        neighbor[i]->mypacket.push(mypacket.front());
        /*cout<<neighbor[i]->mypacket.front()->get(0);
        cout<<neighbor[i]->mypacket.front()->get(1);
        cout<<neighbor[i]->mypacket.front()->get(2);
        cout<<neighbor[i]->mypacket.front()->get(3);*/
    }
}

double dist(node &a,node &b)
{
    return pow((a.location_x - b.location_x), 2) + pow((a.location_y - b.location_y), 2);
}

int main()
{
    int node_cnt;
    cin >> node_cnt;
    node *Node = new node[node_cnt];
    for(int i = 0; i < node_cnt; i++){
        cin >> (Node + i)->id;
        cin >> (Node + i)->location_x;
        cin >> (Node + i)->location_y;
    }
    //find neighbor
    for(int i = 0; i < node_cnt; i++){
        for(int j = 0; j < node_cnt; j++){
            if(i == j) continue;
            if(dist(*(Node + i), *(Node + j)) <= 1){
                (Node + i)->neighbor.push_back(Node + j);
            }
        }
    }

    int output_cnt;
    int start, end;
    packet *Packet = new packet[1];
    cin >> output_cnt;
    cout << output_cnt << endl;
    for(int i = 0; i < output_cnt; i++){
        cin >> start;
        cin >> end;
        Packet->initial(start, end, -1, start); //封包初始化
        (Node + start)->mypacket.push(Packet); //把封包丟給起點
        while(!((Node + start)->mypacket.empty())){
            if(((Node + start)->getNextHop(*(Node + end)))!=-1){
                (Node + start)->send();
                cout << start << " ";
            }
            (Node + start)->mypacket.pop();
            //check queue to get new nexthop
            for(int i = 0; i < node_cnt; i++){
                if((Node + i)->checkQueue()){
                    start = i;
                }
            }
        }
        cout << start << endl;
    }

    return 0;
}