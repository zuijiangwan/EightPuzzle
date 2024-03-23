#include "eight.h"
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    int MAXSTEP;
    cout<<"输入最大搜索步数："<<endl;
    cin>>MAXSTEP;

    // 清空输出文件
	ofstream truncateFile("output.txt", ios::trunc);
	truncateFile.close();
    ofstream fout;
    fout.open("output.txt", ios::app);

    // 读取输入
    ifstream fin("input.txt", ios::in);
    char buf;
    int init = 0;
    for(int i = 0; i < 9; i++){
        fin>>buf;
        int num = buf - '0';
        init = init*10 + num;
    }
    fin.close();

    // 设置初始状态
    int situation = init;
    int step = 0;
    multimap<int, int>fQueue; // 根据估计代价排序的队列，代价（f）-状态散列值
    fQueue.insert(pair<int, int>(h(situation), situation));
    map<int, int>searched; // 以搜索过的状态的散列值及其对应的最短步数，状态散列值-步数（g）
    searched[situation] = 0;

    // A*搜索主过程
    while(!isTarget(situation)){ // 搜索未终止
        step++;
        if(step > MAXSTEP)
            break;

        // 从队列中选出f(n)最小的结点
        situation = fQueue.begin()->second;
        int f = fQueue.begin()->first;
        int g = searched[situation];
        fQueue.erase(fQueue.begin());
        fout<<"第"<<step<<"次，代价为"<<f<<"，需要经过"<<g<<"步"<<endl;
        output(situation, fout);

        // 扩展结点，加入队列
        int pos0 = posZero(situation);
        if(pos0 > 2){
            int newSituation = swap(situation, pos0, pos0-3);
            if(searched.find(newSituation) == searched.end() || g+1 < searched[newSituation]){
                searched[newSituation] = g+1;
                fQueue.insert(pair<int, int>(g+1+h(newSituation), newSituation));
            }
        }
        if(pos0 < 6){
            int newSituation = swap(situation, pos0, pos0+3);
            if(searched.find(newSituation) == searched.end() || g+1 < searched[newSituation]){
                searched[newSituation] = g+1;
                fQueue.insert(pair<int, int>(g+1+h(newSituation), newSituation));
            }
        }
        if(pos0%3 != 0){
            int newSituation = swap(situation, pos0, pos0-1);
            if(searched.find(newSituation) == searched.end() || g+1 < searched[newSituation]){
                searched[newSituation] = g+1;
                fQueue.insert(pair<int, int>(g+1+h(newSituation), newSituation));
            }
        }
        if(pos0%3 != 2){
            int newSituation = swap(situation, pos0, pos0+1);
            if(searched.find(newSituation) == searched.end() || g+1 < searched[newSituation]){
                searched[newSituation] = g+1;
                fQueue.insert(pair<int, int>(g+1+h(newSituation), newSituation));
            }
        }
    }

    // 输出结果
    fout.close();
    if(isTarget(situation))
        cout<<"搜索成功"<<endl;
    else
        cout<<"搜索失败"<<endl;
    cout<<"一共试了"<<step-1<<"次"<<endl;
    return 0;
}