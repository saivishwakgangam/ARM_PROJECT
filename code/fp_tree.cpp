#include<bits/stdc++.h>
using namespace std;
int s_c=360;
class Node{
public:int item_number;
       int count;
       Node* next_link;
       Node* parent;
       map<int,Node*>children;
       Node(int val){
            item_number=val;
            count=0;
            next_link=NULL;
            parent=NULL;
       }
};
class FP_TREE {
    vector<vector<int>>transactions;
    Node *root;
    map<int, int> item_set;
    vector<int> item_set_freq;
    map<int, Node *> item_header;
    int support_count;
    int transactions_size;
    map<int,int>item_support_count;
public:
    FP_TREE(int s_count) {
        root = new Node(-1);
        support_count = s_count;
        transactions_size = 0;
    }

    void read_dataset(string file_name) {
        cout << "READING DATASET....." << endl;
        ifstream read_file(file_name);
        map<int, int> temp_item_set;
        vector<vector<int>>temp_transactions;
        string line;
        int index = 0;
        while (getline(read_file, line)) {
            stringstream ss(line);
            string token;
            vector<int>t;
            while (getline(ss, token, ' ')) {
                if (stoi(token) != -1 && stoi(token) != -2) {
                    temp_item_set[stoi(token)]++;
                    t.push_back(stoi(token));

                }

            }
            temp_transactions.push_back(t);


        }
        cout << "REMOVING ITEMS WITHOUT MINIMUM SUPPORT COUNT..." << endl;
        for (auto ele: temp_item_set) {
            if (ele.second >= support_count) {
                item_set.insert(ele);
            }
        }
        index = 0;
        bool flag;
        for (auto ele: temp_transactions) {
            flag = false;
            vector<int>t;
            for (auto e: ele) {
                if (item_set.count(e)) {
                    flag = true;
                    t.push_back(e);
                }
            }
            sort(t.begin(), t.end());
            if (flag) {
                transactions.push_back(t);
            }
        }
        transactions_size = transactions.size();
        cout << "COMPLETED READING....ITEM COUNT IS " << item_set.size() << " TRANSACTION SIZE IS " << transactions_size
             << endl;
        read_file.close();
    }
    void create_pattern_base(Node* n,int ele,int s_count) {
        map<int, int> temp_item_set;
        vector<int> temp_transactions[s_count+1];
        //do suffix search
        Node* temp=n;
        int index=0;
        while(temp){
            //traverse temp up
            Node* temp1=temp;
            int min_s_count=temp1->count;
            temp1=temp1->parent;
            while(temp1->item_number!=-1){
                temp_item_set[temp1->item_number]+=min_s_count;
                temp_transactions[index].push_back(temp1->item_number);
                temp1=temp1->parent;
            }
            //now copy temp transactions
            for(int i=index+1;i<=index+min_s_count-1;i++){
                temp_transactions[i]=temp_transactions[index];
            }
            index=index+min_s_count;
            temp=temp->next_link;
        }
        for (auto ele: temp_item_set) {
            if (ele.second >= support_count) {
                item_set.insert(ele);
            }
        }
        index = 0;
        bool flag;
        for (auto ele: temp_transactions) {
            flag = false;
            vector<int>t;
            for (auto e: ele) {
                if (item_set.count(e)) {
                    flag = true;
                    t.push_back(e);
                }
            }
            sort(t.begin(), t.end());
            if (flag) {
                transactions.push_back(t);
            }
        }
        transactions_size = transactions.size();

    }
    void sort_transactions() {
        vector<pair<int, int>>temp_itemset;
        for (auto ele: item_set) {
            temp_itemset.push_back({ele.second, ele.first});
        }
        sort(temp_itemset.begin(), temp_itemset.end());
        for (auto ele: temp_itemset) {
            item_set_freq.push_back(ele.second);
            item_header[ele.second] = NULL;
        }

        reverse(item_set_freq.begin(), item_set_freq.end());

        for (int i = 0; i < transactions_size; i++) {

            vector<int> temp_vector;
            for (auto ele: item_set_freq) {
                if (binary_search(transactions[i].begin(), transactions[i].end(), ele)) {
                    temp_vector.push_back(ele);
                }
            }

            transactions[i] = temp_vector;

        }
    }

    Node *insert_item_list(Node *root, int index, int n, vector<int> &list) {
        root->count++;
        //base case
        if (index == n) {
            return root;
        }
        //check if present node as list[index[ as child
        int element = list[index];
        if (root->children.count(element)) {
            //element is present

            root->children[element] = insert_item_list(root->children[element], index + 1, n, list);
        } else {
            //create a new node with element as item number
            Node *new_node = new Node(element);
            //updating item header
            Node *head = item_header[element];
            if(head==NULL){
                head=new_node;
                item_header[element]=head;

            }
            else{
                while (head->next_link != NULL) {
                    head = head->next_link;
                }
                head->next_link = new_node;

            }
            //updating parent
            new_node->parent=root;
            root->children[element] = insert_item_list(new_node, index + 1, n, list);
        }
        return root;
    }
    bool search(Node* root,int index,int n,vector<int>&list){
        if(index==n){
            return true;
        }
        int element=list[index];
        if(!root->children.count(element)){
            return false;
        }
        return search(root->children[element],index+1,n,list);
    }
    Node* construct_fp_tree() {
        //parse the transactions
        for (int i = 0; i < transactions_size; i++) {
            root = insert_item_list(root, 0, transactions[i].size(), transactions[i]);
        }
        //checking the code
        bool result=true;
        for(int i=0;i<transactions_size;i++){
            result&=search(root,0,transactions[i].size(),transactions[i]);
            if(result==false){
                break;
            }
        }
        if(result){

        }
        else{

            return NULL;
        }
        return root;
    }
    vector<int> getItems(){
        return item_set_freq;
    }
    int get_minimum_support_count(){
        return item_set[*(item_set_freq.end()-1)];
    }
    int get_minimum(vector<int>t){
        int minimum=INT_MAX;
        for(auto ele:t){
            minimum=min(minimum,item_set[ele]);
        }
        return minimum;
    }
    pair<int,Node*> get_item_header(int ele){
        return {item_set[ele],item_header[ele]};
    }
    bool isEmpty(){
        if(root->children.size()==0){
            return true;
        }
        return false;
    }
    void delete_path(Node* ptr){
        //update item_header table
        if(ptr==NULL){
            return;
        }
        Node *temp=ptr;
        Node *temp1=temp->parent;
        while(temp1->item_number!=-1){
            if(temp1->count==temp->count){
                item_header[temp1->item_number]=temp1->next_link;
                temp1=temp1->parent;

            }
            else{
                break;
            }
        }
    }
    int get_support_count(int item){
        return item_set[item];
    }
    ~FP_TREE(){

    }

};
bool containsSinglePath(Node *root){
    if(root->children.size()==0){
        return true;
    }
    if(root->children.size()>=2){
        return false;
    }
    return containsSinglePath(root->children.begin()->second);
}
void generate_subsets(int i,int size,vector<pair<int,int>>&items_seen,vector<int>&temp,vector<int>temp_b,FP_TREE *fp,vector<string>&closed_frequent_items){
    if(i==size){
        return;
    }
    //include the element at index i
    temp_b.push_back(temp[i]);
    // get minimum support count
    int support_count=fp->get_minimum(temp_b);
    string cfi="";
    if(support_count>=s_c){

        for(auto ele:items_seen){
            cfi+= to_string(ele.first);
            cfi+=" ";
        }
        for(auto ele:temp_b){
            cfi+= to_string(ele);
            cfi+=" ";
        }
        cfi+= to_string(support_count);
    }
    closed_frequent_items.push_back(cfi);
    generate_subsets(i+1,size,items_seen,temp,temp_b,fp,closed_frequent_items);
    //backtrack
    temp_b.pop_back();
    generate_subsets(i+1,size,items_seen,temp,temp_b,fp,closed_frequent_items);

}
void fp_growth(FP_TREE *fp,Node *root,vector<pair<int,int>>items_seen,vector<string>&closed_frequent_items){
    //now check the base condition
    if(containsSinglePath(root)){
        //all the items present in header plus items seen are pushed to closed_frequent_items

        vector<int>temp=fp->getItems();
        vector<int>temp_b;
        string cfi="";
        int support_count=INT_MAX;
        for(auto ele:items_seen){
            support_count=min(support_count,ele.second);
        }
        if(support_count>=s_c){
            for(auto ele:items_seen){
                cfi+= to_string(ele.first);
                cfi+=" ";
            }
            cfi+= to_string(support_count);
        }
        closed_frequent_items.push_back(cfi);
        generate_subsets(0,temp.size(),items_seen,temp,temp_b,fp,closed_frequent_items);
        return;
    }
    else{
        //so tree contains more than one path shit!!!
        //create conditional pattern bases for each element in header table
        vector<int>items;
        items=fp->getItems();
        //got the items in reverse order of frequency so traverse from last to first(item header)
        for(int i=items.size()-1;i>=0;i--){
            //construct conditional pattern base and conditional pattern tree on items[i]
            FP_TREE *fp_mine=new FP_TREE(s_c);
            pair<int,Node*>p=fp->get_item_header(items[i]);
            fp_mine->create_pattern_base(p.second,items[i],p.first);
            //delete the path which is already accessed
            //fp->delete_path(p.second);
            fp_mine->sort_transactions();

            Node *root_mine=fp_mine->construct_fp_tree();
            if(fp_mine->isEmpty()){

                continue;
            }
            else{
                //recursive call to fp growth
                items_seen.push_back({items[i],fp->get_support_count(items[i])});
                fp_growth(fp_mine,root_mine,items_seen,closed_frequent_items);
                delete fp_mine;
                items_seen.pop_back();
            }


        }

    }
}
bool isSubset(vector<int>v1,vector<int>v2){
    int ptr1=0;
    int ptr2=0;
    while(ptr1<v1.size()&&ptr2<v2.size()){
        if(v1[ptr1]>v2[ptr2]){
            return false;
        }
        else if(v1[ptr1]<v2[ptr2]){
            ptr1++;
        }
        else{
            ptr1++;
            ptr2++;
        }
    }
    return (ptr2==v2.size());
}
int main() {
    FP_TREE *fp = new FP_TREE(s_c);
    fp->read_dataset("dataset.txt");
    fp->sort_transactions();
    Node *root = fp->construct_fp_tree();
    vector<pair<int,int>> s;
    vector<string> closed_frequent_items;
    fp_growth(fp, root, s, closed_frequent_items);
    delete fp;
    cout<<"FREQUENT ITEMS ARE"<<endl;
    for (auto ele: closed_frequent_items) {
        cout << ele << endl;
    }
    //finding closed frequent itemsets
    map<int,map<int,vector<int>>>mp;
    for(auto ele:closed_frequent_items){
        stringstream  ss(ele);
        string token;
        vector<int>t;
        while(getline(ss,token,' ')){
            t.push_back(stoi(token));
        }
        int support_count=t.back();
        t.pop_back();
        sort(t.begin(),t.end());
        mp[support_count].insert({t.size(),t});
    }
    cout<<"FINDING CLOSED FREQUENT ITEMSETS"<<endl;
    vector<vector<int>>closed_frequent;
    for(auto it=mp.begin();it!=mp.end();it++){
        map<int,vector<int>>frequent_items=it->second;
        for(auto it1=frequent_items.rbegin();it1!=frequent_items.rend();it1++){
            bool flag=false;
            for(auto it2=frequent_items.rbegin();it2!=it1;it2++){
                //use the 2 pointer concept
                if(isSubset(it2->second,it1->second)){
                    flag=true;
                    break;
                }
            }
            if(flag==false){
                closed_frequent.push_back(it1->second);
            }

        }

    }
    cout<<"CLOSED FREQUENT ITEMSETS ARE"<<endl;
    for(auto ele:closed_frequent){
        for(auto e:ele){
            cout<<e<<" ";
        }
        cout<<endl;
    }
    return 0;

}