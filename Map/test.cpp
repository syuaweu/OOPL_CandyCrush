#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
vector<vector<int>> LoadMap(string map_name) {
	ifstream in;
	in.open("../Resources/map/"+map_name + ".txt");
	int row, column;
	in >> row >> column;
	cout << row << ' ' << column << '\n';
	vector<vector<int>> map(10);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			int x = 0;
			in >> x;
			map[i].push_back(x);
		}
	}
	in.close();

	return map;
}
int main(){
    int n=5;
    vector<vector<int>> mp=LoadMap("1");
    for(int i=0;i<n;i++, cout<<'\n'){
        for(int j=0;j<n;j++){
            cout<<mp[i][j]<<' ';
        }
    }
}