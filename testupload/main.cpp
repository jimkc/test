
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;

void saveHints(vector<vector<int> >&height,vector<vector<int> >&width,int n,int m){

    
    int hint = 0;
    stringstream ss;
    string       temp;
    
    for (int i=0; i<n; i++) {
        string tmp,line1;
        
        getline(cin, line1);
        
        for (int j = 0; j < line1.length(); j++) {
            if (line1[j] ==' ') {
                istringstream ss(tmp);
                ss >> hint;
                
                height[i].push_back(hint);
                tmp.clear();
            }
            else tmp += line1[j];
        }
        
        istringstream ss(tmp);
        ss >> hint;
        height[i].push_back(hint);
        
        
        
    }
    for (int i=0; i<m; i++) {
        string tmp,line1;
        
        getline(cin, line1);
        
        for (int j = 0; j < line1.length(); j++) {
            if (line1[j] ==' ') {
                istringstream ss(tmp);
                ss >> hint;
                
                width[i].push_back(hint);
                tmp.clear();
            }
            else tmp += line1[j];
        }
        
        istringstream ss(tmp);
        ss >> hint;
        width[i].push_back(hint);
        
        
        
    }
    
  
}


void leftRight(vector<vector<int> >&hint,int roll,int length,vector<int> &temp){
    vector<int > tempRight ;//都空一格情況擠到最右邊
    vector<int > tempLeft(length,0);//擠到最左邊

    
    for (int i=1; i<hint[roll].size(); i++) {
        for (int j=0; j<hint[roll][i]; j++) {
            
            tempRight.push_back(i);
        }
        tempRight.push_back(0);
    }
    tempRight.pop_back();
    
    
    for (int i = 0; i < tempRight.size(); ++i)
    {
        tempLeft[tempLeft.size()-1-i]=tempRight[tempRight.size()-1-i];
    }
    
    for (int j=tempRight.size()+1; j<=length; j++) {
        tempRight.push_back(0);
    }

    for (int i = 0; i < tempRight.size(); i++)
    {
        if (tempRight[i]>0 && tempRight[i]==tempLeft[i])
        {
            temp.push_back(tempRight[i]);
        }
        else temp.push_back(0);
    }
    
}

void mark(vector<vector<int> >&nono,vector<vector<int> >&hHint,vector<vector<int> >&wHint,int n,int m,vector<int> lftemp){
    for (int i=1; i<n+1; i++) {
        leftRight(hHint, i-1, m,lftemp);
        
        for (int j=1; j<m+1; j++) {
            if (lftemp[j-1]>0) {
                nono[i][j]=lftemp[j-1];
            }
        }
        
        lftemp.clear();
    }
    
    for (int i=1; i<m+1; i++) {
        leftRight(wHint, i-1, n,lftemp);
        for (int j=1; j<n+1; j++) {
            if (lftemp[j-1]>0) {
                nono[j][i]=lftemp[j-1];
            }
        }
        lftemp.clear();
    }
    
    
}

bool checkDoneHorizon(vector<vector<int > >&nono, vector<int > &hHint,int length,int roll){
  
    int temp = 0;//計算有沒有和hint一樣
    vector<int > compare;//和hint比較有沒有一樣

    for (int i = 1; i <=length ; i++)
    {
        if (nono[roll][i]>0)
        {
            temp++;
        }
        else if (nono[roll][i]<=0)
        {
            if (temp>0) {
                compare.push_back(temp);
                temp=0;
            }
            
        }
    }
    compare.push_back(temp);
    
    
    if (compare.size()!=hHint.size()-1) {
        return false;
    }
    
    for (int i=0; i<compare.size(); i++) {
        if (compare[i]!=hHint[i+1]) {
            return false;
        }
    }
    
    return true;
}

bool checkDoneVertical(vector<vector<int > >&nono, vector<int > &wHint,int length,int column){
   
    int temp = 0;//計算有沒有和hint一樣
    vector<int > compare;//和hint比較有沒有一樣
    
    for (int i = 1; i <=length ; i++)
    {
        if (nono[i][column]>0)
        {
            temp++;
        }
        else if (nono[i][column]<=0)
        {
            if (temp>0) {
                compare.push_back(temp);
                temp=0;
            }
            
        }
    }
    compare.push_back(temp);
    
    for (int i=0; i<compare.size(); i++) {
        cout<<compare[i]<<" ";
    }
    cout<<endl;
    
    if (compare.size()!=wHint.size()-1) {
        return false;
    }
    
    for (int i=0; i<compare.size(); i++) {
        if (compare[i]!=wHint[i+1]) {
            return false;
        }
    }
    
    return true;
}

void linePossibilities(vector<vector<vector<int> > >&p,vector<int >linehint,int length,int pos,vector<int> &temp,int index/*hint中的第幾個提示*/,int roll/*p的第幾排*/){
    
    int end=0;
    int head=pos;//pos預設為0
    int otherhints=0;//除了當前自己以外後面hint往最右擠所佔的格子數;
    
    for (int i=index+1; i<linehint.size(); i++) {
        otherhints+=linehint[i];
        otherhints+=1;
    }
    end=length-otherhints-linehint[index];//line最右邊格子可以走到的最底
    
    index++;
    
    for (int i=head; i<=end; i++) {
        pos=i+linehint[index-1]+1;
        
        for(int j=i;j<linehint[index-1]+i;j++){
            temp[j]=1;
        }
        
        if(index-1==linehint.size()-1/*因為前面index先多加了*/){
            for(int j=0;j<length;j++){
                p[roll][j].push_back(temp[j]);
            }
        }
        
        if(index-1<linehint.size()-1){
            linePossibilities(p,linehint, length, pos, temp, index,roll);
        }
        
        for(int j=i;j<temp.size();j++){
            temp[j]=0;
        }
    }
    
}

void definite(vector<vector<vector<int> > >&hp,int length1,vector<vector<vector<int> > >&vp,int length2,vector<vector<int> >&nono){
   
    for (int i=0; i<hp.size(); i++) {
        for (int j=0; j<length1; j++) {
            for (int k=1; k<hp[i][j].size(); k++) {
                hp[i][j][0]+=hp[i][j][k];
            }
            for (int l=0; l<length1; l++) {
                if (hp[i][j][0]==hp[i][j].size()-1) {
                    nono[i+1][j+1]=1;
                }
                if (hp[i][j][0]==0) {
                    nono[i+1][j+1]=-1;
                }
            }
            
        }
    }
    
    for (int i=0; i<vp.size(); i++) {
        for (int j=0; j<length2; j++) {
            for (int k=1; k<vp[i][j].size(); k++) {
                vp[i][j][0]+=vp[i][j][k];
            }
            for (int l=0; l<length2; l++) {
                if (vp[i][j][0]==vp[i][j].size()-1) {
                    nono[j+1][i+1]=1;
                }
                if (vp[i][j][0]==0) {
                    nono[j+1][i+1]=-1;
                }
            }
            
        }
    }
}


bool compare(vector<int> const &a, vector<int> const &b){
    return a[0]>b[0];
}

void findOrder(vector<vector<int > >hHint,vector<vector<int > >wHint,vector<int >&hOrder,vector<int >&wOrder){
    for (int j=0; j<hHint.size();j++ ) {
        for (int i=1; i<hHint[j].size(); i++) {
            hHint[j][0]+=hHint[j][i];//在hint的最後一格插入第幾排代號（跟hint一樣從0開始）
        }
        hHint[j].push_back(j);
    }
    
    for (int j=0; j<wHint.size();j++ ) {
        for (int i=1; i<wHint[j].size(); i++) {
            wHint[j][0]+=wHint[j][i];
        }
        wHint[j].push_back(j);
    }
    
    sort(hHint.begin(), hHint.end(), compare );
    sort(wHint.begin(), wHint.end(), compare);
    
    for (int i=0; i<hHint.size(); i++) {
        hOrder.push_back(hHint[i].back());
    }
    
    for (int i=0; i<wHint.size(); i++) {
        wOrder.push_back(wHint[i].back());
    }
//////////////////////////////////////////////////////
    for (int i=0; i<hOrder.size(); i++) {
        cout<<hOrder[i]<<" ";
    }
    cout<<endl;
    for (int i=0; i<wOrder.size(); i++) {
        cout<<wOrder[i]<<" ";
    }
    
    cout<<endl;
    /*for (int j=0; j<hHint.size();j++ ) {
        for (int i=0; i<hHint[j].size(); i++) {
            cout<<hHint[j][i]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for (int j=0; j<wHint.size();j++ ) {
        for (int i=0; i<wHint[j].size(); i++) {
            cout<<wHint[j][i]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
    
    
}

void wScanner(vector<vector<int> >&nono,vector<vector<int > >&wtemp,int i,vector<int >wOrder/*大小從0開始,記錄位置也是0開始*/){
    int scanIndex=wOrder[i];
    vector<int >tmp(2,0);
    
    for (int k=1; k<=nono.size()-2; k++) {
        if (nono[k][scanIndex+1]==1) {
            tmp[0]=k-1;//讓存進去的index跟possibilitiy一樣從0開始
            tmp[1]=1;
            wtemp.push_back(tmp);
        }
        else if (nono[k][scanIndex+1]==-1){
            tmp[0]=k-1;
            tmp[1]=0;
            wtemp.push_back(tmp);
        }
    }
    
    
}

void hScanner(vector<vector<int> >&nono,vector<vector<int > >&htemp,int i,vector<int >hOrder/*大小從0開始,記錄位置也是0開始*/){
    int scanIndex=hOrder[i];
    vector<int >tmp(2,0);
    
    for (int k=1; k<=nono[0].size()-2; k++) {
        if (nono[scanIndex+1][k]==1) {
            tmp[0]=k-1;
            tmp[1]=1;
            htemp.push_back(tmp);
        }
        else if (nono[scanIndex+1][k]==-1){
            tmp[0]=k-1;
            tmp[1]=0;
            htemp.push_back(tmp);
        }
    }
    
    
}

void guessing(vector<vector<int> >nono,vector<int>&hOrder,vector<int>&wOrder){
    stack<vector<vector<int> > >s;
    
    for (int i=0; i<wOrder.size(); i++) {
        
    }
}
void guess(vector<vector<int> >nono,vector<vector<vector<int> > >&hp,vector<vector<vector<int > > >&vp,vector<int>&hOrder,vector<int>&wOrder){
    stack<vector<vector<int> > >s;
    stack<vector<vector<int> > >rec;
    stack<vector<vector<int> > >stk;
    vector<vector<int> >wtemp;
    vector<vector<int > >htemp;//儲存nono裡面標記的格子,再去找有的,第一格是0,從第一格開始
    int orderW = 0;//要執行第幾排
    int orderH = 0;
    int havePush=0;
    int hdo = 1;
    int wdo = 1;
    vector<int >wdoOrder(wOrder.size(),0);
    vector<int >hdoOrder(hOrder.size(),0);
    
    s.push(nono);
    
    while (1) {
        for (int i=0; i<wOrder.size(); i++) {
            if (wdoOrder[i]==0) {
                orderW=wOrder[i];
                wdo=1;
                break;
            }
            else{wdo=0;};
            
        }
        while (havePush==0&&wdo==1) {
            wScanner(nono, wtemp, orderW, wOrder);
            if (wtemp.size()==0) {
                for (int k=1; k<vp[orderW][0].size(); k++) {
                    stk.push(s.top());
                    wdoOrder[orderW]-=1;
                    for (int n=1; n<=nono.size()-2; n++) {
                        stk.top()[n][orderW+1]=vp[orderW][n-1][k];
                    }
                }
                havePush=1;
            }
            if (wtemp.size()>0) {
                for (int k=1; k<vp[orderW][0].size(); k++) {
                    
                    for (int l=0; l<wtemp.size(); l++) {
                        
                        if (vp[orderW][wtemp[l][0]][k]!=wtemp[l][1]) {
                            break;//如果possiblity的格子和temp的值不一樣就break出去
                        }
                        if (l==wtemp.size()-1&&vp[orderW][wtemp[l][0]][k]==wtemp.back()[1]) {//跑到wtemp最後一格還是一樣就抓出來
                            stk.push(s.top());//把進行到的前一步驟放進stack
                            wdoOrder[orderW]-=1;
                            havePush=1;
                            for (int n=1; n<=nono.size()-2; n++) {
                                stk.top()[n][orderW+1]=vp[orderW][n-1][k];
                            }
                        }
                    }
                    
                }
            }
            if (havePush==0) {
                stk.pop();
                hdoOrder[orderH]+=1;
                if (hdoOrder[orderH]==0) {
                    s.push(stk.top());
                    stk.pop();
                    wdoOrder[orderW-1]+=1;
                    orderW-=1;////////
                    break;
                }
                s.push(stk.top());
                stk.pop();
                hdoOrder[orderH]+=1;
            }
            htemp.clear();
        }
        s.push(stk.top());
        stk.pop();
        wdoOrder[orderW]+=1;
        havePush=0;
        //////////////////////////////////////////////////
        for (int i=0; i<hOrder.size(); i++) {
            if (hdoOrder[i]==0) {
                orderH=hOrder[i];
                hdo=1;
                break;
            }
            else{hdo=0;};
        }
        while (havePush==0&&hdo==1) {
            hScanner(nono, htemp, orderH, hOrder);
            if (htemp.size()==0) {
                for (int k=1; k<hp[orderH][0].size(); k++) {
                    stk.push(s.top());
                    hdoOrder[orderH]-=1;
                    for (int j=0; j<stk.top().size(); j++) {
                        for (int i=0; i<stk.top()[j].size(); i++) {
                            cout<<stk.top()[j][i]<<" ";
                        }
                        cout<<endl;
                    }
                    cout<<endl;
                    for (int n=1; n<=nono[0].size()-2; n++) {
                        stk.top()[orderH+1][n]=hp[orderH][n-1][k];
                    }
                }
                havePush=1;
            }
            if (htemp.size()>0) {
                for (int k=1; k<hp[orderH][0].size(); k++) {
                    
                    for (int l=0; l<htemp.size(); l++) {
                        
                        if (hp[orderH][htemp[l][0]][k]!=htemp[l][1]) {
                            break;//如果possiblity的格子和temp的值不一樣就break出去
                        }
                        if (l==htemp.size()-1&&hp[orderH][htemp[l][0]][k]==htemp.back()[1]) {//跑到wtemp最後一格還是一樣就抓出來
                            stk.push(s.top());//把進行到的前一步驟放進stack
                            hdoOrder[orderH]-=1;
                            havePush=1;
                            for (int n=1; n<=nono[0].size()-2; n++) {
                                stk.top()[orderH+1][n]=hp[orderH][n-1][k];
                            }
                        }
                    }
                    
                }
            }
            if (havePush==0) {
                stk.pop();
                wdoOrder[orderW]+=1;
                if (wdoOrder[orderW]==0) {
                    s.push(stk.top());
                    stk.pop();
                    hdoOrder[orderH-1]+=1;
                    break;
                }
                s.push(stk.top());
                stk.pop();
                wdoOrder[orderW]+=1;
            }
            htemp.clear();
        }
        s.push(stk.top());
        stk.pop();
        hdoOrder[orderH]+=1;
        havePush=0;
        
        if (hdoOrder.back()==0) {
            break;
        }
    }
    
    for (int j=1; j<s.top().size()-1;j++) {
        for (int i=1; i<s.top()[j].size()-1; i++) {
            if (s.top()[j][i]==1) {
                cout<<"# ";
            }
            else cout<<". ";
        }
        cout<<endl;
    }
    cout<<endl;
}



/*void guess(vector<vector<int> >nono,vector<vector<vector<int> > >&hp,vector<vector<vector<int > > >&vp,vector<int>&hOrder,vector<int>&wOrder,vector<vector<int> > &wHints, vector<vector<int> > &hHints,int m,int n){
    
    stack<vector<vector<int> > >s;//紀錄前一步驟nono的樣子
    stack<vector<vector<int> > >stack;
    vector<vector<int> >wtemp;
    vector<vector<int > >htemp;//儲存nono裡面標記的格子,再去找有的,第一格是0,從第一格開始
    s.push(nono);
    stack.push(s.top());
    int havePush=0;
    int done=-1;
    
    
    if (hOrder.size()==wOrder.size()) {
        while (1) {
            
            for (int i=0; i<wOrder.size(); i++) {
                if (checkDoneVertical(nono, wHints[i], n, i)==false) {
                    while (havePush==0) {
                        
                        wScanner(s.top(), wtemp, i, wOrder);//掃描那行的確定有和沒有的格子放到wtemp裡面
                        //cout<<wtemp.size()<<" /////////"<<endl;//////
                        if (wtemp.size()==0) {
                            for (int k=1; k<vp[wOrder[i]][0].size(); k++) {
                                stack.push(s.top());
                                for (int n=1; n<=nono.size()-2; n++) {
                                    stack.top()[n][wOrder[i]+1]=vp[wOrder[i]][n-1][k];
                                }
                            }
                            havePush=1;
                        }
                        if (wtemp.size()>0) {
                            for (int k=1; k<vp[wOrder[i]][0].size(); k++) {
                                
                                for (int l=0; l<wtemp.size(); l++) {
                                    
                                    if (vp[wOrder[i]][wtemp[l][0]][k]!=wtemp[l][1]) {
                                        break;//如果possiblity的格子和temp的值不一樣就break出去
                                    }
                                    if (l==wtemp.size()-1&&vp[wOrder[i]][wtemp[l][0]][k]==wtemp.back()[1]) {//跑到wtemp最後一格還是一樣就抓出來
                                        stack.push(s.top());//把進行到的前一步驟放進stack
                                        havePush=1;
                                        for (int n=1; n<=nono.size()-2; n++) {
                                            stack.top()[n][wOrder[i]+1]=vp[wOrder[i]][n-1][k];
                                        }
                                    }
                                }
                                
                            }
                        }
                        if (havePush==0) {
                            stack.pop();
                        }
                        wtemp.clear();
                        s.push(stack.top());
                        stack.pop();
                        
                        
                        
                    }

                }
                havePush=0;
                
                if (checkDoneHorizon(nono, hHints[i], m, i)==false) {
                    while (havePush==0) {
                        hScanner(s.top(), htemp, i, hOrder);//掃描那行的確定有和沒有的格子放到wtemp裡面
                        
                        if (htemp.size()==0) {
                            for (int k=1; k<hp[hOrder[i]][0].size(); k++) {
                                stack.push(s.top());
                                for (int n=1; n<=nono[0].size()-2; n++) {
                                    stack.top()[hOrder[i]+1][n]=hp[hOrder[i]][n-1][k];
                                    // cout<<stack.top()[hOrder[i]+1][n]<<" ";
                                }
                                //cout<<endl;
                            }
                            havePush=1;
                        }
                        if (htemp.size()>0) {
                            for (int k=1; k<hp[hOrder[i]][0].size(); k++) {
                                
                                for (int l=0; l<htemp.size(); l++) {
                                    
                                    if (hp[hOrder[i]][htemp[l][0]][k]!=htemp[l][1]) {
                                        break;//如果possiblity的格子和temp的值不一樣就break出去
                                    }
                                    
                                    if (l==htemp.size()-1&&hp[hOrder[i]][htemp[l][0]][k]==htemp.back()[1]) {//跑到wtemp最後一格還是一樣就抓出來
                                        stack.push(s.top());//把進行到的前一步驟放進stack
                                        havePush=1;
                                        
                                        for (int n=1; n<=nono[0].size()-2; n++) {
                                            stack.top()[hOrder[i]+1][n]=hp[hOrder[i]][n-1][k];
                                        }
                                    }
                                }
                                
                            }
                        }
                        if (havePush==0) {
                            stack.pop();
                        }
                        //cout<<"stack size="<<stack.size()<<endl;
                        
                        htemp.clear();
                        s.push(stack.top());
                        stack.pop();
                        
                    }

                }
                havePush=0;
                
            }
            
            
            done=0;
            for (int i=1; i<=nono.size()-2; i++) {
                if (checkDoneHorizon(s.top(), hHints[i-1], m, i)==false) {
                    done=-1;
                    break;
                }
            }
            
            for (int i=1; i<=nono[0].size()-2; i++) {
                if (checkDoneVertical(s.top(), wHints[i-1], n, i)==false) {
                    done=-1;
                    break;
                }
            }
            if (done==0) {
                break;
            }
        }
    }
    ///////
    
    
    cout<<"hi"<<endl;   
    for (int j=1; j<s.top().size()-1;j++) {
        for (int i=1; i<s.top()[j].size()-1; i++) {
            if (s.top()[j][i]==1) {
                cout<<"# ";
            }
            else cout<<". ";
        }
        cout<<endl;
    }
    cout<<endl;
    
}*/


int main(int argc, char const *argv[])
{
    int n,m;//size of nonogram = n*m
    
    cin>>n>>m;
    cin.ignore();

    vector<vector<int> > nonogram(n+2,vector<int>(m+2,0));//大小n+2*m+2,實際格子index從1開始到邊界-1
    vector<vector<int> > widthHints(m,vector<int>(1,0));
    vector<vector<int> > heightHints(n,vector<int>(1,0));//提示的index從0開始
    vector<int > hOrder;//記錄每個行hint的權重大小
    vector<int > wOrder;
    vector<int > lftemp;
    vector<vector<vector<int > > > horrizontalPossiblities(n,vector<vector<int> >(m,vector<int >(1,0)));
    vector<vector<vector<int > > > verticalPossiblities(m,vector<vector<int> >(n,vector<int >(1,0)));//三維陣列存hint的所有可能,黑標記1白標記0
    vector<int > ptemp1(m,0);
    vector<int> ptemp2(n,0);

    
    for (int i=0; i<n+2; i++) {
        nonogram[i][0]=-1;
        nonogram[i][m+1]=-1;
    }
    for (int i=0; i<m+2; i++) {
        nonogram[0][i]=-1;
        nonogram[n+1][i]=-1;
    }
    
    
    saveHints(heightHints, widthHints, n, m);
    findOrder(heightHints, widthHints, hOrder, wOrder);
    
    for (int i=0; i<n; i++) {
        linePossibilities(horrizontalPossiblities, heightHints[i], m, 0, ptemp1, 1, i);
    }
    for (int i=0; i<m; i++) {
        linePossibilities(verticalPossiblities, widthHints[i], n, 0, ptemp2, 1, i);
    }
    
    
    definite(horrizontalPossiblities, m, verticalPossiblities, n, nonogram);
    //mark(nonogram, heightHints, widthHints, n, m, lftemp);
    for (int i=0; i<nonogram.size(); i++) {
        for (int j=0; j<nonogram[i].size(); j++) {
            cout<<nonogram[i][j]<<" ";
        }
        cout<<endl;
    }//////
    
    /*for (int i=0; i<verticalPossiblities.size(); i++) {
        for (int k=0; k<verticalPossiblities[i][0].size(); k++) {
            for (int j=0; j<verticalPossiblities[i].size(); j++) {
                cout<<verticalPossiblities[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }//////
    
    for (int i=0; i<horrizontalPossiblities.size(); i++) {
        for (int k=0; k<horrizontalPossiblities[i][0].size(); k++) {
            for (int j=0; j<horrizontalPossiblities[i].size(); j++) {
                cout<<horrizontalPossiblities[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }*//////


    cout<<endl;
    guess(nonogram, horrizontalPossiblities, verticalPossiblities, hOrder, wOrder);
}








