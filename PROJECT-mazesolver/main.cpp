#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <fstream> // <--- needed for JSON export
using namespace std;

// ANSI colors
const string RESET   = "\033[0m";
const string BOLD    = "\033[1m";
const string BLUE    = "\033[34m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string CYAN    = "\033[36m";
const string MAGENTA = "\033[35m";
const string GRAY    = "\033[90m";
const string WHITE   = "\033[97m";

// Maze dimensions
int n = 21, m = 41; // width longer for visual appeal

// Directions
const int dr[4] = {-1,1,0,0};
const int dc[4] = {0,0,-1,1};

// --- UI FUNCTIONS ---
void printHeader(){
    cout << BOLD << CYAN
         << "\n====================================================\n"
         << "          INTELLIGENT MAZE PATHFINDER - BFS         \n"
         << "====================================================\n" 
         << RESET;
}

void showProgress(const string& msg, int percent){
    cout << "\r" << CYAN << msg << " [";
    int bars = percent/5;
    for(int i=0;i<20;i++){
        if(i<bars) cout << GREEN << "=" << RESET;
        else cout << GRAY << "-" << RESET;
    }
    cout << "] " << YELLOW << percent << "%" << RESET << flush;
}

void printStats(int pathLen, int totalCells, int wallCount, int exploreCount){
    cout << "\n" << BOLD << YELLOW << "=================== STATISTICS ===================\n" << RESET;
    cout << CYAN << "Maze Size:       " << RESET << WHITE << n << "x" << m << " (" << totalCells << " cells)\n" << RESET;
    cout << CYAN << "Wall Density:    " << RESET << WHITE << (wallCount*100/totalCells) << "%\n" << RESET;
    cout << CYAN << "Cells Explored:  " << RESET << MAGENTA << exploreCount << "\n" << RESET;
    cout << CYAN << "Shortest Path:   " << RESET << GREEN << pathLen << " steps\n" << RESET;
    cout << BOLD << YELLOW << "==================================================\n" << RESET;
}

// --- MAZE GENERATION ---
vector<vector<int>> generateMaze(){
    vector<vector<int>> grid(n, vector<int>(m,1));
    int progress=0;

    // Recursive backtracking
    function<void(int,int)> carve=[&](int r,int c){
        grid[r][c]=0; progress++;
        if(progress%20==0) showProgress("Building maze", min(99,(progress*100)/(n*m/2)));

        vector<int> dirs={0,1,2,3};
        for(int i=3;i>0;i--){
            int j=rand()%(i+1);
            swap(dirs[i],dirs[j]);
        }

        for(int i=0;i<4;i++){
            int nr=r+dr[dirs[i]]*2, nc=c+dc[dirs[i]]*2;
            if(nr>0 && nr<n-1 && nc>0 && nc<m-1 && grid[nr][nc]==1){
                grid[r+dr[dirs[i]]][c+dc[dirs[i]]]=0;
                carve(nr,nc);
            }
        }
    };

    carve(1,1);

    // Random openings for visual appeal
    for(int i=1;i<n-1;i++)
        for(int j=1;j<m-1;j++)
            if(grid[i][j]==1 && rand()%100<10) grid[i][j]=0;

    // Ensure start/end open
    grid[0][0]=0; grid[n-1][m-1]=0;
    grid[0][1]=0; grid[1][0]=0;
    grid[n-1][m-2]=0; grid[n-2][m-1]=0;

    showProgress("Building maze",100);
    cout << " " << GREEN << "Done!" << RESET << "\n";
    return grid;
}

// --- BFS PATHFINDING ---
pair<vector<pair<int,int>>, int> bfsPath(vector<vector<int>>& grid){
    vector<vector<int>> dist(n, vector<int>(m,-1));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m,{-1,-1}));
    queue<pair<int,int>> q;
    int explored=0;

    dist[0][0]=0; q.push({0,0});
    while(!q.empty()){
        auto [r,c]=q.front(); q.pop();
        if(r==n-1 && c==m-1) break;

        for(int k=0;k<4;k++){
            int nr=r+dr[k], nc=c+dc[k];
            if(nr>=0 && nr<n && nc>=0 && nc<m && grid[nr][nc]==0 && dist[nr][nc]==-1){
                dist[nr][nc]=dist[r][c]+1;
                parent[nr][nc]={r,c};
                q.push({nr,nc});
                explored++;
            }
        }
    }

    vector<pair<int,int>> path;
    if(dist[n-1][m-1]==-1) return {path, explored};

    pair<int,int> cur={n-1,m-1};
    while(cur.first!=-1){
        path.push_back(cur);
        cur=parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    return {path, explored};
}

// --- PRINT MAZE ---
void printMaze(vector<vector<int>>& grid, set<pair<int,int>>& pathCells, pair<int,int> head){
    system("cls");
    printHeader();

    // Top border
    cout << " ";
    for(int j=0;j<m;j++) cout << "--";
    cout << "\n";

    for(int i=0;i<n;i++){
        cout << "|";
        for(int j=0;j<m;j++){
            if(i==0 && j==0) cout<<BLUE<<"S "<<RESET;
            else if(i==n-1 && j==m-1) cout<<RED<<"E "<<RESET;
            else if(head==make_pair(i,j)) cout<<YELLOW<<"O "<<RESET;
            else if(pathCells.count({i,j})) cout<<GREEN<<"* "<<RESET;
            else if(grid[i][j]==1) cout<<GRAY<<"##"<<RESET;
            else cout<<"  ";
        }
        cout<<"|\n";
    }

    // Bottom border
    cout << " ";
    for(int j=0;j<m;j++) cout << "--";
    cout << "\n";

    // Legend
    cout << BLUE<<"S"<<RESET<<"=Start  "<<RED<<"E"<<RESET<<"=End  "
         <<YELLOW<<"O"<<RESET<<"=Current  "<<GREEN<<"*"<<RESET<<"=Path  "
         <<GRAY<<"#"<<RESET<<"=Wall\n";

    this_thread::sleep_for(chrono::milliseconds(50));
}

// --- MAIN ---
int main(){
    srand(time(0));
    system("cls");
    printHeader();
    cout << CYAN << "\nInitializing pathfinding...\n" << RESET;
    this_thread::sleep_for(chrono::milliseconds(800));

    vector<vector<int>> grid; vector<pair<int,int>> path; int explored=0;
    int attempts=0;

    cout << YELLOW << "\nGenerating complex maze...\n" << RESET;
    do{
        grid=generateMaze();
        auto res=bfsPath(grid);
        path=res.first; explored=res.second;
        attempts++;
        if(path.empty() && attempts<5){
            cout << YELLOW << "Retrying maze generation...\n" << RESET;
        }
    }while(path.empty() && attempts<5);

    if(path.empty()){
        cout << RED << "Failed to generate solvable maze after 5 attempts!\n" << RESET;
        return 1;
    }

    cout << GREEN << "\nMaze generated!\n" << RESET;
    this_thread::sleep_for(chrono::milliseconds(600));

    // Animate pathfinding
    set<pair<int,int>> pathCells;
    for(auto cell:path){
        pathCells.insert(cell);
        printMaze(grid,pathCells,cell);
    }

    // Stats
    int wallCount=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(grid[i][j]==1) wallCount++;

    printStats(path.size(), n*m, wallCount, explored);

    // --- EXPORT MAZE & PATH TO JSON ---
    ofstream outFile("maze.json");
    outFile << "{\n";
    outFile << "  \"n\": " << n << ",\n";
    outFile << "  \"m\": " << m << ",\n";
    outFile << "  \"maze\": [\n";
    for(int i=0;i<n;i++){
        outFile << "    [";
        for(int j=0;j<m;j++){
            outFile << grid[i][j];
            if(j!=m-1) outFile << ",";
        }
        outFile << "]";
        if(i!=n-1) outFile << ",";
        outFile << "\n";
    }
    outFile << "  ],\n";
    outFile << "  \"path\": [\n";
    for(size_t i=0;i<path.size();i++){
        outFile << "    [" << path[i].first << "," << path[i].second << "]";
        if(i!=path.size()-1) outFile << ",";
        outFile << "\n";
    }
    outFile << "  ]\n";
    outFile << "}\n";
    outFile.close();

    cout << GREEN << "\nMaze and path exported to maze.json!\n" << RESET;
    cout << CYAN << "\nPress Enter to exit...\n" << RESET;
    cin.get();
    return 0;
}
